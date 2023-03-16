#include "ds1302.h"
#include "smg.h"

int main()
{
	u8 time_buf[8];
	ds1302_init();

	while(1)
	{
		ds1302_read_time();
		time_buf[0] = gsmg_code[gDS1302_TIME[2] / 16];
		time_buf[1] = gsmg_code[gDS1302_TIME[2] % 16];
		time_buf[2] = 0x40;
		time_buf[3] = gsmg_code[gDS1302_TIME[1] / 16];
		time_buf[4] = gsmg_code[gDS1302_TIME[1] % 16];
		time_buf[5] = 0x40;
		time_buf[6] = gsmg_code[gDS1302_TIME[0] / 16];
		time_buf[7] = gsmg_code[gDS1302_TIME[0] % 16];
		smg_display(time_buf, 1);
	}
}