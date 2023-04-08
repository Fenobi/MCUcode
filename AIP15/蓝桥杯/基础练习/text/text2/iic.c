#include <STC15F2K60S2.h>
#include <intrins.h>

sbit SCL = P2^0;
sbit SDA = P2^1;

void Delay5us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 11;
	while (--i);
}


void iic_Start()
{
	SDA = 1;
	SCL = 1;
	Delay5us();
	SDA = 0;
	Delay5us();
	SCL = 0;
}

void iic_Stop()
{
	SDA = 0;
	SCL = 1;
	Delay5us();
	SDA = 1;
	Delay5us();
}

void write_byte(unsigned char da)
{
	unsigned char i;
	for (i=0; i<8; i++)
	{
		SCL = 0;
		if(da & 0x80) SDA  = 1;
    else SDA  = 0;
		Delay5us();
		SCL = 1;
		da <<= 1;
		Delay5us();
	}
	SCL = 0;
}

unsigned char Read_Byte()
{
	unsigned char i,da;
	for (i=0; i<8; i++)
	{
	
		SCL = 1;
		Delay5us();
		da <<= 1;
		if (SDA)
		{
			da |= 0x01;
		}
		SCL = 0;
		Delay5us();
	}
	return da;
}

void SendAck()
{
	SCL = 0;
	SDA = 0;
	Delay5us();
	SCL = 1;
	Delay5us();
	SCL = 0;
	SDA = 1;
	Delay5us();
}

bit witeACK()
{
	bit ackbit;
	SCL = 1;
	Delay5us();
	ackbit = SDA;
	SCL = 0;
	Delay5us();
	return ackbit;
}

void Write_EEPROM(unsigned char da)
{
	iic_Start();
	write_byte(0xA0);
	witeACK();
	write_byte(0x00);
	witeACK();
	write_byte(da);
	witeACK();
	iic_Stop();
}

unsigned char Read_EEPROM(unsigned char addr)
{
	unsigned char temp;
	iic_Start();
	write_byte(0xA0);
	witeACK();
	write_byte(addr);
	witeACK();
	iic_Start();
	write_byte(0xA1);
	witeACK();
	temp = Read_Byte();
	iic_Stop();
	return temp;
}