#ifndef __USART_H__
#define __USART_H__
#include <STC15F2K60S2.H>


void Init_Uart();//���ڳ�ʼ������
void SendByte(unsigned char dat);//���ڷ���һ���ֽ�
void SendString(unsigned char *str);//���ڷ���һ���ַ���
#endif