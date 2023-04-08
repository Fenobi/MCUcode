/*
 * @Author: Fenobi 13667739122@qq.com
 * @Date: 2023-03-16 19:55:18
 * @LastEditors: Fenobi 13667739122@qq.com
 * @LastEditTime: 2023-03-17 19:12:32
 * @FilePath: \第八届\App\ds1302\ds1302.c
 */
#include "ds1302.h"

u8 gWRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
u8 gREAD_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};

u8 gDS1302_TIME[7] = {0x20, 0x59, 0x23, 0x16, 0x04, 0x03, 0x23};

void ds1302_write_byte(u8 addr, u8 dat)
{
    u8 i = 0;

    DS1302_RST = 0;
    _nop_();
    DS1302_CLK = 0;
    _nop_();
    DS1302_RST = 1;
    _nop_();

    for (i = 0; i < 8; ++i)
    {
        DS1302_IO = addr & 0x01;
        addr >>= 1;

        DS1302_CLK = 1;
        _nop_();
        DS1302_CLK = 0;
        _nop_();
    }
    for (i = 0; i < 8; ++i)
    {
        DS1302_IO = dat & 0x01;
        dat >>= 1;

        DS1302_CLK = 1;
        _nop_();
        DS1302_CLK = 0;
        _nop_();
    }
    DS1302_RST = 0;
    _nop_();
}

u8 ds1302_read_byte(u8 addr)
{
    u8 i = 0;
    u8 temp = 0;
    u8 value = 0;

    DS1302_RST = 0;
    _nop_();
    DS1302_CLK = 0;
    _nop_();
    DS1302_RST = 1;
    _nop_();

    for (i = 0; i < 8; ++i)
    {
        DS1302_IO = addr & 0x01;
        addr >>= 1;

        DS1302_CLK = 1;
        _nop_();
        DS1302_CLK = 0;
        _nop_();
    }
    for (i = 0; i < 8; ++i)
    {
        temp = DS1302_IO;
        value = (temp << 7) | (value >> 1);
        DS1302_CLK = 1;
        _nop_();
        DS1302_CLK = 0;
        _nop_();
    }
    DS1302_RST = 0;
    _nop_();

    // P3.4口没有外接上拉电阻的，此处代码需要添加
    DS1302_CLK = 1;
    _nop_();
    DS1302_IO = 0;
    _nop_();
    DS1302_IO = 1;
    _nop_();

    return value;
}

void ds1302_init(void)
{
    u8 i = 0;

    ds1302_write_byte(0x8e, 0x00); // 开启写保护
    for (i = 0; i < 7; ++i)
    {
        ds1302_write_byte(gWRITE_RTC_ADDR[i], gDS1302_TIME[i]);
    }
    ds1302_write_byte(0x8e, 0x80); // 关闭写保护
}

void ds1302_read_time(void)
{
    u8 i = 0;

    for (i = 0; i < 7; ++i)
    {
        gDS1302_TIME[i] = ds1302_read_byte(gREAD_RTC_ADDR[i]);
    }
}