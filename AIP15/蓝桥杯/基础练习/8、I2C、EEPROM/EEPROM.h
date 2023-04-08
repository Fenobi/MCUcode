#ifndef EEPROM_H
#define EEPROM_H

#include <STC15F2K60S2.h>
#include "iic.h"

void Write_EEPROM(unsigned char addr,unsigned char dat);
unsigned char Read_EEPROM(unsigned char addr); 

#endif