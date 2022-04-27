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
dac_channel_t channel = DAC_CHANNEL_2;

void dac_init(){
    esp_err_t ret;

    ret = dac_output_enable(channel);
    ESP_ERROR_CHECK(ret);

    for(int i=0; i<PROFILE_SIZE; i++){
        profile[i] = i;
    }
}



void dac_start(){
    SENS.sar_dac_ctrl1.sw_tone_en = 0;
    SENS.sar_dac_ctrl2.dac_cw_en1 = 0;

    dac_ll_update_output_value(channel, profile[1]);
    dac_ll_update_output_value(channel, profile[2]);
    dac_ll_update_output_value(channel, profile[3]);
    dac_ll_update_output_value(channel, profile[4]);
    dac_ll_update_output_value(channel, profile[5]);
    dac_ll_update_output_value(channel, profile[6]);
    dac_ll_update_output_value(channel, profile[7]);
    dac_ll_update_output_value(channel, profile[8]);
    dac_ll_update_output_value(channel, profile[9]);
    dac_ll_update_output_value(channel, profile[10]);


    dac_ll_update_output_value(channel, profile[11]);
    dac_ll_update_output_value(channel, profile[12]);
    dac_ll_update_output_value(channel, profile[13]);
    dac_ll_update_output_value(channel, profile[14]);
    dac_ll_update_output_value(channel, profile[15]);
    dac_ll_update_output_value(channel, profile[16]);
    dac_ll_update_output_value(channel, profile[17]);
    dac_ll_update_output_value(channel, profile[18]);
    dac_ll_update_output_value(channel, profile[19]);
    dac_ll_update_output_value(channel, profile[20]);

    dac_ll_update_output_value(channel, profile[21]);
    dac_ll_update_output_value(channel, profile[22]);
    dac_ll_update_output_value(channel, profile[23]);
    dac_ll_update_output_value(channel, profile[24]);
    dac_ll_update_output_value(channel, profile[25]);
    dac_ll_update_output_value(channel, profile[26]);
    dac_ll_update_output_value(channel, profile[27]);
    dac_ll_update_output_value(channel, profile[28]);
    dac_ll_update_output_value(channel, profile[29]);
    dac_ll_update_output_value(channel, profile[30]);

    dac_ll_update_output_value(channel, profile[31]);
    dac_ll_update_output_value(channel, profile[32]);
    dac_ll_update_output_value(channel, profile[33]);
    dac_ll_update_output_value(channel, profile[34]);
    dac_ll_update_output_value(channel, profile[35]);
    dac_ll_update_output_value(channel, profile[36]);
    dac_ll_update_output_value(channel, profile[37]);
    dac_ll_update_output_value(channel, profile[38]);
    dac_ll_update_output_value(channel, profile[39]);
    dac_ll_update_output_value(channel, profile[40]);

    dac_ll_update_output_value(channel, profile[41]);
    dac_ll_update_output_value(channel, profile[42]);
    dac_ll_update_output_value(channel, profile[43]);
    dac_ll_update_output_value(channel, profile[44]);
    dac_ll_update_output_value(channel, profile[45]);
    dac_ll_update_output_value(channel, profile[46]);
    dac_ll_update_output_value(channel, profile[47]);
    dac_ll_update_output_value(channel, profile[48]);
    dac_ll_update_output_value(channel, profile[49]);
    dac_ll_update_output_value(channel, profile[50]);

    dac_ll_update_output_value(channel, profile[51]);
    dac_ll_update_output_value(channel, profile[52]);
    dac_ll_update_output_value(channel, profile[53]);
    dac_ll_update_output_value(channel, profile[54]);
    dac_ll_update_output_value(channel, profile[55]);
    dac_ll_update_output_value(channel, profile[56]);
    dac_ll_update_output_value(channel, profile[57]);
    dac_ll_update_output_value(channel, profile[58]);
    dac_ll_update_output_value(channel, profile[59]);
    dac_ll_update_output_value(channel, profile[60]);

    dac_ll_update_output_value(channel, profile[61]);
    dac_ll_update_output_value(channel, profile[62]);
    dac_ll_update_output_value(channel, profile[63]);
    dac_ll_update_output_value(channel, profile[64]);
    dac_ll_update_output_value(channel, profile[65]);
    dac_ll_update_output_value(channel, profile[66]);
    dac_ll_update_output_value(channel, profile[67]);
    dac_ll_update_output_value(channel, profile[68]);
    dac_ll_update_output_value(channel, profile[69]);
    dac_ll_update_output_value(channel, profile[70]);

    dac_ll_update_output_value(channel, profile[71]);
    dac_ll_update_output_value(channel, profile[72]);
    dac_ll_update_output_value(channel, profile[73]);
    dac_ll_update_output_value(channel, profile[74]);
    dac_ll_update_output_value(channel, profile[75]);
    dac_ll_update_output_value(channel, profile[76]);
    dac_ll_update_output_value(channel, profile[77]);
    dac_ll_update_output_value(channel, profile[78]);
    dac_ll_update_output_value(channel, profile[79]);
    dac_ll_update_output_value(channel, profile[80]);

    dac_ll_update_output_value(channel, profile[81]);
    dac_ll_update_output_value(channel, profile[82]);
    dac_ll_update_output_value(channel, profile[83]);
    dac_ll_update_output_value(channel, profile[84]);
    dac_ll_update_output_value(channel, profile[85]);
    dac_ll_update_output_value(channel, profile[86]);
    dac_ll_update_output_value(channel, profile[87]);
    dac_ll_update_output_value(channel, profile[88]);
    dac_ll_update_output_value(channel, profile[89]);
    dac_ll_update_output_value(channel, profile[90]);

    dac_ll_update_output_value(channel, profile[91]);
    dac_ll_update_output_value(channel, profile[92]);
    dac_ll_update_output_value(channel, profile[93]);
    dac_ll_update_output_value(channel, profile[94]);
    dac_ll_update_output_value(channel, profile[95]);
    dac_ll_update_output_value(channel, profile[96]);
    dac_ll_update_output_value(channel, profile[97]);
    dac_ll_update_output_value(channel, profile[98]);
    dac_ll_update_output_value(channel, profile[99]);
}

