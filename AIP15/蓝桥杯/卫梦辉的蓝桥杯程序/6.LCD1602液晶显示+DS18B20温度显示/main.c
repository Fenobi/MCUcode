#include <STC15F2K60S2.H>
#include "delay.h"//延时函数头文件
#include "lcd1602.h"
#include "DS18B20.h"

void main()
{
	float Temp;	
	
	LcdInit(); //LCD1602初始化
	
	while(1)
	{
		Temp=DS18B20_Tem();//DS18B20返回温度值函数
		DisplayListChar(0, 0, "Temp:");
		Display_XS(5, 0,Temp,2);//显示指定小数。
		Delay_ms(300);//DS18B20温度转换需要延时一定时间
	}
}
