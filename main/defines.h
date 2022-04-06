#ifndef _DEFINES_H_
#define _DEFINES_H_

#include <string.h>
#include <stdio.h>
#include "driver/adc.h"

/******************************************************************************
ToDo:
    - DAC code shift, levels
    - ADC shift, levels, profile
    - Disable all interrupt and Freertos task switch - tried to do but rebooing...
    - Setup proper 4 pulses at RMT module
    - Add PWM and ADC for minus 5V/40V

******************************************************************************/

/******************************************************************************
1.75 MHz 4 pulses setup:
    - period = 1/1.75=0.571 us
    - pulse duration = period/2 = 0.2855 us = 285 ns
    - RMT tick = 1/80MHz = 12.5 ns
    - pulse rmt's tick = 285/12.5 = 22.8 ticks
******************************************************************************/


/******************************************************************************
Hardware pin's setup:
    GPIO21 - Transmitter Channel A
    GPIO22 - Transmitter Channel B
    GPIO35 - Echo ADC input (ADC1_CHANNEL_7)
    GPIOxx - DAC ouptut
    pin - UART Tx - depends from current breadboard 
    pin - UART Rx - depends from current breadboard 
    GPIO34 - minus 5V ADC input (ADC1_CHANNEL_6)
    GPIO39 - 40V ADC input (ADC1_CHANNEL_3)
    GPIO16 - minus 5V pulse gen 
    GPIO17 - 40V pulse gen

******************************************************************************/

/****************************************************************/
#define BUILD_VERSION       "Build Version: 0.3 "
/****************************************************************/

//////////////////////////////////////////////////////////////////////////////
// For release uncomment this option:
#define RELEASE                             1

//////////////////////////////////////////////////////////////////////////////
#define PROFILE_SIZE        100

#define TIMES              1024 //256
#define GET_UNIT(x)        ((x>>3) & 0x1)

#define ADC_ECHO_INPUT      ADC1_CHANNEL_7 /* pin GPIO35 */
#define ADC_MINUS_5V_INPUT  ADC1_CHANNEL_6 /* pin GPIO35 */
#define ADC_40V_INPUT       ADC1_CHANNEL_3 /* pin GPIO35 */

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

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_MINUS_5V    (16) // TBD
#define LEDC_OUTPUT_40V         (16) // TBD
#define LEDC_CHANNEL_MINUS_5V   LEDC_CHANNEL_0
#define LEDC_CHANNEL_40V        LEDC_CHANNEL_1
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY_MINUS_5V      (4095) // Set duty to 50%. ((2 ** 13) - 1) * 50% = 4095
#define LEDC_DUTY_40V           (4095) // Set duty to 50%. ((2 ** 13) - 1) * 50% = 4095
#define LEDC_FREQUENCY          (5000) // Frequency in Hertz. Set frequency at 5 kHz

#endif
