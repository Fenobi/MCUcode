#include "smg.h"
#include "led.h"
#include "key.h"
#include "iic.h"
#include "onewire.h"
#include "public.h"
#include "ds1302.h"

u8 smg_display_num_arr[]={10,10,10,10,10,10,10,10};
u8 smg_display_addr_arr[]={0,0,0,0,0,0,0,0};
u8 smg_display_point_arr[]={0,0,0,0,0,0,0,0};
u8 smg_slow_down;
u8 key_val,key_down,key_up,key_slow_down,key_old;
u8 led_display_arr[]={0,0,0,0,0,0,0,0};
u8 pos;
u8 time[] = {0, 0, 0};
u8 mode;
u8 work_mode;

u8 time_display_arr[]={23,25,0x00};
u8 time_flag;

float temperlate;
float temperlate_set;
float set_temp_ok;

u8 L3;
u8 L1;
u8 led_flag;

void key()
{
	if(key_slow_down) return;
	key_slow_down=1;
	
	key_val=key_val_B();
	key_down=key_val & (key_val ^ key_old);
	key_up=~key_val & (key_val ^ key_old);
	key_old=key_val;

	if(mode==2)
	{
		if(key_old==17)
		{
			time_flag=1;
		}
		else
			time_flag=0;
	}
	
	switch(key_down)
	{
		case 12:
			if(++mode==4) 
			{
				mode=1;
				set_temp_ok=temperlate_set;
			}
			break;
		case 13:
			work_mode ^= 1;
			break;
		case 16:
			if(mode==3)
				if(++temperlate_set>=99) temperlate_set=99;
			break;
		case 17:
			if(mode==3)
				if(--temperlate_set<=10) temperlate_set=10;
			break;
	}
}

void smg()
{
	if(smg_slow_down) return;
	smg_slow_down=1;

	temperlate = read_ds18b20_temperature();

	smg_display_num_arr[0] = 14;
	smg_display_num_arr[1] = mode;
	if(mode==1)
		smg_display_point_arr[6]=1;
	else
		smg_display_point_arr[6]=0;
	switch(mode)
	{
		case 1:
		smg_display_num_arr[3] = 10;
		smg_display_num_arr[4] = 10;
		smg_display_num_arr[5] = (u8)temperlate / 10;
		smg_display_num_arr[6] = (u8)temperlate % 10;
		smg_display_num_arr[7] = (u8)temperlate * 10 % 10;
		break;
		case 2:
		read_time_func(time_display_arr);
		smg_display_num_arr[3] = time_display_arr[0+time_flag] / 10;
		smg_display_num_arr[4] = time_display_arr[0+time_flag] % 10;
		smg_display_num_arr[5]=13;
		smg_display_num_arr[6] = time_display_arr[1+time_flag] / 10;
		smg_display_num_arr[7] = time_display_arr[1+time_flag] % 10;
		break;
		case 3:
		smg_display_num_arr[3] = 10;
		smg_display_num_arr[4] = 10;
		smg_display_num_arr[5] = 10;
		smg_display_num_arr[6] = (u8)temperlate_set / 10;
		smg_display_num_arr[7] = (u8)temperlate_set % 10;
	}
	
}

void led()
{
	if(work_mode==0)//温控模式
	{
		led_display_arr[1]=1;
		if(set_temp_ok<temperlate)
		{
			RELAY(1);
			led_display_arr[2]=L3;
		}
		else
			RELAY(0);
	}
	else
	{
		led_display_arr[1]=0;
		if(time_display_arr[1]==0 && time_display_arr[2]==0)
		{
			RELAY(1);
			led_display_arr[2]=L3;
		}
	}
	
}

void Timer0_Isr(void) interrupt 1
{
	if(++smg_slow_down==500) smg_slow_down=0;
	if(++key_slow_down==10) key_slow_down=0;
	
	if(++pos==8) pos=0;
	smg_display(pos,smg_display_num_arr[pos],smg_display_point_arr[pos]);
	led_display(pos,led_display_arr[pos]);
	if(++led_flag==100)
	{
		L3=~L3;
		led_flag=0;
	}
}

void Timer0_Init(void)		//1毫秒@12.000MHz
{
	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0x18;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;				//使能定时器0中断
	EA = 1;
}

void System_Init()
{
	P0 = 0xff;
	P2 = P2 & 0x1f | 0x80;
	P2 &= 0x1f;
	
	P0 = 0x00;
	P2 = P2 & 0x1f | 0xa0;
	P2 &= 0x1f;
}

void main()
{
	Timer0_Init();
	System_Init();
	BUZZ(1);
	read_ds18b20_temperature();
	Delay1ms(500);
	set_time_func(time_display_arr);
	mode=1;
	temperlate_set=23.0;
	set_temp_ok=23.0;
	
	while (1)
	{
		key();
		smg();
		led();
	}
}