#ifndef _E2PROM_H
#define _E2PROM_H

#include "public.h"
#include "iic.h"

void Write_EEPROM(u8 addr,u8 Data);
u8 Read_EEPROM(u8 addr);

#endif