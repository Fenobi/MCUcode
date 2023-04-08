#include <STC15F2K60S2.h>
#include <intrins.h>

sbit DQ = P1^4;

void Delay500us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 6;
	j = 93;
	do
	{
		while (--j);
	} while (--i);
}

void Delay60us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 1;
	j = 162;
	do
	{
		while (--j);
	} while (--i);
}

void Delay1us()		//@11.0592MHz
{
	_nop_();
	_nop_();
	_nop_();
}

bit Init_DS18B20()
{
	bit DSACK;
	DQ = 1;
	Delay1us();
	DQ = 0;
	Delay500us();
	DQ = 1;
	Delay60us();
	DSACK = DQ;
	DQ = 1;
	Delay500us();
	return DQ;
}

void write_byte(unsigned char da)
{
	unsigned char i;
	for (i=0; i<8; i++)
	{
		DQ = 0;
		Delay1us();
		DQ = da&0x01;
		Delay60us();
		da >>=1;		
		DQ = 1;
		Delay1us();
	}
	Delay60us();
}

unsigned char Read_byte()
{
	unsigned char i,temp;
	for (i=0; i<8; i++)
	{
		DQ = 0;
		Delay1us();
		temp >>= 1;
		DQ = 1;
		Delay1us();
		if (DQ)
		{
			temp |= 0x80;
		}
		Delay60us();
	}	
	DQ = 0;
	return temp;
}

unsigned char read_T()
{
	unsigned char low,high,THEtemper;
	Init_DS18B20();
	write_byte(0xCC);
	write_byte(0x44);
	Init_DS18B20();
	write_byte(0xCC);
	write_byte(0xBE);
	
	low = Read_byte();
	high = Read_byte();
	THEtemper = low>>4;
	THEtemper |= (high<<4);
	return THEtemper;
}