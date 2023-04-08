#ifndef _SMG_H
#define _SMG_H

#include "public.h"

sbit LA=P2^5;
sbit LB=P2^6;
sbit LC=P2^7;

void HC138(u8 num);
void smg_display_wei(u8 wei);
void smg_dispaly_num(u8 num);
void smg_dispaly_fore_num(u16 num);

#endif