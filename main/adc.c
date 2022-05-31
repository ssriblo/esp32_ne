#include <string.h>
#include <stdio.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/adc.h"
#include "esp_timer.h"
#include <rom/ets_sys.h>

#include "defines.h"
#include "dac-cosin.h"
#include "utility.h"
#include "dac.h"

#include "pwm.h"

#include "rmt.h"
#include "gpio.h"

#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

static const char *TAG = "ADC";

static bool buffer_print_done = false;
///////////////////////////////////////////////////////////////////////////////
// Helper function takes tick into nanoseconds
// https://github.com/eerimoq/simba/issues/155
static int sys_port_get_time_into_tick()
{
    // get clock count
    // http://sub.nanona.fi/esp8266/timing-and-ticks.html
    uint32_t ccount;
    __asm__ __volatile__("esync; rsr %0,ccount":"=a" (ccount));
    // get nanos
    // from https://github.com/adafruit/ESP8266-Arduino/blob/50122289a3ecb7cddcba34db9ec9ec8b4d7e7442/hardware/esp8266com/esp8266/cores/esp8266/Esp.h#L129
    // system_get_cpu_freq() returns 80 or 160; unit MHz
    ccount /= ets_get_cpu_frequency(); // (freq_MHz*1000000) Hz = 1/second // Get the real CPU ticks per us to the ets.
    
    return ccount;
}

static void print_char_val_type(esp_adc_cal_value_t val_type)
{
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
        printf("Characterized using Two Point Value\n");
    } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
        printf("Characterized using eFuse Vref\n");
    } else {
        printf("Characterized using Default Vref\n");
    }
}

uint32_t adc1_slow(const adc_channel_t channel){
    static esp_adc_cal_characteristics_t *adc_chars;
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(channel, ADC_ATTEN_DB_11);
    //Characterize ADC
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_chars);
    print_char_val_type(val_type);

    uint32_t adc_reading = 0;
    //Multisampling
    for (int i = 0; i < NO_OF_SAMPLES; i++) {
            // adc_reading += adc1_get_raw((adc1_channel_t)channel);
    }
    adc_reading /= NO_OF_SAMPLES;
    //Convert adc_reading to voltage in mV
    uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
    printf("Raw: %d\tVoltage: %dmV\n", adc_reading, voltage);

    adc_digi_stop();
    adc_digi_deinitialize();
    return voltage;
}

///////////////////////////////////////////////////////////////////////////////
static void continuous_adc_init(uint16_t adc1_chan_mask, uint16_t adc2_chan_mask, adc_channel_t *channel, uint8_t channel_num)
{
    adc_digi_init_config_t adc_dma_config = {
        .max_store_buf_size = MAX_STORE_BUFF_SIZE,
        .conv_num_each_intr = TIMES,
        .adc1_chan_mask = adc1_chan_mask,
        .adc2_chan_mask = adc2_chan_mask,
    };
    ESP_ERROR_CHECK(adc_digi_initialize(&adc_dma_config));

    adc_digi_configuration_t dig_cfg = {
        .conv_limit_en = ADC_CONV_LIMIT_EN,
        .conv_limit_num = CONV_LIMIT_NUM,
        .sample_freq_hz = SAMPLE_FREQ_HZ,
        .conv_mode = ADC_CONV_MODE,
        .format = ADC_OUTPUT_TYPE,
    };

    adc_digi_pattern_config_t adc_pattern[SOC_ADC_PATT_LEN_MAX] = {0};
    dig_cfg.pattern_num = channel_num;
    for (int i = 0; i < channel_num; i++) {
        uint8_t unit = GET_UNIT(channel[i]);
        uint8_t ch = channel[i] & 0x7;
        adc_pattern[i].atten = ADC_ATTEN_DB_11; // ADC_ATTEN_DB_11  ADC_ATTEN_DB_6  ADC_ATTEN_DB_0
        adc_pattern[i].channel = ch;
        adc_pattern[i].unit = unit;
        adc_pattern[i].bit_width = SOC_ADC_DIGI_MAX_BITWIDTH;

        ESP_LOGI(TAG, "adc_pattern[%d].atten is :%x", i, adc_pattern[i].atten);
        ESP_LOGI(TAG, "adc_pattern[%d].channel is :%x", i, adc_pattern[i].channel);
        ESP_LOGI(TAG, "adc_pattern[%d].unit is :%x", i, adc_pattern[i].unit);
    }
    dig_cfg.adc_pattern = adc_pattern;
    ESP_ERROR_CHECK(adc_digi_controller_configure(&dig_cfg));

    ESP_LOGI(TAG, "TIMES=%d  sample_freq_hz= %d", TIMES, dig_cfg.sample_freq_hz);
}

///////////////////////////////////////////////////////////////////////////////
void IRAM_ATTR start_adc_rmt_dac(channelPulses_t channelPulses)
{
    // ESP_LOGI(TAG, ">-1"));
    esp_err_t ret=0;
    uint32_t ret_num = 0;
    uint8_t result[TIMES] = {0};
    memset(result, 0xcc, TIMES);

    adc_channel_t channel_list[1] = {ADC_ECHO_INPUT};
    continuous_adc_init(ADC1_CHAN_MASK, ADC2_CHAN_MASK, channel_list, sizeof(channel_list) / sizeof(adc_channel_t));

    // initRmt(channelPulses);
    ESP_LOGI("TASK:", ">>> START");


        /* How to prevent ESP32 from switching tasks?
        https://esp32.com/viewtopic.php?t=10457 */
        // !!! WARNING !!! mutex and interrupt disable can not use there. Need to find out why, but rebooting !!!
        // portMUX_TYPE mutex = portMUX_INITIALIZER_UNLOCKED;
        // portENTER_CRITICAL(&mutex); 
        // taskDISABLE_INTERRUPTS();
        // vTaskDelay(8000 / portTICK_PERIOD_MS); // example only
        // taskENABLE_INTERRUPTS();
        // portEXIT_CRITICAL(&mutex);


    int t1 = sys_port_get_time_into_tick();
    
    adc_digi_start(); // ADC+DMA start
    
    ledc_stop(LEDC_MODE, LEDC_CHANNEL_40V, 0);
    setFrameLow();

    runRmt(channelPulses);

#ifndef COSIN_DAC_TEST
    dac_start();    
#endif 

    ret = adc_digi_read_bytes(result, TIMES, &ret_num, ADC_MAX_DELAY); // ADC data obtained from DAC ring buffer
    
    setFrameHigh();
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_40V);

    int t2 = sys_port_get_time_into_tick();


    if (ret == ESP_OK || ret == ESP_ERR_INVALID_STATE) {
        if (ret == ESP_ERR_INVALID_STATE) {
            /**
             * @note 1
             * Issue:
             * As an example, we simply print the result out, which is super slow. Therefore the conversion is too
             * fast for the task to handle. In this condition, some conversion results lost.
             *
             * Reason:
             * When this error occurs, you will usually see the task watchdog timeout issue also.
             * Because the conversion is too fast, whereas the task calling `adc_digi_read_bytes` is slow.
             * So `adc_digi_read_bytes` will hardly block. Therefore Idle Task hardly has chance to run. In this
             * example, we add a `vTaskDelay(1)` below, to prevent the task watchdog timeout.
             *
             * Solution:
             * Either decrease the conversion speed, or increase the frequency you call `adc_digi_read_bytes`
             */
        }

        ESP_LOGI("TASK:", "ret is %x, ret_num is %d", ret, ret_num);
        ESP_LOGI("TASK:", "t1=%d, t2=%d t2-t1=%d\n", t1, t2, t2-t1);
#ifdef PRINT_ADC_DATA
        uint64_t adc_data64 = 0;
        uint32_t result32 = 0;
        if(buffer_print_done != true){
            for (int i = 0; i < ret_num; i += ADC_RESULT_BYTE) {
            // for (int i = 0; i < 10; i += ADC_RESULT_BYTE) {
                adc_digi_output_data_t *p = (void*)&result[i];
                adc_data64 += p->type1.data;
                result32 = p->type1.data;
                // ESP_LOGI(TAG, "Unit: %d, Channel: %d, Value: %x  ", 1, p->type1.channel, p->type1.data);
                // ESP_LOGI(TAG, "i=%d Value_Hex: %x Value_Dec= %d ", i, p->type1.data, p->type1.data);
                // buffer_print_done = true;
            }
                uint32_t adc_data32 = adc_data64 / (ret_num / ADC_RESULT_BYTE);
                ESP_LOGI(TAG, "result32=%d ADC=%d ", result32, adc_data32);
           
        }
#endif
        //See `note 1`
        // vTaskDelay(100);
    } else if (ret == ESP_ERR_TIMEOUT) {
        /**
         * ``ESP_ERR_TIMEOUT``: If ADC conversion is not finished until Timeout, you'll get this return error.
         * Here we set Timeout ``portMAX_DELAY``, so you'll never reach this branch.
         */
        ESP_LOGW(TAG, "No data, increase timeout or reduce conv_num_each_intr");
    }
    adc_digi_stop();
    ret = adc_digi_deinitialize();
    assert(ret == ESP_OK);

    ESP_LOGI("TASK:", ">>> END");

}


