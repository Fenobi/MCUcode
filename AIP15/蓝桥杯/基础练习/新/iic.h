#ifndef __IIC_H_
#define __IIC_H_

void Write_EEPROM(unsigned char addr,unsigned char da);
unsigned char Read_EEPROM(unsigned char addr);

#endif