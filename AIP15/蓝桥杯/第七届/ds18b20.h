/***
 * @Author: Fenobi 13667739122@qq.com
 * @Date: 2023-03-15 22:48:47
 * @LastEditors: Fenobi 13667739122@qq.com
 * @LastEditTime: 2023-03-16 11:44:52
 * @FilePath: \DS18B20\App\ds18b20\ds18b20.h
 */
#ifndef _ds18b20_H
#define _ds18b20_H

#include "public.h"

sbit DS18B20_PORT = P1^4;

u8 ds18b20_init(void);
void ds18b20_write_byte(u8 dat);
u8 ds18b20_read_byte(void);
float ds18b20_read_temperture(void);

#endif