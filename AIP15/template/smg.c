#include "smg.h"

u8 addr_arr[8]={1,2,4,8,16,32,64,128};
u8 num_arr[13]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0x88};

void smg_display(u8 addr,u8 num,u8 point)
{
	P0 = 0XFF;
	P2 = 0X1F & P2 | 0XE0;
	P2 &= 0X1F;
	
	P0=addr_arr[addr];
	P2 = P2 & 0x1f | 0xc0;
	P2 &= 0x1f;
	
	P0=num_arr[num];
	if(point)
		P0 &= 0X7f;
	P2 = P2 & 0x1f | 0xe0;
	P2 &= 0x1f;
}
