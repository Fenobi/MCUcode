#ifndef __LCD1602_H__
#define __LCD1602_H__
#include <STC15F2K60S2.H>
#include <stdio.h>

/**********************************
当使用的是4位数据传输的时候定义，
使用8位取消这个定义
**********************************/
//#define LCD1602_4PINS

//---重定义关键词---//
#define uchar unsigned char
#define uint unsigned int

/**********************************
PIN口定义
**********************************/
sbit LCD1602_E=P1^2;
sbit LCD1602_RW=P2^1;
sbit LCD1602_RS=P2^0;

#define LCD1602_DATAPINS P0


/**********************************
函数声明
**********************************/
/*在51单片机12MHZ时钟下的延时函数*/
void Lcd1602_Delay1ms(uint c);   //误差 0us
/*LCD1602写入8位命令子函数*/
void LcdWriteCom(uchar com);
/*LCD1602写入8位数据子函数*/	
void LcdWriteData(uchar dat);
/*LCD1602初始化子程序*/		
void LcdInit();						  

void DisplayOneChar(uchar X, uchar Y, uchar DData);//显示单个字符
void DisplayListChar(uchar X, uchar Y, uchar *DData);//显示字符串
void Display_XS(uchar X, uchar Y,float XS,uchar XS_wei);//显示指定小数。

void LCD1602_test(void);//LCD1602测试程序

#endif
