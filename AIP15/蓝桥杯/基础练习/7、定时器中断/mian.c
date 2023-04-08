#include<STC15F2K60S2.h>

unsigned char timer = 0;

void Close_Buzz();
	
void TimerInit();

void main()
{
	Close_Buzz();
	TimerInit();
	P2 = 0x80;
	P0 = 0xff;
	
	while(1);
}


void Close_Buzz()
{
	P2 = 0xA0;
	P0 = 0x00;
	P2 = 0x00; 
}

void TimerInit()
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x00;		//设置定时初值
	TH0 = 0xDC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	
	ET0 = 1;
	EA = 1;
}

void Tmier1() interrupt 1
{
	timer += 1;
	if (timer == 100)
	{
		timer = 0;
		P2 = 0x80;
		P00 = ~P00;
	}
	TL0 = 0x00;		//设置定时初值
	TH0 = 0xDC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}