#include <STC15F2K60S2.h>
#include <intrins.h>
#include "IIC.h"

unsigned char tab[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char dbuff[4];
unsigned char PCF8591_Read();
void Display();
void Delay1ms();
unsigned char wei = 0x80;

void main()
{
	unsigned char display;
	
	P2 = 0xA0;
	P0 = 0x00;
	P2 = 0x00;
	
	while(1)
	{
		display = PCF8591_Read();
		dbuff[3] = display/1000;
		dbuff[2] = display%1000/100;
		dbuff[1] = display%1000%100/10;
		dbuff[0] = display%1000%100%10;
		Display();
	}

}

unsigned char PCF8591_Read()
{
	unsigned char temp;
	iic_Start();
	Write_byte(0x90);
	waitAck();
	Write_byte(0x01);
	waitAck();
	iic_Start();
	Write_byte(0x91);
	waitAck();
	temp = Read_byte();
	Send_ACK(0);
	iic_Stop();
	return temp;
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


void Display()
{
	unsigned char i;
	for (i=0; i<4; i++)
	{
		P2 = 0xC0;
		P0 = wei>>i;
		P2 = 0x00;
		
		P2 = 0xE0;
		P0 = tab[dbuff[i]];
		Delay1ms();

		P2 = 0x00;
	}
}