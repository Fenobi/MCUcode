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

void Timer0Init()		//5����@12.000MHz
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0xA0;		//���ö�ʱ��ʼֵ
	TH0 = 0x15;		//���ö�ʱ��ʼֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	
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

