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
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x00;		//���ö�ʱ��ֵ
	TH0 = 0xDC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	
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
	TL0 = 0x00;		//���ö�ʱ��ֵ
	TH0 = 0xDC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}