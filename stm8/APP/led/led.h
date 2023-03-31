#ifndef _led_H
#define _led_H

#include "stm8s.h"


#define     LED1_ON()       GPIO_WriteLow(GPIOC , GPIO_PIN_1) //LED1ÁÁ
#define     LED1_OFF()      GPIO_WriteHigh(GPIOC , GPIO_PIN_1) //LED1Ãð


void InitLED(void);

#endif
