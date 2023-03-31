#ifndef _XPT2046_H
#define _XPT2046_H

#include "public.h"

sbit DOUT = P3^7;	  //输出
sbit CLK  = P3^6;	  //时钟
sbit DIN  = P3^4;	  //输入
sbit CS   = P3^5;	  //片选

u16 xpt2046_read_adc_value(u8 cmd);

#endif