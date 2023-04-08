#include <STC15F2K60S2.H>
#include "delay.h"//延时函数头文件
#include "TIMERx.h"//定时器函数头文件
#include "led.h"//led灯函数头文件

void main()
{
	
	LED_Init();//LED灯初始化函数（设置锁存器为跟随输出）
	
	TIM0_Init();//定时器0初始化函数
  TIM1_Init();//定时器1初始化函数
	TIM2_Init();//定时器2初始化函数
	while(1)
	{
		
	}
	
}
