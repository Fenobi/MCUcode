#include <STC15F2K60S2.H>

sbit LED1=P0^0;

void tm0_isr() interrupt 1
{
	LED1=~LED1;
}

void LED()
{
	P25=0;
	P26=0;
	P27=1;
}

void Timer0Init()		//5毫秒@12.000MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xA0;		//设置定时初始值
	TH0 = 0x15;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	
	ET0 = 1;
	EA = 1;
}


void main()
{
	LED();
	
	Timer0Init();
	//LED1=~LED1;
	while(1)
	{
		
	}
}

