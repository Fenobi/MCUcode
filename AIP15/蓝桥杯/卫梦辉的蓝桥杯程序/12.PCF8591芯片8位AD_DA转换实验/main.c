#include <STC15F2K60S2.h>
#include "smg.h"//数码管函数头文件
#include "PCF8591.h"//PCF8591芯片A/D D/A转换函数头文件


void main()
{
	int Digital;
	while(1)
	{
		
		//可调电阻
		Digital=PCF8591_Read(AIN3);
		Display_4_WEI(1,Digital);//数码管显示AD转换值（数码管左4位显示）
		
		
//*******以下代码打开一个，因为都是用数码管右4位显示，否则会有冲突，显示出错
		
		//1.光敏电阻 
		Digital=PCF8591_Read(AIN1);
		Display_4_WEI(5,Digital);//数码管显示AD转换值（数码管右4位显示）
		
		//2.运算放大器
//		Digital=PCF8591_Read(AIN2);
//		Display_4_WEI(5,Digital);//数码管显示AD转换值（数码管右4位显示）
		
		//3.排针(A/D)外接通道AIN0
//		Digital=PCF8591_Read(AIN0);
//		Display_4_WEI(5,Digital);//数码管显示AD转换值（数码管右4位显示）
	}
}
