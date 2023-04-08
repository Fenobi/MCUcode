#include <STC15F2K60S2.h>
#include <onewire.h>

unsigned char data_pros[10] = {0xc0, 0xf9, 0xa4, 0xb0, 
																0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

void DS(unsigned char yi, unsigned char er);

void main()
{
	unsigned char i,j, temper;
	P2 = 0xA0; P0 = 0x00; P2 = 0x00;
	ReadROM();
	while (1)
	{
		temper = read_T();

		i = temper/10;
		j = temper%10;
		DS(i,j);
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

void DS(unsigned char yi, unsigned char er)
{
	P2 = 0xC0;
	P0 = 0x40;
	P2 = 0xE0;
	P0 = data_pros[yi];
	Delay1ms();

	P2 = 0xC0;
	P0 = 0x80;
	P2 = 0xE0;
	P0 = data_pros[er];
	Delay1ms();
	P2 = 0x00;	
	
}