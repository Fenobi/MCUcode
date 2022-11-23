#include <STC15F2K60S2.H>

sbit s5=P3^2;
sbit s4=P3^3;
sbit LED1=P0^0;
sbit LED2=P0^1;
sbit lA=P2^5;
sbit lB=P2^6;
sbit lC=P2^7;

//void Delay10us()		//@11.0592MHz
//{
//	unsigned char i;

//	i = 2;
//	while (--i);
//}


void LED()
{
	lA=0;
	lB=0;
	lC=1;
}

void main()
{
	LED();
	
	EX0 = 1;
	IT0 = 1;
	
	EX1 = 1;
	IT1 = 1;
	
	EA = 1;
	
	while(1)
		;
	
}

void Interrupt1() interrupt 0
{
	LED1=~LED1;
}

void Interrupt2() interrupt 2
{
	LED2=~LED2;
}