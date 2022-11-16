#include <reg52.h>

sbit led1=P2^0;
sbit led2=P2^1;
sbit led3=P2^2;
sbit led4=P2^3;

typedef unsigned char u8;
typedef unsigned int u16;



void delay(void)   
{
	unsigned char a,b,c;
	for(c=19;c>0;c--)
		for(b=20;b>0;b--)
			for(a=130;a>0;a--);
}

void main()
{
		while(1)
		{
			led1=0;
			delay();
			
			led2=0;
			delay();
			
			led3=0;
			delay();
			
			led4=0;
			delay();
			
			led1=1;
			delay();
			
			led2=1;
			delay();
			
			led3=1;
			delay();
			
			led4=1;
			delay();
		}
}