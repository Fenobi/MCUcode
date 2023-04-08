#ifndef __KEY_H__
#define __KEY_H__
#include <STC15F2K60S2.H>

sbit S4=P3^3;//独立按键控制引脚
sbit S5=P3^2;
sbit S6=P3^1;
sbit S7=P3^0;

char DL_key1(void);//简单的独立按键函数

char JZ_key(void);//矩阵按键驱动函数(返回对应键值)

#endif