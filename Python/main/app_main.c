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



///////////////////////////////////////////////////////////////////////////////
void app_main(){
    printf("START");
    for(int i=0; i< 400; i++){
        printf("%d ", i);
    }
    vTaskDelay( 10 * portTICK_PERIOD_MS ); // actually 150 ms period, why??
}



