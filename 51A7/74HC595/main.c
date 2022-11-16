#include "74HC595.h"

u8 hc595_buf[9]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0xFF};

//u8 t[9]={0x7F,0xBF,0xDF,0xBF,0XF7,0xFB,0xFD,0xFE,0xFF};

void main()
{
	
	while(1)
	{
		u8 i=0;
		for(i=0;i<8;i++)
		{
			HC595_write_data(0,0,0,0);
			HC595_write_data(hc595_buf[i],0,0,0);
			delay_n10us(5000);
		}
		for(i=0;i<8;i++)
		{
			HC595_write_data(0,0,0,0);
			HC595_write_data(0,hc595_buf[i],0,0);
			delay_n10us(5000);
		}
		
	}
}