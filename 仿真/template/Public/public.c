#include "public.h"

void Delay1ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}

void Delay10us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 2;
	while (--i);
}

void DelayNms(u16 n)
{
    while(n--)
        Delay1ms();
}

void DelayN10us(u16 n)
{
     while(n--)
        Delay10us();
}
