#include <STC15F2K60S2.H>
#include "intrins.h"

void Delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 23;
	j = 205;
	k = 120;
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
        P00=0;
        Delay500ms();
        P00=1;
        Delay500ms();
    }
}