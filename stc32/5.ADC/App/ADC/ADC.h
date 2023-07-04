#ifndef __ADC_H
#define __ADC_H

#include "public.h"

#define ADC_Vref  5.0

void ADC_Init();
u16 ADC_Read(u8 ADC_Channel_x);//xΪ0~1
float ADC_Vol(u16 vol);

#endif 