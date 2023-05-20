#include <STC15F2K60S2.H>

sbit LED1=P0^0;

static unsigned char i;

void tm0_isr() interrupt 1
{
	++i;
	if(i==20)
	{
		i=0;
		LED1=~LED1;
	}
}

void Timer0Init(void)		//50毫秒@12.000MHz
{
	
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xB0;		//设置定时初始值
	TH0 = 0x3C;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	
}

void main()
{
	i=0;
	ET0 = 1;
	EA = 1;
	Timer0Init();
	while(1)
	{}
}

