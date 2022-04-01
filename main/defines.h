#ifndef _DEFINES_H_
#define _DEFINES_H_

#include <string.h>
#include <stdio.h>
#include "driver/adc.h"

//////////////////////////////////////////////////////////////////////////////
// For release comment this option
#define ADC_DMA_TIME_MEASUREMENT            1

// For release uncomment this option:
#define RELEASE                             1
//////////////////////////////////////////////////////////////////////////////

#define TIMES              1024 //256
#define GET_UNIT(x)        ((x>>3) & 0x1)

#define ADC_RESULT_BYTE     2
#define ADC_CONV_LIMIT_EN   1                       //For ESP32, this should always be set to 1
#define ADC_CONV_MODE       ADC_CONV_SINGLE_UNIT_1  //ESP32 only supports ADC1 DMA mode
#define ADC_OUTPUT_TYPE     ADC_DIGI_OUTPUT_FORMAT_TYPE1
#define MAX_STORE_BUFF_SIZE 1024                    // let to find out what is it?
#define CONV_LIMIT_NUM      250                     // let to find out what is it?
#define SAMPLE_FREQ_HZ      2000*1000               // 2000000 is maximum value, not more!


static uint16_t adc1_chan_mask = BIT(7);
static uint16_t adc2_chan_mask = 0;
static adc_channel_t channel[1] = {ADC1_CHANNEL_7};


#endif
