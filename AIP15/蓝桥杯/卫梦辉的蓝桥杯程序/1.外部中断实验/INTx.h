#ifndef __INTX_H__
#define __INTX_H__
#include <STC15F2K60S2.H>

//具体看芯片寄存器INT_CLKO
#define EX2             0x10
#define EX3             0x20
#define EX4             0x40

void INT0_Init(void);//外部中断0初始化函数
void INT1_Init(void);//外部中断1初始化函数
void INT2_Init(void);//外部中断3初始化函数
void INT3_Init(void);//外部中断3初始化函数
void INT4_Init(void);//外部中断4初始化函数

#endif
