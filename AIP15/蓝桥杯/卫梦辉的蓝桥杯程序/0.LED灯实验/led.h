#ifndef __LED_H__
#define __LED_H__
#include <STC15F2K60S2.H>

#define u8 unsigned char 
#define u16 unsigned int

	
void LED_Init(void);//LED�Ƴ�ʼ������������������Ϊ���������
void LED_One(u8 Lx);//����ָ��һ��LED�ƺ���
void LED_LSD1(u16 ms);//��������ˮ
void LED_LSD2(u16 ms);//���ҵ�����ˮ
void LED_HY(void);//������ˮ����
#endif
