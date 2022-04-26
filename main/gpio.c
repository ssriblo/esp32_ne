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
#include "gpio.h"

void gpio_ini(){
    //zero-initialize the config sructure.
    gpio_config_t io_conf = {};
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO14
    io_conf.pin_bit_mask = (1ULL<<FRAME_OUT_PIN);
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);
    GPIO.out_w1ts = (1 << FRAME_OUT_PIN);
}


void setFrameLow(){
    GPIO.out_w1tc = (1 << FRAME_OUT_PIN);
}

void setFrameHigh(){
    GPIO.out_w1ts = (1 << FRAME_OUT_PIN);
}

// For test only, not used at main program
void gpio_max_speed_test(){
    gpio_ini(FRAME_OUT_PIN);
    // int cnt = 0;
    // while(1) {
    //     printf("cnt: %d\n", cnt++);
    //     vTaskDelay(1000 / portTICK_RATE_MS);
    //     gpio_set_level(FRAME_OUT_PIN, cnt % 2);
    // }
    while (1)   
    {
        for(int i=0; i<10; i++){
            GPIO.out_w1ts = (1 << FRAME_OUT_PIN);
            // __asm__ __volatile__("nop;nop;nop;nop;nop;nop;nop;"); // Bug workaround (I found this snippet somewhere in this forum)

            GPIO.out_w1tc = (1 << FRAME_OUT_PIN);
            // __asm__ __volatile__("nop;nop;nop;nop;nop;nop;nop;");
        }
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}
