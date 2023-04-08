#include "pcf8591.h"
#include "e2prom.h"
#include "smg.h"
#include "key.h"


u8 smg_display[8];
float VOL;
float VOL_set=0.0;
u8 u_flag = 1;
u8 p_flag = 0;
u8 n_flag = 0;
u8 t=1;

void n_display()
{
	
}

void u_display()
{
	u8 num;
	
	num = AD_read(0x43);
	VOL = num / 51.0;
	smg_display[5] = (u8)(VOL) % 10;
	smg_display[6] = (u16)(VOL * 100) / 10 % 10;
	smg_display[7] = (u16)(VOL * 100) % 10;

	display_wei(1);
	HC_138(7);
	P0 = 0xc1;
	Delay_ms(2);
	display_wei(6);
	display_1num(smg_display[5], 1);
	display_wei(7);
	display_1num(smg_display[6], 0);
	display_wei(8);
	display_1num(smg_display[7], 0);
	
}

void p_display()
{
	u8 butten,key_up,key_old,key_down,key_slow_down;
	if(key_slow_down) return ;
	
	smg_display[5] = (u8)(VOL_set) % 10;
	smg_display[6] = (u16)(VOL_set * 100) / 10 % 10;
	smg_display[7] = (u16)(VOL_set * 100) % 10;

	display_wei(1);
	HC_138(7);
	P0 = 0x8c;
	Delay_ms(2);
	display_wei(6);
	display_1num(smg_display[5], 1);
	display_wei(7);
	display_1num(smg_display[6], 0);
	display_wei(8);
	display_1num(smg_display[7], 0);
	butten=Key_KBD_Read(0);
	key_up=butten&(butten^key_old);
	key_down=~butten&(butten^key_old);
	key_old=butten;
	if (butten == 16)
	{
		VOL_set += 0.5;
		
		if(VOL_set>5.0)
		{
			VOL_set = 0.0;
		}
	}
	else if(butten == 17)
	{
		VOL_set -= 0.5;
		if (VOL_set < 0.0)
		{
			VOL_set = 5.0;
		}
	}
	
}

void main()
{
	u8 butten;
	while(1)
	{
		butten=Key_KBD_Read(0);
		if(butten==12)
		{
			++t;
			if(t>4)
			{
				t=1;
			}
		}
		if(t==1)
			u_display();
		else if(t==2)
			p_display();
		else if(t==3)
			;
	}
	
}