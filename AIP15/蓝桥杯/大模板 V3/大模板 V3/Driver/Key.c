#include <Key.h>

/* 
		函数名称：矩阵键盘读取函数
		函数说明：读取当前按键的键码值
		入口参数：无
		返回数据：按键键码值
*/
unsigned char Key_KBD_Read()
{
	unsigned char temp = 0;
	
	AUXR &= 0xEF; //关闭T2R 即 定时器2 （串口波特率发生所用的定时器）
	
	P44 = 0;P42 = 1;P35 = 1;P34 = 1;
	if(P33 == 0) temp = 4;
	if(P32 == 0) temp = 5;
	if(P31 == 0) temp = 6;
	if(P30 == 0) temp = 7;

	P44 = 1;P42 = 0;P35 = 1;P34 = 1;
	if(P33 == 0) temp = 8;
	if(P32 == 0) temp = 9;
	if(P31 == 0) temp = 10;
	if(P30 == 0) temp = 11;
	
	P44 = 1;P42 = 1;P35 = 0;P34 = 1;
	if(P33 == 0) temp = 12;
	if(P32 == 0) temp = 13;
	if(P31 == 0) temp = 14;
	if(P30 == 0) temp = 15;
	
	P44 = 1;P42 = 1;P35 = 1;P34 = 0;
	if(P33 == 0) temp = 16;
	if(P32 == 0) temp = 17;
	if(P31 == 0) temp = 18;
	if(P30 == 0) temp = 19;
	
	P3 = 0xff;
	AUXR |= 0x10; //打开T2R 即 定时器2 （串口波特率发生所用的定时器）
	
	return temp;
}


/* 
		函数名称：独立键盘读取函数
		函数说明：读取当前按键的键码值
		入口参数：无
		返回数据：按键键码值
*/
unsigned char Key_BTN_Read()
{
	unsigned char temp = 0;
	
	AUXR &= 0xEF; //关闭T2R 即 定时器2 （串口波特率发生所用的定时器）
	
	if(P33 == 0) temp = 4;
	if(P32 == 0) temp = 5;
	if(P31 == 0) temp = 6;
	if(P30 == 0) temp = 7;

	P3 = 0xff;
	AUXR |= 0x10; //打开T2R 即 定时器2 （串口波特率发生所用的定时器）	
	return temp;
}