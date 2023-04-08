#include "onewire.h"
#include <STC15F2K60S2.h>
unsigned char THEROM[8];
sbit DQ = P1^4;

void Delay1us()		//@11.0592MHz
{
	_nop_();
	_nop_();
	_nop_();
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

void InitDS18B20()
{
	DQ = 1;
	DQ = 0;
	Delay500us();
	DQ = 1;
	Delay500us();
}

void write_ds(unsigned char dat)
{
	unsigned char i;
	for (i=0; i<8; i++)
	{
		DQ = 0;
		Delay1us();
		DQ = dat&0x01;		
		Delay60us();
		DQ = 1;		
		dat >>= 1;
	}
}

unsigned char read_ds()
{
	unsigned char i,temp;
	for (i=0; i<8; i++)
	{
		DQ = 0;
		temp >>= 1;
		DQ = 1;
		Delay1us();
		if (DQ)
		{
			temp |= 0x80;
		}
		Delay60us();
	}
	return temp;
}

unsigned char read_T()
{
	unsigned char i;
	unsigned char high, low, temper;
	InitDS18B20();
	write_ds(0x55);
	for (i=0; i<8; i++)
	{
		write_ds(THEROM[i]);
	}
	write_ds(0x44);
	
	InitDS18B20();
	write_ds(0x55);
	for (i=0; i<8; i++)
	{
		write_ds(THEROM[i]);
	}
	write_ds(0xBE);
	low = read_ds();
	high = read_ds();
	
	temper = low>>4;
	temper |= high<<4;
	
	return temper;
}

void ReadROM()
{
	unsigned char i;
	InitDS18B20();
	write_ds(0x33);
	for (i=0; i<8; i++)
	{
		THEROM[i] = read_ds();
	}
}