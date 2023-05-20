#ifndef __LCD1602_H__
#define __LCD1602_H__
#include <stdio.h>
#include "intrins.h"

/**********************************
当使用的是4位数据传输的时候定义，
使用8位取消这个定义
**********************************/
//#define LCD1602_4PINS

//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

/**********************************
PIN口定义
**********************************/


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

//		LcdWriteCom(0x01);  //清屏
void DisplayOneChar(uchar X, uchar Y, uchar DData);//显示单个字符
void DisplayListChar(uchar X, uchar Y, uchar *DData);//显示字符串
void Display_Num(uchar X, uchar Y, int num);//显整数函数 范围-32768~32767
void Display_NumPoint(uchar X, uchar Y, float decimal);//显小数函数 范围

void LCD1602_test(void);//LCD1602测试程序

#endif
