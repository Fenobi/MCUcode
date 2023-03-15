/*** 
 * @Author: Fenobi 13667739122@qq.com
 * @Date: 2023-03-14 16:55:49
 * @LastEditors: Fenobi 13667739122@qq.com
 * @LastEditTime: 2023-03-16 11:41:00
 * @FilePath: \EEPROM\App\at24c02\at24c02.h
 */
#ifndef _at24c02_H
#define _at24c02_H

#include "public.h"
#include "iic.h"

void at24c02_write_one_byte(u8 addr,u8 dat);
u8 at24c02_read_one_byte(u8 addr);



#endif