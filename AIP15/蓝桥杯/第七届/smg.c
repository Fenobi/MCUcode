#include "smg.h"

u8 SMG_DISPLAY_WEI[9]={0,1,2,4,8,16,32,64,128};
u8 SMG_DISPLAY_NUM[13] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x7f, 0xbf, 0xc6};

void HC138(u8 num)
{
	switch(num)
	{
		case 0:LA=0;LB=0;LC=0;break;
		case 1:LA=1;LB=0;LC=0;break;
		case 2:LA=0;LB=1;LC=0;break;
		case 3:LA=1;LB=1;LC=0;break;
		case 4:LA=0;LB=0;LC=1;break;
		case 5:LA=1;LB=0;LC=1;break;
		case 6:LA=0;LB=1;LC=1;break;
		case 7:LA=1;LB=1;LC=1;break;
	}
}

void smg_display_wei(u8 wei)
{
	P0=SMG_DISPLAY_WEI[wei];
}

void smg_dispaly_num(u8 num)
{
	P0=SMG_DISPLAY_NUM[num];
}

void smg_dispaly_fore_num(u16 num)
{
	if(num>=0&&num<100)
	{
		HC138(6);
		smg_display_wei(5);
		HC138(7);
		smg_dispaly_num(0);
		Delay_ms(2);
		
		HC138(6);
		smg_display_wei(6);
		HC138(7);
		smg_dispaly_num(0);
		Delay_ms(2);
		
		HC138(6);
		smg_display_wei(7);
		HC138(7);
		smg_dispaly_num(num/10);
		Delay_ms(2);
		
		HC138(6);
		smg_display_wei(8);
		HC138(7);
		smg_dispaly_num(num%10);
		Delay_ms(2);
	}
	else if(num>=100&&num<1000)
	{
		HC138(6);
		smg_display_wei(5);
		HC138(7);
		smg_dispaly_num(0);
		Delay_ms(2);
		
		HC138(6);
		smg_display_wei(6);
		HC138(7);
		smg_dispaly_num(num/100);
		Delay_ms(2);
		
		HC138(6);
		smg_display_wei(7);
		HC138(7);
		smg_dispaly_num(num/10%10);
		Delay_ms(2);
		
		HC138(6);
		smg_display_wei(8);
		HC138(7);
		smg_dispaly_num(num%10);
		Delay_ms(2);
	}
	else if(num>=1000)
	{
		HC138(6);
		smg_display_wei(5);
		HC138(7);
		smg_dispaly_num(num/1000);
		Delay_ms(2);
		
		HC138(6);
		smg_display_wei(6);
		HC138(7);
		smg_dispaly_num(num/100%10);
		Delay_ms(2);
		
		HC138(6);
		smg_display_wei(7);
		HC138(7);
		smg_dispaly_num(num/10%10);
		Delay_ms(2);
		
		HC138(6);
		smg_display_wei(8);
		HC138(7);
		smg_dispaly_num(num%10);
		Delay_ms(2);
	}
	else
	{
		;
	}
	
	
	
}

