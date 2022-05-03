#ifndef _ADC_H_
#define _ADC_H

void IRAM_ATTR start_adc_rmt_dac();
void init();
uint32_t adc1_slow(const adc_channel_t channel);

#endif