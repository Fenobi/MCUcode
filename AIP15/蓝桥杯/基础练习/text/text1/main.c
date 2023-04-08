#include <STC15F2K60S2.h>
#include <intrins.h>
#include "DS18B20.h"

unsigned char data_pros[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};


void DS(unsigned char yi,unsigned char er);


void main()
{
	unsigned char temper,yi,er;
	P2 = 0xA0; P0 = 0x00; P2 = 0x00;
	while(1)
	{
		temper = read_T();
		yi = temper/10;
		er = temper%10;
		DS(yi,er);
	}
}



void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

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

void DS(unsigned char yi,unsigned char er)
{	
		P2 = 0xC0;
		P0 = 0x40;	
		P2 = 0xE0;
		P0 = data_pros[yi];	
		Delay1ms();
		P2 = 0x00;
		
		P2 = 0xC0;
		P0 = 0x80;		
		P2 = 0xE0;
		P0 = data_pros[er];	
		Delay1ms();
		P2 = 0x00;
}