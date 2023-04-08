#ifndef	__LCM12864_H
#define	__LCM12864_H
#include <STC15F2K60S2.H>
#include "stdio.h"

void LCD12864_Write_Data(unsigned char dat);//��12864��д������
void LCD12864_Write_Com(unsigned char com);//��12864��д������
extern void LCD12864_Init();//��LCD12864���г�ʼ��
extern void LCD12864_Display_Char(unsigned char x,unsigned char y,unsigned char dat);//��ʾ�����ַ�
extern void LCD12864_Display_Chars(unsigned char x,unsigned char y,unsigned char *dat);//��ʾ�ַ���
extern void LCD12864_Clear_Screen(unsigned char value);//������������ LCD12864_Clear_Screen(0xFF)ȫ��,LCD12864_Clear_Screen(0xFF)ȫ��
extern void LCD12864_ZS_display(unsigned char x,unsigned char y,unsigned int dat1);//��ʾ��������ֵ����
extern void LCD12864_XS_display(unsigned char x,unsigned char y,float num,unsigned char wei);//��ʾָ��λ��С������ֵ 

extern void LCD12864_Test();//LCD12864��ʾ���Գ���
extern void LCD12864_Clearn(unsigned char hang,unsigned char x1,unsigned char x2);//��ʾ����ֵ����

#endif