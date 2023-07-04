#ifndef __12864_ST7920C_H_
#define __12864_ST7920C_H_

#include "public.h"

void LCD12864_Init();
void font1();
void font2(int h,l);
void wr_gdram(int k,h);//显示网点函数
void wr_gdram_H();
void wr_gdram_W();
void chk_busy();
unsigned char ReceiveByte(void);
void write_com(unsigned char Cbyte);
void write_data(unsigned char Dbyte );
void delay(int t);
void SendByte(unsigned char Dbyte);
void PutBMP(unsigned char *puts);
void LcmClearBMP( void );
void LcmClearTXT( void );	

void lcd_text();//初始化函数


#endif