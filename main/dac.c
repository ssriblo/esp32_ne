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
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[1]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[2]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[3]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[4]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[5]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[6]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[7]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[8]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[9]); // 10
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[10]); // 11
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[11]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[12]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[13]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[14]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[15]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[16]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[17]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[18]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[19]); // 20
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[20]); // 21
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[21]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[22]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[23]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[24]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[25]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[26]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[27]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[28]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[29]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[30]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[31]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[32]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[33]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[34]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[35]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[36]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[37]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[38]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[39]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[40]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[41]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[42]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[43]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[44]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[45]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[46]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[47]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[48]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[49]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[50]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[51]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[52]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[53]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[54]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[55]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[56]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[57]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[58]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[59]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[60]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[61]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[62]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[63]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[64]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[65]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[66]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[67]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[68]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[69]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[70]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[71]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[72]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[73]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[74]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[75]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[76]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[77]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[78]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[79]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[80]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[81]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[82]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[83]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[84]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[85]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[86]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[87]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[88]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[89]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[90]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[81]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[82]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[83]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[84]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[85]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[86]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[87]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[88]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[89]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[90]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[91]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[92]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[93]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[94]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[95]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[96]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[97]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[98]);
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[0], dac, profile[99]);

}

