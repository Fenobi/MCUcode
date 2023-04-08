#include "smg.h"

unsigned char Display_Digital[12]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x7f,0xbf};
unsigned char Display_WEI[9]={0,1,2,4,8,16,32,64,128};

void Delay1ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
}


void HC138(u8 num)
{
	switch(num)
	{
		case 0:LA=0;LB=0;LC=0;break;
		case 1:LA=0;LB=0;LC=1;break;
		case 2:LA=0;LB=1;LC=0;break;
		case 3:LA=0;LB=1;LC=1;break;
		case 4:LA=1;LB=0;LC=0;break;
		case 5:LA=1;LB=0;LC=1;break;
		case 6:LA=1;LB=1;LC=0;break;
		case 7:LA=1;LB=1;LC=1;break;
	}
}

void smg_wei(u8 wei)
{
	P0=Display_WEI[wei];
}

void smg_wei_num(u8 wei,u8 num)
{
	HC138(6);
	smg_wei(wei);
	HC138(7);
	P0=Display_Digital[num];
	Delay1ms();
	Delay1ms();
}

void Display_2_2Wei_XS(u8 wei,float num)
{
	num=num*100;//将小数扩大100倍
	smg_wei_num(wei, num/1000);//显示千位
	smg_wei_num(wei+1, (int)num%1000/100);//显示百位
	smg_wei_num(wei+2, (int)num%100/10);//显示十位
	smg_wei_num(wei+3, (int)num%10);//显示个位
}