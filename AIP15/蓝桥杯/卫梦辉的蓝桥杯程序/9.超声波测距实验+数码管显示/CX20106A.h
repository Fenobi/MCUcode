#ifndef __CX20106_H__
#define __CX20106_H__
#include <STC15F2K60S2.h>
#include <intrins.h>

#define u8 unsigned char 
#define u16 unsigned int 
	
void Delay12us(void);//@11.0592MHz
void send_wave(void);//发送八段脉冲波(40Khz)
void CSB_Init(void);//超声波模块初始化函数
u16 Get_Distance(void);//超声波模块获得距离函数（函数还回距离值 单位：cm）

#endif