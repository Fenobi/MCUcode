#include <STC15F2K60S2.H>
#include "delay.h"//延时函数头文件
#include "Buzz_Relay.h"//继电器与蜂鸣器函数头文件


void main()
{
	
	while(1)
	{
		
		BUZZ(1);//蜂鸣器打开
		Delay_ms(500);
		BUZZ(0);//蜂鸣器关闭
		Delay_ms(500);
		
		RELAY(1);//继电器打开
		Delay_ms(500);
		RELAY(0);//继电器关闭
		Delay_ms(500);
		
	}
}
