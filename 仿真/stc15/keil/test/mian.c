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

void Timer0Init(void)		//50����@12.000MHz
{
	
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0xB0;		//���ö�ʱ��ʼֵ
	TH0 = 0x3C;		//���ö�ʱ��ʼֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	
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

