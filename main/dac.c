#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "driver/dac.h"
#include "driver/timer.h"
#include "esp_log.h"
#include "hal/dac_ll.h"
//#include "hal/misc.h"
#include "soc/sens_struct.h"

#include "defines.h"
#include "utility.h"
#include "dac.h"

static const char *TAG = "dac";
uint8_t profile[PROFILE_SIZE];

void dac_init(){
    esp_err_t ret;

    ret = dac_output_enable(DAC_CHANNEL_2);
    ESP_ERROR_CHECK(ret);

    SENS.sar_dac_ctrl1.sw_tone_en = 0;
    SENS.sar_dac_ctrl2.dac_cw_en1 = 0;

    for(int i=0; i<PROFILE_SIZE; i++){
        profile[i] = i;
    }
}



void dac_start(){
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]); // 1
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]); // 10
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]); // 11
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]); // 20
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]); // 21
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]); // 30
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]); // 31
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]); // 40
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]); // 41
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]); // 50
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]); // 51
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]); // 60
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]); // 61
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]); // 70
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]); // 71
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]); // 80
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]); // 81
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]); // 90
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]); // 91
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[0]); // 100

}

