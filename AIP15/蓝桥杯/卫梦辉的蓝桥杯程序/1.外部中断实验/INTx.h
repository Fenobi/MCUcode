#ifndef __INTX_H__
#define __INTX_H__
#include <STC15F2K60S2.H>

//���忴оƬ�Ĵ���INT_CLKO
#define EX2             0x10
#define EX3             0x20
#define EX4             0x40

void INT0_Init(void);//�ⲿ�ж�0��ʼ������
void INT1_Init(void);//�ⲿ�ж�1��ʼ������
void INT2_Init(void);//�ⲿ�ж�3��ʼ������
void INT3_Init(void);//�ⲿ�ж�3��ʼ������
void INT4_Init(void);//�ⲿ�ж�4��ʼ������

#endif
