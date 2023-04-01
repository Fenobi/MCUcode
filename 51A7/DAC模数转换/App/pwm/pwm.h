#ifndef _PWM_H
#define _PWM_H

#include "public.h"

sbit PWM=P2^1;

void pwm_init(u8 tim_h,u8 tim_l,u8 time_scale,u8 duty);
void pwm_set_duty_cycle(u8 duty);

#endif