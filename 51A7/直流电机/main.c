#include <REGX52.H>

sbit A=P1^0;

void delay1ms(void)
{
    unsigned char a,b;
    for(b=102;b>0;b--)
        for(a=3;a>0;a--);
}

void delay_nms(unsigned int x)
{
	while(x--)
	{
		delay1ms();
	}
}

void delay5s(void)   //误差 -0.000000001137us
{
    unsigned char a,b,c;
    for(c=179;c>0;c--)
        for(b=220;b>0;b--)
            for(a=57;a>0;a--);
}

void main()
{
	A=1;
	delay5s();
	while(1)
	{
		A=0;
	}
	
}