#ifndef __LCD1602_H__
#define __LCD1602_H__
#include <STC15F2K60S2.H>
#include <stdio.h>

/**********************************
��ʹ�õ���4λ���ݴ����ʱ���壬
ʹ��8λȡ���������
**********************************/
//#define LCD1602_4PINS

//---�ض���ؼ���---//
#define uchar unsigned char
#define uint unsigned int

/**********************************
PIN�ڶ���
**********************************/
sbit LCD1602_E=P1^2;
sbit LCD1602_RW=P2^1;
sbit LCD1602_RS=P2^0;

#define LCD1602_DATAPINS P0


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

void DisplayOneChar(uchar X, uchar Y, uchar DData);//��ʾ�����ַ�
void DisplayListChar(uchar X, uchar Y, uchar *DData);//��ʾ�ַ���
void Display_XS(uchar X, uchar Y,float XS,uchar XS_wei);//��ʾָ��С����

void LCD1602_test(void);//LCD1602���Գ���

#endif
