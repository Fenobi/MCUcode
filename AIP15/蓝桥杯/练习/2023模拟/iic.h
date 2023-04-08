#include "public.h"

sbit SDA = P2^1;
sbit SCL = P2^0;

u8 AD_read(u8 addr);
void DA_write(u8 dat);

void EEPROM_read(u8 *string, u8 addr, u8 num);
void EEPROM_write(u8 *string, u8 addr, u8 num);