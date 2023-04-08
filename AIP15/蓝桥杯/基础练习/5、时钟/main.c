#include<STC15F2K60S2.h>
#include<intrins.h>
#include"time.h"

bit key = 0;
sbit k1 = P3^0;
unsigned char data_pros[10] = {0xc0, 0xf9, 0xa4, 0xb0, 
																0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
void Delay3us()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 1;
	j = 5;
	k = 5;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Close_Buzz()
{
	P2 = 0xA0;
	P0 = 0x00;
	P2 = 0x00;
}

void display(unsigned char dat[7])
{
	unsigned char i;
	int temp = 0;;
	if (key == 1)
	{
		for (i=0; i<8; i++)
		{
			switch (i)
			{
				case 0:
					P2 = 0xC0;
					P0 = 0x01;
					break;
				case 1:
					P2 = 0xC0;
					P0 = 0x02;
					break;
				case 2: 
					P2 = 0xC0;
					P0 = 0x04;
					break;
				case 3:
					P2 = 0xC0;
					P0 = 0x08;
					break;
				case 4:
					P2 = 0xC0;
					P0 = 0x10;
					break;
				case 5:
					P2 = 0xC0;
					P0 = 0x20;					
					break;
				case 6: 
					P2 = 0xC0;
					P0 = 0x40;	
					break;
				case 7: 
					P2 = 0xC0;
					P0 = 0x80;
					break;
				default:
					break;
			}
			switch (i)
			{
				case 0: P2 = 0xE0;P0 = data_pros[dat[0]/16];break;
				case 1: P2 = 0xE0;P0 = data_pros[dat[0]%16];break;
				case 2: P2 = 0xE0;P0 = data_pros[dat[2]/16];break;
				case 3: P2 = 0xE0;P0 = data_pros[dat[2]%16];break;
				case 4: P2 = 0xE0;P0 = data_pros[dat[3]/16];break;
				case 5: P2 = 0xE0;P0 = data_pros[dat[3]%16];break;
				case 6: P2 = 0xE0;P0 = 0xBF;  break;
				case 7: P2 = 0xE0;P0 = data_pros[dat[1]];break;
				default:
					break;
			}
			Delay3us();
			P0 = 0xFF;
			
		}
	}
	else 
	{
		for (i=0; i<8; i++)
		{
			switch (i)
			{
				case 0:
					P2 = 0xC0;
					P0 = 0x01;
					break;
				case 1:
					P2 = 0xC0;
					P0 = 0x02;
					break;
				case 2: 
					P2 = 0xC0;
					P0 = 0x04;
					break;
				case 3:
					P2 = 0xC0;
					P0 = 0x08;
					break;
				case 4:
					P2 = 0xC0;
					P0 = 0x10;
					break;
				case 5:
					P2 = 0xC0;
					P0 = 0x20;					
					break;
				case 6: 
					P2 = 0xC0;
					P0 = 0x40;	
					break;
				case 7: 
					P2 = 0xC0;
					P0 = 0x80;
					break;
				default:
					break;
			}
			switch (i)
			{
				case 0: P2 = 0xE0;P0 = 0xBF;break;
				case 1: P2 = 0xE0;P0 = 0xBF;break;
				case 2: P2 = 0xE0;P0 = data_pros[dat[4]/16];break;
				case 3: P2 = 0xE0;P0 = data_pros[dat[4]%16];break;
				case 4: P2 = 0xE0;P0 = data_pros[dat[5]/16];break;
				case 5: P2 = 0xE0;P0 = data_pros[dat[5]%16];break;
				case 6: P2 = 0xE0;P0 = data_pros[dat[6]/16];break;
				case 7: P2 = 0xE0;P0 = data_pros[dat[6]%16];break;
				default:
					break;
			}
			Delay3us();
			P0 = 0xFF;
		}
	}
}



void main()
{
	Close_Buzz();
	burst_Init_time();
	
	EX0 = 1;
	IT0 = 1;
	EA = 1;
	
	
	while(1)
	{
		Read_DS1302_Time();
		display(Time);
	}
}

void key_press() interrupt 0
{
	key = ~key;
}
	