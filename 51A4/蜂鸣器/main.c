#include <reg52.h>

sbit fmq=P1^5;

typedef unsigned int u16;
typedef unsigned char u8;

void delay500ms(void)   //无延迟
{
    unsigned char a,b,c;
    for(c=23;c>0;c--)
        for(b=152;b>0;b--)
            for(a=70;a>0;a--);
}


void delay(u16 i)
{
	while(i--);
}

void main()
{
	while(1)
	{
//		fmq=~fmq;
//		delay(10);
		
		fmq=1;
		delay(100);
		fmq=0;
		delay(100);
		fmq=1;
		delay(100);
		fmq=0;
		delay(50);
	}
}