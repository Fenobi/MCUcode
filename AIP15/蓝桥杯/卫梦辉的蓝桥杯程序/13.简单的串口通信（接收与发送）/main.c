#include <STC15F2K60S2.h>
#include "delay.h"//��ʱ����ͷ�ļ�
#include "usart.h"//����ͨ�ź���ͷ�ļ�

void main()
{
	Init_Uart();	
	SendString("Welcome to Serial port! \r\n");//�����ַ���
	while(1)
	{
		SendByte('W');Delay_ms(500);//�����ַ�W
		SendByte('M');Delay_ms(500);//�����ַ�M
		SendByte('H');Delay_ms(500);//�����ַ�H
		SendString("\r\n");//���ͻ���
		Delay_ms(2000);//��ʱ���2s
	}
}
