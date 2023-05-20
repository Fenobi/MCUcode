#ifndef __PUBLIC_H
#define __PUBLIC_H

#include <STC15F2K60S2.H>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int

typedef struct
{
	unsigned char l;
	unsigned char m;
	unsigned char r;
	unsigned char l_old;
	unsigned char m_old;
	unsigned char r_old;

} lmr_struct;

void Timer0_Init(void);		//1毫秒@12.000MHz
void Timer1_Init(void);		//1毫秒@12.000MHz

void DelayNms(unsigned int n);

#endif
