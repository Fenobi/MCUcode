#include "LED.h"

void delay_n10us(u16 n)
{
	while(n--)
	{
		unsigned char a,b;
		for(b=1;b>0;b--)
			for(a=2;a>0;a--);
	}
    
}

void HC595_write_data(u8 dat1,u8 dat2,u8 dat3,u8 dat4)
{
	u8 i=0;
	for(i=0;i<8;i++)
	{
		SER=dat4>>7;
		dat4<<=1;
		SRCLK=0;
		_nop_();
		SRCLK=1;
		_nop_();
		
	}
	for(i=0;i<8;i++)
	{
		SER=dat3>>7;
		dat3<<=1;
		SRCLK=0;
		_nop_();
		SRCLK=1;
		_nop_();
		
	}
	for(i=0;i<8;i++)
	{
		SER=dat2>>7;
		dat2<<=1;
		SRCLK=0;
		_nop_();
		SRCLK=1;
		_nop_();
		
	}
	for(i=0;i<8;i++)
	{
		SER=dat1>>7;
		dat1<<=1;
		SRCLK=0;
		_nop_();
		SRCLK=1;
		_nop_();
		
	}
	rCLK=0;
	_nop_();
	rCLK=1;
	
}


