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
    - Fram pulse
    - ADC for minus 5V, 40V
    - ADC Echo adjust sample rate, about 1.75MHz, not more then 2MHz
    - Second RMT channels 2A/2B add
    - ADC minus 40V function call
    - SPI for external ADC??
    - ADC 8 bit parallel?
    - cycle should be about 100ms

Check List:
    + Frame pulse --__-- 8ms, perido 160ms
    + RMT pulses
    +  RMT 2nd channel
    - DAC shift, level
    - ADC Echo input range
    + PWM 40V pulses
    - DAC signal
    - ADC signal
    - 100 ms cycle
    - ADC 40V, minus 5V test

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
    GPIO21 - Transmitter Channel 1A
    GPIO22 - Transmitter Channel 1B
    GPIO32 - Transmitter Channel 2A
    GPIO33 - Transmitter Channel 2B
    GPIO35 - Echo ADC input (ADC1_CHANNEL_7)
    GPIO26 - DAC ouptut
    GPIO14 - Frame pulse
    TXD0 - UART Tx 
    RXD0 - UART Rx 
    GPIO34 - minus 5V ADC input (ADC1_CHANNEL_6)
    GPIO39 - 40V ADC input (ADC1_CHANNEL_3)
    GPIO17 - 40V pulse gen (10us pulse high level, period 100 us)
******************************************************************************/

/****************************************************************/
#define BUILD_VERSION       "Build Version: 0.5 "
/****************************************************************/

#define PRINT_ADC_DATA      1
// Uncomment follow if need to test ADC and disable DAC. Instead ordinary DAC cosin generator used
// #define COSIN_DAC_TEST      1

// Uncomment follow if need to do 40V slow adc
#define SLOW_ADC_TEST       1

//////////////////////////////////////////////////////////////////////////////
// For release uncomment this option:
#define RELEASE                             1

//////////////////////////////////////////////////////////////////////////////
// DAC samples number
#define PROFILE_SIZE        100

// ADC samples number
#define TIMES              1024 //256
#define GET_UNIT(x)        ((x>>3) & 0x1)

// ADC for echo acquisition
#define ADC_ECHO_INPUT      ADC1_CHANNEL_7 /* pin GPIO35 */

// ADC for minus 5V power supply (possibly is not needed?)
#define ADC_MINUS_5V_INPUT  ADC1_CHANNEL_6 /* pin GPIO34 */

// ADC for 40V power supply
#define ADC_40V_INPUT       ADC1_CHANNEL_3 /* pin GPIO39 */

// ADC setup
#define ADC_RESULT_BYTE     2
#define ADC_CONV_LIMIT_EN   1                       //For ESP32, this should always be set to 1
#define ADC_CONV_MODE       ADC_CONV_SINGLE_UNIT_1  //ESP32 only supports ADC1 DMA mode
#define ADC_OUTPUT_TYPE     ADC_DIGI_OUTPUT_FORMAT_TYPE1
#define MAX_STORE_BUFF_SIZE 1024                    // let to find out what is it?
#define CONV_LIMIT_NUM      250                     // let to find out what is it?
#define SAMPLE_FREQ_HZ      2000*1000               // TBD, 2000000 is maximum value, not more!
// #define DAC_CHANNEL_1       0    /*!< DAC channel 1 is GPIO25(ESP32) / GPIO17(ESP32S2) */
#define DAC_CHANNEL_2       1    /*!< DAC channel 2 is GPIO26(ESP32) / GPIO18(ESP32S2) */

#define ADC1_CHAN_MASK      BIT(7)
#define ADC2_CHAN_MASK      0  

#define DEFAULT_VREF    1100        //Use adc2_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES   64          //Multisampling
#define CHANNEL_SLOW    ADC1_CHANNEL_3  /*GPIO34 for ADC1*/

// PWM output for minus 40V
#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE /* LEDC_HIGH_SPEED_MODE  LEDC_LOW_SPEED_MODE */
#define LEDC_OUTPUT_40V         (17) 
#define LEDC_CHANNEL_40V        LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_8_BIT 
#define LEDC_DUTY_40V           (25) // Set duty to 10%. ((2 ** 8) - 1) * 10% = 25.5
// PWM period 100us, frequency 10KHz
#define LEDC_FREQUENCY          (10000) // Frequency in Hertz. Set frequency at 10 kHz

// Frame Ouput setup
#define FRAME_OUT_PIN           GPIO_NUM_14

// RMT setup
typedef enum {
    CHANNEL_1_AB = 0,
    CHANNEL_2_AB
}channelPulses_t;

#define CHANNEL_1A_PIN 21
#define CHANNEL_1B_PIN 22
#define CHANNEL_2A_PIN 32
#define CHANNEL_2B_PIN 33

#endif
