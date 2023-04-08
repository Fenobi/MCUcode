#include "public.h"
#include "iic.h"
#include "onewire.h"
#include "led.h"
#include "smg.h"
#include "button.h"
#include "ds1302.h"

u8 smg_display_arr[]={10,10,10,10,10,10,10,10};
u8 smg_display_point_arr[]={0,0,0,0,0,0,0,0};
u8 led_display_arr[]={0,0,0,0,0,0,0,0};
u8 key_down,key_up,key_value,key_value_old;
u8 smg_addr,smg_slow_down;
u8 key_slow_down;
u8 smg_pos;
u16 hz;
u16 time=0;

void display()
{
	if(smg_slow_down) return;
	
	smg_display_arr[0]=1;
}

void key()
{
	if(key_slow_down) return;
	key_slow_down=1;
	key_value=key_addr_B();
	key_down=key_value & (key_value_old ^ key_value);
	key_up=~key_value & (key_value_old ^ key_value);
	key_value_old=key_value;
}

void led()
{
	led_display_arr[1]=1;
}

void Timer0_Isr() interrupt 1
{
	if(++smg_slow_down==500) smg_slow_down=0;
	if(++key_slow_down==10) key_slow_down=0;
	if(++smg_pos==8) smg_pos=0;
	smg_display(smg_pos,smg_display_arr[smg_pos],smg_display_point_arr[smg_pos]);
	led_display(smg_pos,led_display_arr[smg_pos]);
	if(++time==1000) time=0;
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
	System_Init();
	Timer0_Init();
	Timer1_Init();
	while(1)
	{
		display();
		key();
		led();
	}
}