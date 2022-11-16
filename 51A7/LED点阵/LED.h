#include <REGX52.H>
#include <intrins.h>

typedef unsigned char u8;
typedef unsigned int u16;

sbit SRCLK=P3^6;//上升延 储存
sbit rCLK=P3^5; //数据输入端
sbit SER=P3^4;//上升延 移位 0~1

//extern u8 gled_col[32];
//extern u8 gled_row[32];


void delay_n10us(u16 n);

void HC595_write_data(u8 dat1,u8 dat2,u8 dat3,u8 dat4);