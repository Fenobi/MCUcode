#include<STC15F2K60S2.h>

//定义独立按键
sbit S0 = P3^0;
sbit S1 = P3^1;
sbit S2 = P3^2;
sbit S3 = P3^3;

void cls_buzz()
{
	P2 = (P2&0x1f|0xa0);
	P0 = 0x00;
	P2 = 0x1f; 
}

void main()
{
	cls_buzz();	
	P2 = 0x80;
	P0 = 0xff;	
	
	while(1)
	{
		if (0 == S0)
		{	
			P0 = 0xff;
			P0 = 0x7f;
		}
		if (0 == S1)
		{
			P0 = 0xff;
			P0 = 0xbf;
		}
		if (0 == S2)
		{
			P0 = 0xff;
			P0 = 0xdf;
		}
		if (0 == S3)
		{
			P0 = 0xff;
			P0 = 0xef;
		}
	}
}