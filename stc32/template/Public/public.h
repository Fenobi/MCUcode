#ifndef __PUBLIC_H
#define __PUBLIC_H

#include <STC32G.H>
typedef unsigned char u8;
typedef unsigned int u16;

#define MAIN_Fosc 35000000UL

void Delay10us();		//@35MHz
void Delay1ms();		//@35MHz
void Delay1us();		//@35MHz
void DelayMs(unsigned int n);
void Delay10Nus(unsigned int n);
void DelayNus(unsigned int n);

#endif
