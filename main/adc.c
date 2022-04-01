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
#include "rmt.h"

/******************************************************************************
ToDo:
- add DAC code

******************************************************************************/

static const char *TAG = "newEchoADC";

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
        adc_pattern[i].atten = ADC_ATTEN_DB_0;
        adc_pattern[i].channel = ch;
        adc_pattern[i].unit = unit;
        adc_pattern[i].bit_width = SOC_ADC_DIGI_MAX_BITWIDTH;

        ESP_LOGI(TAG, "adc_pattern[%d].atten is :%x", i, adc_pattern[i].atten);
        ESP_LOGI(TAG, "adc_pattern[%d].channel is :%x", i, adc_pattern[i].channel);
        ESP_LOGI(TAG, "adc_pattern[%d].unit is :%x", i, adc_pattern[i].unit);
    }
    dig_cfg.adc_pattern = adc_pattern;
    ESP_ERROR_CHECK(adc_digi_controller_configure(&dig_cfg));

    printf("TIMES=%d  sample_freq_hz= %d\n", TIMES, dig_cfg.sample_freq_hz);

}

///////////////////////////////////////////////////////////////////////////////
void IRAM_ATTR adc_start()
{
    esp_err_t ret;
    uint32_t ret_num = 0;
    uint8_t result[TIMES] = {0};
    memset(result, 0xcc, TIMES);

#ifdef SIN_WAVE_TEST_ONLY
    dac_app_main();     // Generate sinus wave to test only
#endif
    continuous_adc_init(adc1_chan_mask, adc2_chan_mask, channel, sizeof(channel) / sizeof(adc_channel_t));

#ifdef ADC_DMA_TIME_MEASUREMENT    
    // test code time spend measure, not for release:
    int t1 = portGET_RUN_TIME_COUNTER_VALUE();
    int t11 = sys_port_get_time_into_tick();
    uint64_t t_start = esp_timer_get_time();
    ets_delay_us(25); // just for test, not used
    __asm__ __volatile__ ("nop");

    uint64_t t_end = esp_timer_get_time();
    int t22 = sys_port_get_time_into_tick();
    int t2 = portGET_RUN_TIME_COUNTER_VALUE();
#endif

    initRmt();

    adc_digi_start(); // ADC+DMA start
#ifdef RELEASE
    runRmt();
    dac_start();    
#endif    
#ifdef ADC_DMA_TIME_MEASUREMENT    
    // test code time spend measure, not for release:
    uint64_t start = esp_timer_get_time();
    uint64_t start2 = esp_timer_get_time();
    int t33 = sys_port_get_time_into_tick();
    int t3 = portGET_RUN_TIME_COUNTER_VALUE();
#endif

    ret = adc_digi_read_bytes(result, TIMES, &ret_num, ADC_MAX_DELAY); // ADC data obtained from DAC ring buffer

#ifdef ADC_DMA_TIME_MEASUREMENT    
    uint64_t end = esp_timer_get_time();
    int t44 = sys_port_get_time_into_tick();
    int t4 = portGET_RUN_TIME_COUNTER_VALUE();
    printf("TIME took %llu microseconds ret number= %d\n", (end - start), ret_num);
    printf("TIME2 took %llu microseconds ret number= %d\n", (end - start2), ret_num);
    printf("us=%llu \n", t_end-t_start);
    printf("tt= %d %d %d %u\n", t22-t11, t44-t33, t4-t3, ets_get_cpu_frequency());
#endif

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
#ifdef PRINT_ADC_DATA
        for (int i = 0; i < ret_num; i += ADC_RESULT_BYTE) {
            adc_digi_output_data_t *p = (void*)&result[i];
            ESP_LOGI(TAG, "Unit: %d, Channel: %d, Value: %x", 1, p->type1.channel, p->type1.data);
            ESP_LOGI(TAG, "i=%d Value_Hex: %x Value_Dec= %d ", i, p->type1.data, p->type1.data);
        }
#endif
        //See `note 1`
        vTaskDelay(1);
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
}


