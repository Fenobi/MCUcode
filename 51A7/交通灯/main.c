#include <REGX51.H>

sbit LED1=P3^0;
sbit LED2=P3^1;

void main()
{
	while(1)
	{
		LED1=0;
		LED2=0;
	}
}