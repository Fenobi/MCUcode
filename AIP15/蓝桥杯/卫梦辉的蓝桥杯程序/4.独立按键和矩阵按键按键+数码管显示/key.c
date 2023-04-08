#include "key.h"//按键函数头文件
#include "delay.h"//延时函数头文件

//简单的独立按键函数(返回对应键值)
char DL_key1(void)
{
	if(S4==0)//按键S7
	{
		Delay_ms(5);//延时消抖
		if(S4==0)
			return 1;//还回值1
	}	
	else if(S5==0)//按键S6
	{
		Delay_ms(5);//延时消抖
		if(S5==0)
			return 2;//还回值2
	}
	
	else if(S6==0)//按键S5
	{
		Delay_ms(5);//延时消抖
		if(S6==0)
			return 3;//还回值3
	}
	else	if(S7==0)//按键S4
	{
		Delay_ms(5);//延时消抖
		if(S7==0)
			return 4;//还回值4
	}
	return 0;//当没有按键按下时还回值为0
}

//复杂的独立按键函数
void DL_key2()
{
	
}


//矩阵按键驱动函数(返回对应键值)
char JZ_key(void)
{
	char key_value = 0;
	
	P34 = 1;P35 = 1;P42 = 1;P44 = 1;//将矩阵按键的列GPIO拉高,以便读取引脚电平
	P30 = 0;P31 = 0;P32 = 0;P33 = 0;//将矩阵按键的行GPIO拉低,以便被读取低电平
	
	//列扫描
	if ((P34 == 0) || (P35 == 0) || (P42 == 0) || (P44 == 0))
	{
		Delay_ms(5);//延时消抖
		if ((P34 == 0) || (P35 == 0) || (P42 == 0) || (P44 == 0))
		{
			if(P34 == 0){key_value=4;}
			else	if(P35 == 0){key_value=3;}
			else	if(P42 == 0){key_value=2;}
			else	if(P44 == 0){key_value=1;}			
		}
	}
	
	P34 = 0;P35 = 0;P42 = 0;P44 = 0;//将矩阵按键的列GPIO拉低,以便被读取低电平
	P30 = 1;P31 = 1;P32 = 1;P33 = 1;//将矩阵按键的行GPIO拉高,以便读取引脚电平
	
	//行扫描
	if ((P30 == 0) || (P31 == 0) || (P32 == 0) || (P33 == 0))
	{
		Delay_ms(5);//延时消抖
		if ((P30 == 0) || (P31 == 0) || (P32 == 0) || (P33 == 0))
		{
			if(P30 == 0){key_value+=0;}
			else	if(P31 == 0){key_value+=4;}
			else	if(P32 == 0){key_value+=8;}
			else	if(P33 == 0){key_value+=12;}			
		}
	}
	return key_value;
}
