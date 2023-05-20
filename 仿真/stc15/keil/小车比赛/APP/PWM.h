#ifndef __PWM_H
#define __PWM_H

//#include "public.h"
#include <STC15F2K60S2.H>

#define CYCLE   6000L //定义PWM周期
sbit PWM2=P3^7;
sbit PWM3=P2^1;
sbit PWM4=P2^2;
sbit PWM5=P2^3;

void pwminit();

void pwm2(unsigned int DUTY);
void pwm3(unsigned int DUTY);
void pwm4(unsigned int DUTY);
void pwm5(unsigned int DUTY);

#endif
