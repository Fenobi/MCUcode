#include "public.h"

void Delay10us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 27;
	while (--i);
}

void Delay1ms(u16 n)		//@12.000MHz
{
	unsigned char i, j;
	while(n--)
	{
		i = 12;
		j = 169;
		do
		{
			while (--j);
		} while (--i);
	}
}

