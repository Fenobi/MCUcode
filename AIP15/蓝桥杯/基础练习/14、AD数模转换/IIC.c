#include "IIC.h"

void Delay1us()		//@11.0592MHz
{
	_nop_();
	_nop_();
	_nop_();
}


void iic_Start()
{
	SDA = 1;
	SCL = 1;
	Delay1us();
	Delay1us();
	Delay1us();
	Delay1us();
	Delay1us();
	SDA = 0;
	Delay1us();
	Delay1us();
	Delay1us();
	Delay1us();
	Delay1us();
	SCL = 0;
}

void iic_Stop()
{
	SDA = 0;	
	SCL = 1;
	Delay1us();
	Delay1us();
	Delay1us();
	Delay1us();	
	Delay1us();			
	SDA = 1;
	Delay1us();
	Delay1us();
	Delay1us();
	Delay1us();	
	Delay1us();			
}

void Send_ACK(bit ackbit)
{
	SCL = 0;
	SDA = ackbit;
	Delay1us();
	Delay1us();
	Delay1us();
	Delay1us();	
	Delay1us();
	SCL = 1;
	Delay1us();
	Delay1us();
	Delay1us();
	Delay1us();	
	Delay1us();
	SCL = 0;
	SDA = 1;
	Delay1us();
	Delay1us();
	Delay1us();
	Delay1us();	
	Delay1us();	
}

bit waitAck()
{
	bit ackbit;
	
	SCL = 1;
	Delay1us();
	Delay1us();
	Delay1us();
	Delay1us();	
	Delay1us();
	ackbit = SDA;
	SCL = 0;
	Delay1us();
	Delay1us();
	Delay1us();
	Delay1us();	
	Delay1us();
	return ackbit;
}

void Write_byte(unsigned char da)
{
	unsigned char i;
	for (i=0; i<8; i++)
	{
		SCL = 0;
		Delay1us();
		Delay1us();
		Delay1us();
		Delay1us();	
		Delay1us();			
		SDA = da&0x80;
		da <<= 1;
		Delay1us();
		Delay1us();
		Delay1us();
		Delay1us();	
		Delay1us();		
		SCL = 1;
		Delay1us();
		Delay1us();
		Delay1us();	
		Delay1us();
		Delay1us();
	}		
	SCL = 0;
}

unsigned char Read_byte()
{
	unsigned char i,temp;
	for (i=0; i<8; i++)
	{
		SCL = 1;
		Delay1us();
		Delay1us();
		Delay1us();	
		Delay1us();
		Delay1us();	
		temp <<= 1;
		temp = temp|SDA;
		SCL = 0;
		Delay1us();
		Delay1us();
		Delay1us();	
		Delay1us();
		Delay1us();			
	}
	return temp;
}


