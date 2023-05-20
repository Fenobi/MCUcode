#ifndef __LCD1602_H__
#define __LCD1602_H__
#include <stdio.h>
#include "intrins.h"

/**********************************
��ʹ�õ���4λ���ݴ����ʱ���壬
ʹ��8λȡ���������
**********************************/
//#define LCD1602_4PINS

//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

/**********************************
PIN�ڶ���
**********************************/


/**********************************
��������
**********************************/
/*��51��Ƭ��12MHZʱ���µ���ʱ����*/
void Lcd1602_Delay1ms(uint c);   //��� 0us
/*LCD1602д��8λ�����Ӻ���*/
void LcdWriteCom(uchar com);
/*LCD1602д��8λ�����Ӻ���*/	
void LcdWriteData(uchar dat);
/*LCD1602��ʼ���ӳ���*/		
void LcdInit();						  

//		LcdWriteCom(0x01);  //����
void DisplayOneChar(uchar X, uchar Y, uchar DData);//��ʾ�����ַ�
void DisplayListChar(uchar X, uchar Y, uchar *DData);//��ʾ�ַ���
void Display_Num(uchar X, uchar Y, int num);//���������� ��Χ-32768~32767
void Display_NumPoint(uchar X, uchar Y, float decimal);//��С������ ��Χ

void LCD1602_test(void);//LCD1602���Գ���

#endif
