#ifndef __CX20106_H__
#define __CX20106_H__
#include <STC15F2K60S2.h>
#include <intrins.h>

#define u8 unsigned char 
#define u16 unsigned int 
	
void Delay12us(void);//@11.0592MHz
void send_wave(void);//���Ͱ˶����岨(40Khz)
void CSB_Init(void);//������ģ���ʼ������
u16 Get_Distance(void);//������ģ���þ��뺯�����������ؾ���ֵ ��λ��cm��

#endif