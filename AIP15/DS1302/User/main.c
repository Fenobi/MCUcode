/*
 * @Author: Fenobi 13667739122@qq.com
 * @Date: 2023-03-16 20:59:44
 * @LastEditors: Fenobi 13667739122@qq.com
 * @LastEditTime: 2023-03-16 22:01:45
 * @FilePath: \DS1302\User\main.c
 */
#include "ds1302.h"
#include "smg.h"

int main()
{
	u8 time_buf[8];
	// ds1302_init();

	while (1)
	{
		ds1302_read_time();
		time_buf[0] = gDS1302_TIME[2] / 16;
		time_buf[1] = gDS1302_TIME[2] % 16;
		time_buf[2] = 0x40;
		time_buf[3] = gDS1302_TIME[1] / 16;
		time_buf[4] = gDS1302_TIME[1] % 16;
		time_buf[5] = 0x40;
		time_buf[6] = gDS1302_TIME[0] / 16;
		time_buf[7] = gDS1302_TIME[0] % 16;

		Display_2_WEI(1, time_buf[0] * 10 + time_buf[1]);
		Display_1_WEI(3, 11, 0);
		Display_2_WEI(4, time_buf[3] * 10 + time_buf[4]);
		Display_1_WEI(6, 11, 0);
		Display_2_WEI(7, time_buf[6] * 10 + time_buf[7]);
	}
}