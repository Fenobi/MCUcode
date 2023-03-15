/***
 * @Author: Fenobi 13667739122@qq.com
 * @Date: 2023-03-14 15:53:38
 * @LastEditors: Fenobi 13667739122@qq.com
 * @LastEditTime: 2023-03-16 11:41:50
 * @FilePath: \EEPROM\App\smg\smg.h
 */
#ifndef _smg_H
#define _smg_H

#include "public.h"

#define SMG_A_DP_PORT P0

sbit LSA = P2^2;
sbit LSB = P2^3;
sbit LSC = P2^4;

void smg_display(u8 dat[], u8 pos);

#endif