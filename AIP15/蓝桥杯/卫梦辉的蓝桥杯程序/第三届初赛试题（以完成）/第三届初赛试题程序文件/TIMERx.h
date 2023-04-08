#ifndef __TIMERx_H__
#define __TIMERx_H__
#include <STC15F2K60S2.H>

#define u8 unsigned char
#define u16 unsigned int 
	
extern float Water_L;

void TIM0_Init(void);//定时器0初始化函数
void TIM1_Init(void);//定时器1初始化函数
void TIM2_Init(void);//定时器2初始化函数

#endif
