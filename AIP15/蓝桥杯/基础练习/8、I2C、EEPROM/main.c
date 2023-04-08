#include <STC15F2K60S2.h>
#include <intrins.h>

#include "iic.h"
#include "EEPROM.h"
#include "led.h"

void Close_Buzz();

void main()
{
	unsigned char temp = 0; 
	Close_Buzz();
	Write_EEPROM(0x00,1);
	temp = Read_EEPROM(0x00);
	while(1)
	{
		Display(temp);	
	}
}

void Close_Buzz()
{
	P0 = 0x00;
	P2 = 0xA0;
	_nop_();
	_nop_();
	P2 = 0x00;	
}