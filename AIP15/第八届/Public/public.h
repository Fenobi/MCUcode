/***
 * @Author: Fenobi 13667739122@qq.com
 * @Date: 2023-03-15 22:48:47
 * @LastEditors: Fenobi 13667739122@qq.com
 * @LastEditTime: 2023-03-16 11:44:26
 * @FilePath: \DS18B20\Public\public.h
 */
#ifndef _public_H
#define _public_H

#include <STC15F2K60S2.H>
#include <intrins.h>

typedef unsigned int u16;
typedef unsigned char u8;

void Delay_ms(unsigned int ms);
void delay_10us(unsigned int us);
void delay_1us(unsigned int us);

#endif