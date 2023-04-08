#ifndef __LED_H__
#define __LED_H__
#include <STC15F2K60S2.H>

#define u8 unsigned char 
#define u16 unsigned int

	
void LED_Init(void);//LED灯初始化函数（设置锁存器为跟随输出）
void LED_One(u8 Lx);//点亮指定一个LED灯函数
void LED_LSD1(u16 ms);//从左到右流水
void LED_LSD2(u16 ms);//从右到左流水
void LED_HY(void);//花样流水函数
#endif
