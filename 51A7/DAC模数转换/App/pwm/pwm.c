#include "pwm.h"

u8 gtim_h=0;
u8 gtim_l=0;
u8 gtime_scale=0;
u8 gduty=0;

void pwm_init(u8 tim_h,u8 tim_l,u8 time_scale,u8 duty)
{
	gtim_h=tim_h;
	gtim_l=tim_l;
	gtime_scale=time_scale;
	gduty=duty;
	
	TMOD |= 0x01;			//设置定时器模式
	TL0 = gtim_l;			//设置定时初始值
	TH0 = gtim_h;			//设置定时初始值
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;
	EA = 1;
}

void pwm_set_duty_cycle(u8 duty)
{
	gduty=duty;
}

void pwm(void) interrupt 1
{
	static u16 time=0;
	TL0 = gtim_l;
	TH0 = gtim_h;	
	
	++time;
	if(time>=gtime_scale)
		time=0;
	if(time<=gduty)
		PWM=1;
	else
		PWM=0;
	
}