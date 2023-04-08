#include <STC15F2K60S2.H>
#include "delay.h"//延时函数头文件
#include "TIMERx.h"//定时器函数头文件
#include "led.h"//led灯函数头文件
#include "smg.h"//数码管函数头文件
#include "Buzz_Relay.h"//继电器与蜂鸣器函数头文件
#include "PCF8591.h"//PCF8591芯片A/D D/A转换函数头文件


sbit S6=P3^1;//按键
sbit S7=P3^0;
sbit L1=P0^0;


void main()
{
	char mode=0;
	unsigned char ADC;
	
	RELAY(0);//关闭继电器和蜂鸣器
	TIM0_Init();//定时器0初始化函数

	while(1)
	{
		if(S7==0)//开始出水
		{
			mode= 0;
			TR0 = 1;		//使能定时器0中断
			Water_L=0;
			RELAY(1);//打开继电器
		}
		if(S6==0)//暂停出水
		{
			mode= 1;
			TR0 = 0;		//使能定时器0中断
			RELAY(0);//关闭继电器
		}
		
		switch(mode)
		{
			case 0://模式零显示升
				Display_water(Water_L);//显示升程序	
			if(Water_L>=99.99)
			{
				mode=1;
				RELAY(0);//关闭继电器
			}
			break;
			case 1://模式一显示价格
				Display_water(Water_L*0.5);//计算并显示金额程序	
			break;
		}
		
		ADC = PCF8591_Read(AIN1);//返回PCF8591芯片ADC转换值
		if(ADC<64)
		{
			P25=0;P27=1;P26=0;//打开Y4C锁存器			使用这个程序效果完全不一样,   P27=1;P26=0;P25=0;
			L1=0;
			P27=0;P26=0;P25=0;
		}
		else
		{
			P25=0;P27=1;P26=0;//打开Y4C锁存器			使用这个程序效果完全不一样,   P27=1;P26=0;P25=0;
			L1=1;
			P27=0;P26=0;P25=0;
		}
		
	}
}
