#ifndef __KEY_H__
#define __KEY_H__
#include <STC15F2K60S2.H>

sbit S4=P3^3;//����������������
sbit S5=P3^2;
sbit S6=P3^1;
sbit S7=P3^0;

char DL_key1(void);//�򵥵Ķ�����������

char JZ_key(void);//���󰴼���������(���ض�Ӧ��ֵ)

#endif