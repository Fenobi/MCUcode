#include <STC15F2K60S2.h>
#include <iic.h>
#include <intrins.h>
unsigned char data_pros[10] = {0xc0, 0xf9, 0xa4, 0xb0, 
																0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
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

void Delay1275us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 14;
	j = 180;
	do
	{
		while (--j);
	} while (--i);
}


void DS(unsigned char yi)
{
	P2 = 0xC0;
	P0 = 0x80;
	P2 = 0xE0;
	P0 = data_pros[yi];
	Delay1ms();
	P2 = 0x00;
}

void main()
{
	unsigned char i;
	P2 = 0xA0;
	P0 = 0x00;
	P2 = 0x00;
	Write_EEPROM(0x00,3);
	Delay1275us();
	i = Read_EEPROM(0x00);
	while(1)
	{	
		DS(i);
	}
}