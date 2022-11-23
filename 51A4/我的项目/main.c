#include "reg52.h"

sbit led1=P2^0;
sbit led2=P2^1;

void delay500us(void)   //Îó²î 0us
{
    unsigned char a,b;
    for(b=99;b>0;b--)
        for(a=1;a>0;a--);
}

void main()
{
	while(1)
	{
		led1=0;
		delay500us();
		led1=1;
		delay500us();
		led2=0;
		delay500us();
		led2=1;

	}
}