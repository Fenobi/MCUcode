#include <STC15F2K60S2.h>
#include <intrins.h>

sbit LED1=P0^0;
sbit HC138_A=P2^5;
sbit HC138_B=P2^6;
sbit HC138_C=P2^7;

void Delay_ms(unsigned int ms)		//@11.0592MHz
{
	unsigned char i, j;
	while(ms--)
	{
		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} while (--i);
	}
}

void main()
{
	HC138_A=0;
	HC138_B=0;
	HC138_C=1;
	//ÊµÑé³ÌÐò
	while(1)
	{
		LED1=0;
		Delay_ms(500);
		LED1=1;
		Delay_ms(500);
	}
	
}