#ifndef __DS18B20_H__
#define __DS18B20_H__
#include <STC15F2K60S2.H>
#include "intrins.h"

//#define uchar unsigned char
//#define uint unsigned int

sbit DS18B20_DQ =P1^4;//设置DS18B20单片机数据采集引脚

char DS18B20_Reset();//DS18B20复位
void DS18B20_WriteData(unsigned char dat);//向DS18B20写数据
unsigned char DS18B20_ReadData();//向DS18B20读数据
float DS18B20_Tem();//DS18B20返回温度值函数

#endif