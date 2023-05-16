#include <REGX51.H>
#include "intrins.h"

sbit LED1=P2^0;
sbit LED2=P2^1;

void Delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 205;
	k = 187;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void main()
{
	while(1)
	{
		LED1=0;
		LED2=0;
        Delay500ms();
        LED1=1;
		LED2=1;
        Delay500ms();
	}
}