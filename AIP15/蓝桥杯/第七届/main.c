#include "key.h"
#include "smg.h"
#include "ds18b20.h"

u8 work_mode;
u16 work_time1;
u16 time=0;

void tm1_isr() interrupt 1
{
	++time;
	if(time == 20)
	{
		time=0;
		if(work_time1==0)
		{
			work_time1=0;
		}
		else 
		{
			--work_time1;
		}
	}
}

void Timer0_Init(void)		//50毫秒@12.000MHz
{
	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0xB0;				//设置定时初始值
	TH0 = 0x3C;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
}

void temperature_display()
{
	int temp = 0; 
	
	HC138(6);
	smg_display_wei(1);
	HC138(7);
	P0=0xbf;
	Delay_ms(2);
	
	HC138(6);
	smg_display_wei(2);
	HC138(7);
	smg_dispaly_num(4);
	Delay_ms(2);
	
	HC138(6);
	smg_display_wei(3);
	HC138(7);
	P0=0xbf;
	Delay_ms(2);
	
	
	ds18b20_init();
	temp=ds18b20_read_temperture();
	
	HC138(6);
	smg_display_wei(6);
	HC138(7);
	smg_dispaly_num(temp/10);
	Delay_ms(2);
	
	HC138(6);
	smg_display_wei(7);
	HC138(7);
	smg_dispaly_num(temp%10);
	Delay_ms(2);
	
	HC138(6);
	smg_display_wei(8);
	HC138(7);
	smg_dispaly_num(12);
	Delay_ms(2);
	
}

void LED_display()
{
	HC138(4);
	if(work_mode==1)
	{
		P0=0xfe;
	}
	else if(work_mode==2)
	{
		P0=0xfd;
	}
	else if(work_mode==3)
	{
		P0=0xfb;
	}
}

void dispaly()
{
	LED_display();
	
	
	HC138(6);
	smg_display_wei(1);
	HC138(7);
	P0=0xbf;
	Delay_ms(2);
	
	HC138(6);
	smg_display_wei(2);
	HC138(7);
	smg_dispaly_num(work_mode);
	Delay_ms(2);
	
	HC138(6);
	smg_display_wei(3);
	HC138(7);
	P0=0xbf;
	Delay_ms(2);
	
	//smg_display_wei(4);
	smg_dispaly_fore_num(work_time1);
	Delay_ms(2);
}

void main()
{
	u8 key_num;
	u8 temp_flag=0;
	work_mode=1;
	work_time1=50;
	ET0 = 1;
	EA = 1;
	Timer0_Init();
//	while(1)
//	{
//		temperature_display();
//	}
	
	
	while(1)
	{
		key_num=key_scan(0);
		if(key_num==3)
		{
			work_time1+=60;
		}
		else if(key_num==4)
		{
			++work_mode;
			if(work_mode==4)
			{
				work_mode=1;
			}
		}
		else if(key_num==2)
		{
			work_time1=0;
		}
		else if(key_num==1)
		{
			temp_flag=~temp_flag;
		}
		if(temp_flag)
		{
			temperature_display();
		}
		else
		{
			dispaly();
		}
		
		
	}
}