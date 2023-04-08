#include <STC15F2K60S2.H>
#include "delay.h"//延时函数头文件
#include "led.h"//led灯函数头文件


void main()
{
	LED_Init();//LED灯初始化函数（设置控制LED的锁存器为跟随输出）
	while(1)
	{
		
		//实验程序1（LED灯闪烁）
		LED_One(1);//点亮L2灯
		Delay_ms(500);
		LED_One(0);//熄灭所有灯
		Delay_ms(500);
		
		
		//实验程序2 （led流水）
//		LED_LSD1(300);//从左到右流水
//		LED_LSD2(300);//从右到左流水
		
		
		//实验程序3  （一些花样）
//		LED_HY();//花样流水函数
		
		
	}
}
