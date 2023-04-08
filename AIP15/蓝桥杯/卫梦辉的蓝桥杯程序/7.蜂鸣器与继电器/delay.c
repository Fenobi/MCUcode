#include "delay.h"//延时函数头文件

//********************************WMH 2022.12.17
void Delay_ms(unsigned int ms)//@11.0592MHz
{
	unsigned char i, j;

	while(ms--)
	{
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
}



void delay_1us(unsigned int us)		//@11.0592MHz
{
	while(us--)
	{
		_nop_();
		_nop_();
		_nop_();
	}
}
