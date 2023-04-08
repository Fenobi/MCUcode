#ifndef _SMG_H
#define _SMG_H

#include "public.h"

sbit PA=P2^5;
sbit PB=P2^6;
sbit PC=P2^7;

void display_wei(u8 wei);
void display_1num(u8 num, u8 point);
void HC_138(u8 num);

#endif