#include <STC15F2K60S2.h>
#include "delay.h"//延时函数头文件
#include "usart.h"//串口通信函数头文件

void main()
{
	Init_Uart();	
	SendString("Welcome to Serial port! \r\n");//发送字符串
	while(1)
	{
		SendByte('W');Delay_ms(500);//发送字符W
		SendByte('M');Delay_ms(500);//发送字符M
		SendByte('H');Delay_ms(500);//发送字符H
		SendString("\r\n");//发送换行
		Delay_ms(2000);//延时大概2s
	}
}
