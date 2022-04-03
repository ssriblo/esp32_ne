#ifndef _DEFINES_H_
#define _DEFINES_H_

#include <string.h>
#include <stdio.h>
#include "driver/adc.h"

/******************************************************************************
ToDo:
    - DAC code shift, levels
    - ADC shift, levels, profile
    - Disable all interrupt and Freertos task switch

******************************************************************************/

/******************************************************************************
Hardware pin's setup:
    GPIO21 - Transmitter Channel A
    GPIO22 - Transmitter Channel B
    GPIO35 - Echo ADC input
    GPIOxx - DAC ouptut
    pin - UART Tx - depends from current breadboard 
    pin - UART Rx - depends from current breadboard 
    pin TBD - minus 5V ADC input
    pin TBD - 40V ADC input
    pin TBD - minus 5V pulse gen 
    pin TBD - 40V pulse gen

******************************************************************************/

/****************************************************************/
#define BUILD_VERSION       "Build Version: 0.1 "
/****************************************************************/

//////////////////////////////////////////////////////////////////////////////
// For release comment this option
//#define ADC_DMA_TIME_MEASUREMENT            1

// For release uncomment this option:
#define RELEASE                             1
//////////////////////////////////////////////////////////////////////////////
#define PROFILE_SIZE        100

#define TIMES              1024 //256
#define GET_UNIT(x)        ((x>>3) & 0x1)

#define ADC_RESULT_BYTE     2
#define ADC_CONV_LIMIT_EN   1                       //For ESP32, this should always be set to 1
#define ADC_CONV_MODE       ADC_CONV_SINGLE_UNIT_1  //ESP32 only supports ADC1 DMA mode
#define ADC_OUTPUT_TYPE     ADC_DIGI_OUTPUT_FORMAT_TYPE1
#define MAX_STORE_BUFF_SIZE 1024                    // let to find out what is it?
#define CONV_LIMIT_NUM      250                     // let to find out what is it?
#define SAMPLE_FREQ_HZ      2000*1000               // 2000000 is maximum value, not more!
#define DAC_CHANNEL_1       0    /*!< DAC channel 1 is GPIO25(ESP32) / GPIO17(ESP32S2) */
#define DAC_CHANNEL_2       1    /*!< DAC channel 2 is GPIO26(ESP32) / GPIO18(ESP32S2) */

#define ADC1_CHAN_MASK      BIT(7)
#define ADC2_CHAN_MASK      0  

#endif
