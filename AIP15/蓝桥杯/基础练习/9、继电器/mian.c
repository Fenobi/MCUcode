#include <STC15F2K60S2.h>
#include <intrins.h>
sbit k1 = P3^0;
sbit k2 = P3^1;

void Close_Buzz();
void Oppen_Relay();
void Close_Relay();
void Delay6ms();


void main()
{
	Close_Buzz();
	while(1)
	{
		if (k1==0)
		{
			Delay6ms();
			if (k1==0)
			{
				Oppen_Relay();
			}
			while(!k1);
		}
		if (k2==0)
		{
			Delay6ms();
			if (k2==0)
			{
				Close_Relay();
			}
			while(!k2);
		}		
	}
}

void Delay6ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 65;
	j = 136;
	do
	{
		while (--j);
	} while (--i);
}

void Close_Buzz()
{
	P2 = 0xA0;
	P0 = 0x00;
	P2 = 0x00;
}

void Oppen_Relay()
{	
	P0 = 0x10;
	P2 = 0xA0;
	_nop_();_nop_();
	_nop_();_nop_();
	P2 = 0x00;
}

void Close_Relay()
{
	P0 = 0x00;
	P2 = 0xA0;
	_nop_();_nop_();
	_nop_();_nop_();
	P2 = 0x00;
}
