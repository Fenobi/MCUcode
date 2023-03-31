#include "smg.h"
#include "ired.h"

int main()
{
	u8 ired_buf[3];
	ired_init();
	while (1)
	{
		ired_buf[0] = gsmg_code[gired_data[2] / 16];
		ired_buf[1] = gsmg_code[gired_data[2] % 16];
		ired_buf[2] = 0x76;
		smg_display(ired_buf, 6);
	}
}