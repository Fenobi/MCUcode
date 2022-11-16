#include "smg.h"

u8 gamg_code[17] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f,
0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};//共阴0-F

void delay10us(u16 i)
{
	while(i--)
	{
		unsigned char a,b;
		for(b=1;b>0;b--)
			for(a=2;a>0;a--);
	}
}

void smg_display()
{
	u8 i=0;
	for(i=0;i<8;++i)
	{
		switch(i)
		{
			case 0:LSC = 1; LSB = 1; LSA = 1;
				break;
			case 1:LSC = 1; LSB = 1; LSA = 0;
				break;
			case 2:LSC = 1; LSB = 0; LSA = 1;
				break;
			case 3:LSC = 1; LSB = 0; LSA = 0;
				break;
			case 4:LSC = 0; LSB = 1; LSA = 1;
				break;
			case 5:LSC = 0; LSB = 1; LSA = 0;
				break;
			case 6:LSC = 0; LSB = 0; LSA = 1;
				break;
			case 7:LSC = 0; LSB = 0; LSA = 0;
				break;
		}
		SMG_A_DP_PORT = gamg_code[i];
		delay10us(10);
		SMG_A_DP_PORT = 0x00;
	}
}