#ifndef __DS18B20_H__
#define __DS18B20_H__
#include <STC15F2K60S2.H>
#include "intrins.h"

//#define uchar unsigned char
//#define uint unsigned int

sbit DS18B20_DQ =P1^4;//����DS18B20��Ƭ�����ݲɼ�����

char DS18B20_Reset();//DS18B20��λ
void DS18B20_WriteData(unsigned char dat);//��DS18B20д����
unsigned char DS18B20_ReadData();//��DS18B20������
float DS18B20_Tem();//DS18B20�����¶�ֵ����

#endif