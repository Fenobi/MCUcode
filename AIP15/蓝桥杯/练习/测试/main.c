#include <STC15F2K60S2.H>

typedef unsigned char u8;
typedef unsigned int u16;

sbit LED1=P0^0;
sbit LED2=P0^1;
sbit lA=P2^5;
sbit lB=P2^6;
sbit lC=P2^7;

void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 180;
	j = 73;
	do
	{
		while (--j);
	} while (--i);
}

void delay(int n)
{
	
	while(n--)
	{
		Delay100ms();
	}
}

void main()
{
	lA=0;
	lB=0;
	lC=1;
	while(1)
	{
		LED1=0;
		delay(50);
		LED1=1;
		delay(50);
		LED2=0;
		delay(50);
		LED2=1;
		delay(50);
	}
}