#include "public.h"

void Delay_ms(unsigned int ms)
{
	unsigned char i, j;

	while (ms--)
	{
		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j)
				;
		} while (--i);
	}
}

void delay_10us(unsigned int us)
{
	unsigned char i;
	while (us--)
	{
		_nop_();
		i = 25;
		while (--i)
			;
	}
}

void delay_1us(unsigned int us)
{
	while (us--)
	{
		_nop_();
		_nop_();
		_nop_();
	}
}
