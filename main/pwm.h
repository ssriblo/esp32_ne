#ifndef _PWM_H
#define _PWM_H

#include "driver/ledc.h"

void pwm_init();
void pwm_update(ledc_channel_t channel, uint32_t val);

#endif
