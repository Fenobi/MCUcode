#ifndef _ired_H
#define _ired_H

#include "public.h"

sbit IRED=P3^2;

extern u8 gired_data[4];

void ired_init(void);

#endif