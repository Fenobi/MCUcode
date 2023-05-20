#ifndef __IIC_LCD12864_H__
#define __IIC_LCD12864_H__
#include <STC15F2K60S2.H>
#include "intrins.h"
#include "stdio.h"


#define uchar unsigned char
#define uint unsigned int
	

void LCD12864_delay_ms(uint ms);//毫秒延时函数12MHZ晶振下
void oled_clear(void);//清屏
void oled_on(void);//更新显示
void oled_showchar(uchar x,uchar y,uchar chr,uchar char_size);//显示一个字符，x:0-127,y:0-63,size是字体，默认填16就行
void oled_drawbmp(uchar x0,uchar y0,uchar x1,uchar y1,uchar bmp[]);//画图


void oled_init(void);//初始化ssd1306
void oled_showstring(uchar x,uchar y,uchar *chr,uchar char_size);//显示一个字符串
void OLED_Display_Num(uchar x,uchar y,int num);//显示小号整数数字
void OLED_Display_NumPint(uchar x,uchar y,float Point);//显示小号小数数字
void oled_shownum(uchar x,uchar y,uint num,uchar len,uchar size2);//x,y:坐标,num数值,len位数,size2是字体，默认填16就行
void oled_showchinese(uchar x,uchar y,uchar no);//显示汉字,x y为坐标，no为编号

int Test_LCD12864(void);//LCD12864测试程序

#endif