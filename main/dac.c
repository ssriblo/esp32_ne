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
#include "hal/misc.h"
#include "soc/sens_struct.h"

#include "defines.h"
#include "utility.h"
#include "dac.h"

#define DAC_CHAN               0           

static const char *TAG = "dac";

void dac_start(){
    esp_err_t ret;

    ret = dac_output_enable(DAC_CHAN);
    ESP_ERROR_CHECK(ret);

    SENS.sar_dac_ctrl1.sw_tone_en = 0;
    SENS.sar_dac_ctrl2.dac_cw_en1 = 0;

    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, 50);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, 50);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, 50);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, 50);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, 50);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, 50);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, 50);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, 50);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, 50);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, 50);

    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, 150);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, 150);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, 150);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, 150);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, 150);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, 150);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, 150);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, 150);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, 150);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, 150);

}

