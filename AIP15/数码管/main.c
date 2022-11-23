#include <STC15F2K60S2.H>
#include <intrins.h>

unsigned char data_pros[10] = {0xC0};

void delay()	//delay  @ 11.0592M
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 1;
	j = 5;
	k = 5;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}		

void display()
{
	
	P2=0xC0;
	P0=0x80;
	delay();
	P2=0xE0;
	//P0=0xFF;
	P0=0xC0;
	delay();
}

void main()
{
	
	while(1)
	{
		display();
		
	}
}