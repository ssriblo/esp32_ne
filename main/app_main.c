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
#include "adc.h"

static const char *TAG = "NewEcho";

void loop(){
    init();
    while (1)
    {
        start_adc_rmt_dac();
        vTaskDelay( 20 * portTICK_PERIOD_MS );
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



