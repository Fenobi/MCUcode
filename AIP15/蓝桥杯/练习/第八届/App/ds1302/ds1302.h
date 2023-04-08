#ifndef _ds1302_H
#define _ds1302_H

#include "public.h"

sbit DS1302_RST = P1^3;
sbit DS1302_CLK = P1^7;
sbit DS1302_IO = P2^3;

void ds1302_write_byte(u8 addr, u8 dat);
u8 ds1302_read_byte(u8 addr);
void ds1302_init(void);
void ds1302_read_time(void);

extern u8 gWRITE_RTC_ADDR[7]; // 秒分时日月年
extern u8 gREAD_RTC_ADDR[7]; // 秒分时日月年
extern u8 gDS1302_TIME[7];

#endif