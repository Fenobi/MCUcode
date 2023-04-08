#ifndef __USART_H__
#define __USART_H__
#include <STC15F2K60S2.H>

extern unsigned char Rdata_flag;//字符串接收完成标志（接收完成Rdata_flag置1）
extern unsigned char R_data[15];//接收缓存数组

void Init_Uart();//串口初始化函数
void SendByte(unsigned char dat);//串口发送一个字节
void SendString(unsigned char *str);//串口发送一个字符串
#endif