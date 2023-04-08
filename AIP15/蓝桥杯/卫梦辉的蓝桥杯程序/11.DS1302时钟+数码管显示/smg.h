#ifndef __SMG_H__
#define __SMG_H__
#include <STC15F2K60S2.H>

sbit HC138_A=P2^5; //74hc138单片机控制引脚
sbit HC138_B=P2^6;
sbit HC138_C=P2^7;

#define SMG_GPIO  P0 //数码管单片机控制引脚

#define u8 unsigned char
#define u16 unsigned int

void HC138_Y(u8 Yx);//74hc138芯片驱动函数
void SMG_Display_Digital(u8 num,u8 point);//数码管显示数字函数(段选)
void SMG_Display_Wei(u8 wei);//选择第几位数码管显示函数(位选)

void Display_1_WEI(u8 wei,u8 num,u8 point);//数码管指定一位显示一位数字函数
void Display_2_WEI(u8 wei,u8 num);//数码管指定从第几位显示两位整数函数
void Display_4_WEI(u8 wei,u16 num);//数码管指定从第几位显示四位数字函数
void Display_1_2Wei_XS(u8 wei,float num);//显示小于10的两位小数函数
void Display_2_2Wei_XS(u8 wei,float num);//显示小于100的两位小数函数

#endif


//共阳数码管段码
//0	--	0xc0
//1	--	0xf9
//2	--	0xa4
//3	--	0xb0
//4	--	0x99
//5	--	0x92
//6	--	0x82
//7	--	0xf8
//8	--	0x80
//9	--	0x90