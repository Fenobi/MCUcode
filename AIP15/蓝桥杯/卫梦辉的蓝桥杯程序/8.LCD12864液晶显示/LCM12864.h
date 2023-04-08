#ifndef	__LCM12864_H
#define	__LCM12864_H
#include <STC15F2K60S2.H>
#include "stdio.h"

void LCD12864_Write_Data(unsigned char dat);//向12864中写入数据
void LCD12864_Write_Com(unsigned char com);//向12864中写入命令
extern void LCD12864_Init();//对LCD12864进行初始化
extern void LCD12864_Display_Char(unsigned char x,unsigned char y,unsigned char dat);//显示单个字符
extern void LCD12864_Display_Chars(unsigned char x,unsigned char y,unsigned char *dat);//显示字符串
extern void LCD12864_Clear_Screen(unsigned char value);//进行清屏操作 LCD12864_Clear_Screen(0xFF)全亮,LCD12864_Clear_Screen(0xFF)全灭
extern void LCD12864_ZS_display(unsigned char x,unsigned char y,unsigned int dat1);//显示整数变量值函数
extern void LCD12864_XS_display(unsigned char x,unsigned char y,float num,unsigned char wei);//显示指定位数小数变量值 

extern void LCD12864_Test();//LCD12864显示测试程序
extern void LCD12864_Clearn(unsigned char hang,unsigned char x1,unsigned char x2);//显示变量值函数

#endif