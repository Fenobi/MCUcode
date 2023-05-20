#ifndef _DS1302_H_
#define _DS1302_H_

#include "public.h"
	
//---定义ds1302使用的IO口---//
sbit DSIO=P1^5;
sbit SCLK=P1^6;
sbit RST =P1^7;

extern uchar *week_str[7];                    //周的英文缩写
extern uchar TIME[7];

void Ds1302Init();                            //DS1302初始化。
void Ds1302ReadTime();                        //读取时钟信息。
uchar DS1302_sec();                           //读秒
uchar DS1302_min();                           //读分
uchar DS1302_hour();													//读时
uchar DS1302_date();													//读日
uchar DS1302_month();                         //读月
uchar DS1302_week();                          //读周
uint DS1302_year();                           //读年

/*================================================================*/
void Ds1302Write(uchar addr, uchar dat);      //向DS1302写入命令（地址+数据）
uchar Ds1302Read(uchar addr);                 //读取一个地址的数据

#endif




