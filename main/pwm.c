#include <stdio.h>
#include "driver/ledc.h"
#include "esp_err.h"

#include "defines.h"
#include "pwm.h"


// follows example https://github.com/espressif/esp-idf/tree/4350e6fef859b94f3efae6ceced751911c9d2cbc/examples/peripherals/ledc/ledc_basic

void pwm_init(){
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_DUTY_RES,
        .freq_hz          = LEDC_FREQUENCY, 
        .clk_cfg          = LEDC_AUTO_CLK // LEDC_USE_APB_CLK LEDC_AUTO_CLK
    };

    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL_40V,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_40V,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };

    ledc_channel.channel = LEDC_CHANNEL_40V;
    ledc_channel.gpio_num = LEDC_OUTPUT_40V;
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    // Set duty 40V
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_40V, LEDC_DUTY_40V));
    // Update duty to apply the new value
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_40V));

}

void pwm_update(ledc_channel_t channel, uint32_t val){
    // Set duty to 50%
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, channel, val));
    // Update duty to apply the new value
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, channel));

}