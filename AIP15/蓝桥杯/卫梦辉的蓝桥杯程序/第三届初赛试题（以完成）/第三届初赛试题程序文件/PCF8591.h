#ifndef __PCF8591_H__
#define __PCF8591_H__
#include <STC15F2K60S2.H>

#define u8 unsigned char
#define u16 unsigned int

//A/D转换通道选择
#define AIN0 0x00
#define AIN1 0x01 //光敏电阻通道
#define AIN2 0x02
#define AIN3 0x03

u8 PCF8591_Read(u8 AINx);//返回PCF8591芯片ADC转换值

#endif