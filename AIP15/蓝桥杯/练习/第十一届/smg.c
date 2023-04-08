#include "smg.h"

u8 smg_wei[9]={0,1,2,4,8,16,32,64,128};
u8 smg_num[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

void HC_138(u8 num)
{
	switch(num)
	{
		case 0:PA=0;PB=0;PC=0;break;
		case 1:PA=1;PB=0;PC=0;break;
		case 2:PA=0;PB=1;PC=0;break;
		case 3:PA=1;PB=1;PC=0;break;
		case 4:PA=0;PB=0;PC=1;break;
		case 5:PA=1;PB=0;PC=1;break;
		case 6:PA=0;PB=1;PC=1;break;
		case 7:PA=1;PB=1;PC=1;break;
	}
}

void display_wei(u8 wei)
{
	HC_138(6);
	P0=smg_wei[wei];
}

void display_1num(u8 num,u8 point)
{
	HC_138(7);
	switch(point)
	{
		case 0:
			P0=smg_num[num];
			break;
		case 1:
			P0 = smg_num[num] & 0x7f;
			break;
	}

	Delay_ms(2);
}