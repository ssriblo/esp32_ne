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

static const char *TAG = "NewEcho";


void loop(){
    static bool channnelFlipFlop = false;
    channelPulses_t channelPulses;

    while (1)
    {
        /* How to prevent ESP32 from switching tasks?
        https://esp32.com/viewtopic.php?t=10457 */
        // portMUX_TYPE mutex = portMUX_INITIALIZER_UNLOCKED;
        // !!! WARNING !!! mutex and interrupt disable can not use there. Need to find out why, but rebooting !!!
        // portENTER_CRITICAL(&mutex); 
        // taskDISABLE_INTERRUPTS();

        if(channnelFlipFlop){
            channelPulses = CHANNEL_1_AB;
            channnelFlipFlop = false;
        }else{
            channelPulses = CHANNEL_2_AB;
            channnelFlipFlop = true;
        }
        printf(">>>> LOOP channelPulses=%d channnelFlipFlop=%d\n",  channelPulses, channnelFlipFlop);
        start_adc_rmt_dac(channelPulses);
    
        // dac_init();    
        // dac_start();

        // vTaskDelay(8000 / portTICK_PERIOD_MS); // example only
        // taskENABLE_INTERRUPTS();
        // portEXIT_CRITICAL(&mutex);

        vTaskDelay( 1 * portTICK_PERIOD_MS ); // actually 150 ms period, why??
    }
    
}
///////////////////////////////////////////////////////////////////////////////
void app_main(){

    gpio_ini();
    dac_init();
    pwm_init();
   
    xTaskCreatePinnedToCore(
                loop,   /* Function to implement the task */
                "DataqAquringTask", /* Name of the task */
                10000,      /* Stack size in words */
                NULL,       /* Task input parameter */
                0,          /* Priority of the task */
                NULL,       /* Task handle. */
                1);  /* Core where the task should run */

}



