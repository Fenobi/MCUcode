#include "reg52.h"
#include "intrins.h"

typedef unsigned int u16;
typedef unsigned char u8;

sbit relay=P1^0;

int main()
{
	relay=0;
	while(1)
	{
		//beep=~beep;
		//delay(10);
	}
	return 0;
}