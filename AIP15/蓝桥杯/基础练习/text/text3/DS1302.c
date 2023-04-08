#include <STC15F2K60S2.h>

sbit SCLK = P1^7;
sbit DA = P2^3;
sbit RST = P1^3;

void Write_Byte(unsigned char dat)
{
	unsigned char i;
	for(i=0; i<8; i++)
	{
		SCLK = 0;
		DA = dat&0x01;
		dat >>= 1;
		SCLK = 1;
	}
}

unsigned char Read_Byte()
{
	unsigned char i,dat;
	for(i=0; i<8; i++)
	{
		SCLK = 0;
		dat >>= 1;
		if (DA)
		{
			dat |= 0x80;
		}
		SCLK = 1;
	}	
	return dat;
}

void Write_DS(unsigned char addr,unsigned char dat)
{
	RST = 0;
	SCLK = 0;
	RST = 1;
	
	Write_Byte(addr);
	Write_Byte(dat);
	
	RST = 0;
}

unsigned char Read_DS(unsigned char addr)
{
	unsigned char dat;
	RST = 0;
	SCLK = 0;
	RST = 1;
	
	Write_Byte(addr);
	dat = Read_Byte();
	
	RST = 0;
	SCLK = 0;
	SCLK = 1;
	DA = 0;
	DA = 1;
	return dat;
}

void Init_Time()
{
	Write_DS(0x80,0x00);
}