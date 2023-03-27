#include "ds1302.h"
#include "smg.h"
#include "ds18b20.h"
#include "iic.h"
#include "key.h"
#include "Buzz_Relay.h"

u8 falg = 1;
u8 i = 0;
u8 is_on;
u8 time_buf_cpy[8];

void tm0_isr() 	 1
{
	++i;
	if (i == 20)
	{
		i = 0;
		is_on = ~is_on;
	}
}

void Timer0Init(void) // 50毫秒@12.000MHz
{

	AUXR &= 0x7F; // 定时器时钟12T模式
	TMOD &= 0xF0; // 设置定时器模式
	TL0 = 0xB0;	  // 设置定时初始值
	TH0 = 0x3C;	  // 设置定时初始值
	TF0 = 0;	  // 清除TF0标志
	TR0 = 1;	  // 定时器0开始计时
}

void time_display(u8 time_buf[8])
{
	while(1)
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
		if(key_scan(0))
		{
			break;
		}
	}
}

void clock_reg(u8 num,u8 time_buf_cpy[])
{
	switch (num)
	{
	case 2:
		++time_buf_cpy[num];
		break;
	case 3:
		--time_buf_cpy[num];
		break;
	}
}


void clock(u8 time_buf[8],u8 n)
{
	u8 i = 0;
	u8 key_temp;
	
	for (i = 0; i < 8; ++i)
	{
		time_buf_cpy[i] = time_buf[i];
	}
	while(1)
	{
		key_temp = key_scan(0);
		Display_2_WEI(1, time_buf_cpy[0] * 10 + time_buf_cpy[1]);
		Display_1_WEI(3, 11, 0);
		Display_2_WEI(4, time_buf_cpy[3] * 10 + time_buf_cpy[4]);
		Display_1_WEI(6, 11, 0);
		Display_2_WEI(7, time_buf_cpy[6] * 10 + time_buf_cpy[7]);
		while(is_on)
		{
			key_temp = key_scan(0);
			if(n==0)
			{
				Display_2_WEI(1, time_buf_cpy[0] * 10 + time_buf_cpy[1]);
				Display_1_WEI(3, 11, 0);
				Display_2_WEI(4, time_buf_cpy[3] * 10 + time_buf_cpy[4]);
				Display_1_WEI(6, 11, 0);
				// Display_2_WEI(7, time_buf_cpy[6] * 10 + time_buf_cpy[7]);
			}
			else if(n==1)
			{
				Display_2_WEI(1, time_buf_cpy[0] * 10 + time_buf_cpy[1]);
				Display_1_WEI(3, 11, 0);
				//Display_2_WEI(4, time_buf_cpy[3] * 10 + time_buf_cpy[4]);
				Display_1_WEI(6, 11, 0);
				Display_2_WEI(7, time_buf_cpy[6] * 10 + time_buf_cpy[7]);
			}
			else if(n==2)
			{
				//Display_2_WEI(1, time_buf_cpy[0] * 10 + time_buf_cpy[1]);
				Display_1_WEI(3, 11, 0);
				Display_2_WEI(4, time_buf_cpy[3] * 10 + time_buf_cpy[4]);
				Display_1_WEI(6, 11, 0);
				Display_2_WEI(7, time_buf_cpy[6] * 10 + time_buf_cpy[7]);
			}

			if (key_temp == 4)
			{
				falg = 0;
				break;
			}
			else if (key_temp == 2 || key_temp == 3)
			{

				if (key_temp == 2)
				{
					switch (n)
					{
					case 0:
						++time_buf_cpy[7];
						break;
					case 1:
						++time_buf_cpy[4];
						break;
					case 2:
						++time_buf_cpy[1];
						break;
					}
					
				}
				if (key_temp == 3)
				{
					switch (n)
					{
					case 0:
						--time_buf_cpy[7];
						break;
					case 1:
						--time_buf_cpy[4];
						break;
					case 2:
						--time_buf_cpy[1];
						break;
					}
				}
			}
			
			
		}

		if (key_temp == 4)
		{
			falg = 0;
			break;
		}
		else if (key_temp == 2 || key_temp == 3)
		{

			if (key_temp == 2)
			{
				switch (n)
				{
				case 0:
					++time_buf_cpy[7];
					break;
				case 1:
					++time_buf_cpy[4];
					break;
				case 2:
					++time_buf_cpy[1];
					break;
				}
			}
			if (key_temp == 3)
			{
				switch (n)
				{
				case 0:
					--time_buf_cpy[7];
					break;
				case 1:
					--time_buf_cpy[4];
					break;
				case 2:
					--time_buf_cpy[1];
					break;
				}
			}
		}
		else if(key_temp==1)
		{
			if(n==2)
				n = -1;
			clock(time_buf_cpy, ++n);
		}
	}
}

void FMQ(void)
{
	HC138_A = 1;
	HC138_B = 0;
	HC138_C = 1;
	//FMQ_temp = 1;
}

int main()
{
	u8 time_buf[8];
	u8 key_temp = key_scan(0);
	u8 t = 0,q=0;
	i = 0;

	BUZZ(0);
	RELAY(0);
	
	ET0 = 1;
	EA = 1;
	Timer0Init();
	
	ds1302_init();
	ds1302_read_time();
	while (1)
	{
		 for (t = 0; t < 8;++t)
		 {
		 	if(time_buf[t]!=time_buf_cpy[t])
		 		break;
		 	else
			{
		 		++q;
				if(q==8)
				{
		 			BUZZ(1);
		 		}
					
		 	}
		 }
		key_temp = key_scan(0);
		if (KEY4 == 0)
		{
			// while (!key_scan(0))
			Display_2_2Wei_XS(5, ds18b20_read_temperture());
		}
		if (KEY1 == 0 && falg)
		{
			clock(time_buf,0);
			falg = 1;
		}
		else
		{
			time_display(time_buf);
			BUZZ(0);
		}
		
	}

}
