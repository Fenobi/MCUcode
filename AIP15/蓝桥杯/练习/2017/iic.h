#include "public.h"

sbit scl=P2^0;
sbit sda=P2^1;

u8 AD_read(u8 addr);
void AD_write(u8 dat);
void EEPROM_write(u8* string,u8 addr,u8 num);
void EEPROM_read(u8* string,u8 addr,u8 num);