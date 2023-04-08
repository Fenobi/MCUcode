#include<STC15F2K60S2.h>

void Close_Buzz()
{
	P2 = 0xA0;
	P0 = 0x00;
	P2 = 0x00;
}

void main()
{
	Close_Buzz();
	P2 = 0x80;
	P0 = 0xff;
	
	EX0 = 1;
	IT0 = 1;
	
	EA = 1;
	
	while(1);
}

void Interrupt() interrupt 0
{
	P2 = 0x80;
	P01 = ~P01;
}