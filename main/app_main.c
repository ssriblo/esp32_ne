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

static const char *TAG = "NewEcho";

void loop(){
    init();
   
    while (1)
    {
        /* How to prevent ESP32 from switching tasks?
        https://esp32.com/viewtopic.php?t=10457 */
        // portMUX_TYPE mutex = portMUX_INITIALIZER_UNLOCKED;
        // !!! WARNING !!! mutex and interrupt disable can not use there. Need to find out why, but rebooting !!!
        // portENTER_CRITICAL(&mutex); 
        // taskDISABLE_INTERRUPTS();
        start_adc_rmt_dac();
        // vTaskDelay(8000 / portTICK_PERIOD_MS); // example only
        // taskENABLE_INTERRUPTS();
        // portEXIT_CRITICAL(&mutex);

        vTaskDelay( 3 * portTICK_PERIOD_MS ); // actually 150 ms period, why??
    }
    
}
///////////////////////////////////////////////////////////////////////////////
void app_main(){
    // adc_start();       
    xTaskCreatePinnedToCore(
                loop,   /* Function to implement the task */
                "DataqAquringTask", /* Name of the task */
                10000,      /* Stack size in words */
                NULL,       /* Task input parameter */
                0,          /* Priority of the task */
                NULL,       /* Task handle. */
                1);  /* Core where the task should run */

}



