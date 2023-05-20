#ifndef __IIC_LCD12864_H__
#define __IIC_LCD12864_H__
#include <STC15F2K60S2.H>
#include "intrins.h"
#include "stdio.h"


#define uchar unsigned char
#define uint unsigned int
	

void LCD12864_delay_ms(uint ms);//������ʱ����12MHZ������
void oled_clear(void);//����
void oled_on(void);//������ʾ
void oled_showchar(uchar x,uchar y,uchar chr,uchar char_size);//��ʾһ���ַ���x:0-127,y:0-63,size�����壬Ĭ����16����
void oled_drawbmp(uchar x0,uchar y0,uchar x1,uchar y1,uchar bmp[]);//��ͼ


void oled_init(void);//��ʼ��ssd1306
void oled_showstring(uchar x,uchar y,uchar *chr,uchar char_size);//��ʾһ���ַ���
void OLED_Display_Num(uchar x,uchar y,int num);//��ʾС����������
void OLED_Display_NumPint(uchar x,uchar y,float Point);//��ʾС��С������
void oled_shownum(uchar x,uchar y,uint num,uchar len,uchar size2);//x,y:����,num��ֵ,lenλ��,size2�����壬Ĭ����16����
void oled_showchinese(uchar x,uchar y,uchar no);//��ʾ����,x yΪ���꣬noΪ���

int Test_LCD12864(void);//LCD12864���Գ���

#endif