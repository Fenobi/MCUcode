#include "smg.h"
#include "pcf8591.h"

void main()
{	
	u8 dat2;
	//u8 dat;
	u8 gsmg_code[6];
	u16 temp;
	while(1)
	{		
		dat=AD_read(0x41);//读光照强度
		dat2=AD_read(0x43);//读电压
		temp=dat2*197;
		gsmg_code[0]=temp/10000%10;
		gsmg_code[1]=temp/1000%10;
		gsmg_code[2]=temp/100%10;
		
		
		//gsmg_code[3]=dat/100%10;
		//gsmg_code[4]=dat/10%10;
		//gsmg_code[5]=dat%10;
		
		HC138_Y(6); 
		SMG_Display_Wei(2);
		HC138_Y(7); 
		SMG_Display_Digital(gsmg_code[0], 0);
		Delay_ms(2); 
		
		HC138_Y(6); 
		SMG_Display_Wei(3);
		HC138_Y(7); 
		SMG_Display_Digital(gsmg_code[1], 0);
		Delay_ms(2); 
		
		HC138_Y(6); 
		SMG_Display_Wei(4);
		HC138_Y(7); 
		SMG_Display_Digital(gsmg_code[2], 0);
		Delay_ms(2); 
		
		
		HC138_Y(6); 
		SMG_Display_Wei(6);
		HC138_Y(7); 
		SMG_Display_Digital(gsmg_code[3], 1);
		Delay_ms(2); 
		
		HC138_Y(6); 
		SMG_Display_Wei(7);
		HC138_Y(7); 
		SMG_Display_Digital(gsmg_code[4], 0);
		Delay_ms(2); 
		
		HC138_Y(6); 
		SMG_Display_Wei(8);
		HC138_Y(7); 
		SMG_Display_Digital(gsmg_code[5], 0);
		Delay_ms(2); 
		
	}		
}