#include <STC15F2K60S2.H>
#include "delay.h"
#include "INTx.h"
#include "led.h"//led灯函数头文件


void main()
{
	//LED初始化
	LED_Init();//LED灯初始化函数（设置锁存器为跟随输出）
	
	//单片机初始化
	INT0_Init();//外部中断0初始化函数
//	INT1_Init();//外部中断1初始化函数
//	INT2_Init();//外部中断3初始化函数
//	INT3_Init();//外部中断3初始化函数
//	INT4_Init();//外部中断4初始化函数

	while(1)
	{
	}
}


