#include "reg52.h"

sbit led1=P2^0;
sbit led2=P2^1;

void main()
{
	while(1)
	{
		led1=0;
		led2=0;

	}
}