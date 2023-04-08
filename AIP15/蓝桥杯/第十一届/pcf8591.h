#ifndef _PCF8591_H
#define _PCF8591_H

#include "public.h"
#include "iic.h"

u8 AD_read(u8 addr);
void AD_write(u8 dat);

#endif