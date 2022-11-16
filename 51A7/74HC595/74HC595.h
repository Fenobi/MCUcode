#include <REGX52.H>

typedef unsigned char u8;
typedef unsigned int u16;

sbit RC=P3^5;//上升延 移位 0~1
sbit SC=P3^6;//上升延 储存
sbit SER=P3^4; //数据输入端

//#define LED_LATTTICE_COL_PORT  P0

extern u8 hc595_buf[9];

void delay_n10us(u16 n);

void HC595_write_data(u8 dat1,u8 dat2,u8 dat3,u8 dat4);