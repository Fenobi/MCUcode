#ifndef __USART_H__
#define __USART_H__
#include <STC15F2K60S2.H>

extern unsigned char Rdata_flag;//�ַ���������ɱ�־���������Rdata_flag��1��
extern unsigned char R_data[15];//���ջ�������

void Init_Uart();//���ڳ�ʼ������
void SendByte(unsigned char dat);//���ڷ���һ���ֽ�
void SendString(unsigned char *str);//���ڷ���һ���ַ���
#endif