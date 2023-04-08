#include "led.h"

void led_display(u8 addr,u8 can)
{
	static u8 temp=0x00;
	static u8 temp_old=0xff;
	if(can)
		temp |=0x01<<addr;
	else
		temp &=~0x01<<addr;
	if(temp!=temp_old)
	{
		P0=~temp;
		P2=P2 & 0x1f | 0x80;
		P2 &= 0x1f;
		temp_old=temp;
	}
}

void BUZZ(u8 can)
{
	static u8 temp=0x00;
	static u8 temp_old=0xff;
	if(can)
		temp |=0x40;
	else
		temp &=0x40;
	if(temp!=temp_old)
	{
		P0=~temp;
		P2=P2 & 0x1f | 0xa0;
		P2 &= 0x1f;
		temp_old=temp;
	}
}

void RELAY(u8 can)
{
	static u8 temp=0x00;
	static u8 temp_old=0xff;
	if(can)
		temp |=0x10;
	else
		temp &=~0x10;
	if(temp!=temp_old)
	{
		P0=temp;
		P2=P2 & 0x1f | 0xa0;
		P2 &= 0x1f;
		temp_old=temp;
	}
}