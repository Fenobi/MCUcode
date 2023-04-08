#include "TIMERx.h"//定时器函数头文件
#define FOSC 11059200L

#define T1MS (65536-FOSC/1000)      //1T模式***定时1000us（1ms）1
//#define T1MS (65536-FOSC/12/1000) //12T模式**定时1000us（1ms）2

//**************************************************************
void TIM0_Init(void)//定时器0初始化函数
{
    AUXR |= 0x80;                   //定时器0为1T模式 1
//  AUXR &= 0x7f;                   //定时器0为12T模式 2

    TMOD = 0x00;                    //设置定时器为模式0(16位自动重装载)
	
    TL0 = T1MS*5;                     //初始化计时值(5ms)
    TH0 = T1MS*5 >> 8;
    TR0 = 1;                        //使能定时器0中断
    EA = 1;					               //定时器0开始计时
    ET0 = 1;         						  	//打开总中断
}

u16 TIM0_count;
void timer0_isr() interrupt 1
{
	TIM0_count++;
	if(TIM0_count>200)//时间：5ms*200=1s
	{
		TIM0_count=0;
		P00=~P00;
	}
}


//**************************************************************
void TIM1_Init(void)//定时器1初始化函数
{
    AUXR |= 0x40;                   //定时器1为1T模式 1
//  AUXR &= 0xdf;                   //定时器1为12T模式 2

    TMOD = 0x00;                    //设置定时器为模式0(16位自动重装载)
    TL1 = T1MS*5;                     //初始化计时值(5ms)
    TH1 = T1MS*5 >> 8;
    TR1 = 1;                        //定时器1开始计时
    ET1 = 1;                        //使能定时器0中断
    EA = 1;													//打开总中断
}

u16 TIM1_count;
void timer1_isr() interrupt 3
{
	TIM1_count++;
	if(TIM1_count>100)//时间：5ms*100=500ms
	{
		TIM1_count=0;
		P01=~P01;
	}	
}

//**************************************************************
void TIM2_Init(void)//定时器2初始化函数
{
    AUXR |= 0x04;                   //定时器2为1T模式 1
//  AUXR &= ~0x04;                  //定时器2为12T模式 2
	
    T2L = T1MS;                     //初始化计时值
    T2H = T1MS >> 8;
    AUXR |= 0x10;                   //定时器2开始计时
    
    IE2 |= 0x04;                    //开定时器2中断
    EA = 1;
}

//中断服务程序
u16 TIM2_count;
void timer2_isr() interrupt 12           //中断入口
{
	TIM2_count++;
	if(TIM2_count>50)//时间：5ms*50=250ms
	{
		TIM2_count=0;
		P02=~P02;
	}	
	
//  IE2 &= ~0x04;                   //若需要手动清除中断标志,可先关闭中断,此时系统会自动清除内部的中断标志
//  IE2 |= 0x04;                    //然后再开中断即可
}