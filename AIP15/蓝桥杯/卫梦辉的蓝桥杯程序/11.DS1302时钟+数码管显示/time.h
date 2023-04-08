#ifndef __TIME_H__
#define __TIME_H__

#include <STC15F2K60S2.h>
#include <intrins.h>

//DS11302时钟芯片单片机控制引脚
sbit SCLK = P1^7;//时钟
sbit DA = P2^3;//数据
sbit RST = P1^3;//复位

extern unsigned char Time[7];//储存时间数组

void Init_DS1302_Time();//初始化设置DS1302芯片时间函数（把数组Time[7]中的时间数据写入DS1302芯片）
void Read_DS1302_Time();//读取DS1302芯片时间函数（把DS1302芯片的时间数据写入数组Time[7]中）

#endif