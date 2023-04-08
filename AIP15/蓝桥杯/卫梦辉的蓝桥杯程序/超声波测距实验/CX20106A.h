#ifndef __CX20106_H__
#define __CX20106_H__
#include <STC15F2K60S2.h>
#include <intrins.h>

#define u8 unsigned int 
#define u16 unsigned int 

void US_init(void);//超声波模块初始化函数
u16 Get_distance(void);//超声波模块获得距离函数（函数还回距离值 单位：cm）

#endif