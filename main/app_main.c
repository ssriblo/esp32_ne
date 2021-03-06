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
#include "freertos/task.h"

#include "defines.h"
#include "adc.h"
#include "rmt.h"
#include "dac.h"
#include "pwm.h"
#include "gpio.h"
#include "dac-cosin.h"

static const char *TAG = "NewEcho";


void loop(){
    static bool channnelFlipFlop = false;
    channelPulses_t channelPulses = CHANNEL_1_AB;
    initRmt(channelPulses);

    while (1)
    {
        /* How to prevent ESP32 from switching tasks?
        https://esp32.com/viewtopic.php?t=10457 */
        // !!! WARNING !!! mutex and interrupt disable can not use there. Need to find out why, but rebooting !!!
        // portMUX_TYPE mutex = portMUX_INITIALIZER_UNLOCKED;
        // portENTER_CRITICAL(&mutex); 
        // taskDISABLE_INTERRUPTS();
        // if(channnelFlipFlop){
        //     channelPulses = CHANNEL_1_AB;
        //     channnelFlipFlop = false;
        // }else{
        //     channelPulses = CHANNEL_1_AB;
        //     channnelFlipFlop = true;
        // }
        // printf(">>>> LOOP channelPulses=%d channnelFlipFlop=%d\n",  channelPulses, channnelFlipFlop);
        start_adc_rmt_dac(channelPulses);

#ifdef SLOW_ADC_TEST
        adc1_slow(ADC1_CHANNEL_3);
#endif

        // vTaskDelay(8000 / portTICK_PERIOD_MS); // example only
        // taskENABLE_INTERRUPTS();
        // portEXIT_CRITICAL(&mutex);

        vTaskDelay( 1 * portTICK_PERIOD_MS ); // actually 150 ms period, why??
    }
    
}
///////////////////////////////////////////////////////////////////////////////
void app_main(){

    gpio_ini();
    pwm_init();
#ifdef COSIN_DAC_TEST
    dac_app_main(); // cosin generator
#else
    dac_init();
#endif   
    xTaskCreatePinnedToCore(
                loop,   /* Function to implement the task */
                "DataqAquringTask", /* Name of the task */
                10000,      /* Stack size in words */
                NULL,       /* Task input parameter */
                16,          /* Priority of the task */
                NULL,       /* Task handle. */
                APP_CPU_NUM);  /* Core where the task should run */

}



