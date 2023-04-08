#ifndef TIME_H
#define TIME_H

#include<STC15F2K60S2.h>
#include<intrins.h>

sbit SCLK = P1^7;
sbit DA = P2^3;
sbit RST = P1^3;

extern unsigned char Time[7];

void Init_DS1302_Time();
void Read_DS1302_Time();
void burst_Init_time();
#endif