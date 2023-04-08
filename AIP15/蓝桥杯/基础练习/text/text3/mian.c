#include <STC15F2K60S2.h>
#include <DS1302.h>
unsigned char tab[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}


void DS(unsigned char yi,unsigned char er)
{
	P2 = 0xC0;
	P0 = 0x40;
	P2 = 0xE0;
	P0 = tab[yi];
	Delay1ms();
	P2 = 0x00;
	
	P2 = 0xC0;
	P0 = 0x80;
	P2 = 0xE0;
	P0 = tab[er];
	Delay1ms();
	P2 = 0x00;	
}

void main()
{
	unsigned char temp,yi,er;
	P2 = 0xA0; P0 = 0x00; P2 = 0x00;
	Init_Time();
	while(1)
	{
		temp = Read_DS(0x81);
		yi = temp>>4;
		er = temp&0x0F;
		DS(yi,er);
	}	
}

