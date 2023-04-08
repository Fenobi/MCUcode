#ifndef __TIME_H__
#define __TIME_H__

#include <STC15F2K60S2.h>
#include <intrins.h>

//DS11302ʱ��оƬ��Ƭ����������
sbit SCLK = P1^7;//ʱ��
sbit DA = P2^3;//����
sbit RST = P1^3;//��λ

extern unsigned char Time[7];//����ʱ������

void Init_DS1302_Time();//��ʼ������DS1302оƬʱ�亯����������Time[7]�е�ʱ������д��DS1302оƬ��
void Read_DS1302_Time();//��ȡDS1302оƬʱ�亯������DS1302оƬ��ʱ������д������Time[7]�У�

#endif