#ifndef __TIMERx_H__
#define __TIMERx_H__
#include <STC15F2K60S2.H>

#define u8 unsigned char
#define u16 unsigned int 
	
extern float Water_L;

void TIM0_Init(void);//��ʱ��0��ʼ������
void TIM1_Init(void);//��ʱ��1��ʼ������
void TIM2_Init(void);//��ʱ��2��ʼ������

#endif
