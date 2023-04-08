#include<STC15F2K60S2.h>
#include<intrins.h>

unsigned char data_pros[10] = {0xc0, 0xf9, 0xa4, 0xb0, 
																0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

																
void delay()	//delay 200ms @ 11.0592M
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
void main()
{
//	for(i=0; i<2; i++)
//	{

//			if (i == 0)
//			{
//				//显示十位
//				P2 = 0xC0;
//				P0 = 0x40; 
//				//显示数字
//				P2 = 0xE0;
//				P0 = data_pros[temp1];
//			}
//			else
//			{
//				//显示个位
//				P2 = 0xC0;
//				P0 = 0x80;
//				//显示数字
//				P2 = 0xE0;
//				P0 = data_pros[temp2];
//			}		
//	}	

//				//显示个位
//				P2 = 0xC0;
//				P0 = 0x80;
//				//显示数字
//				P2 = 0xE0;
//				P0 = data_pros[1];
//				delay();
			

		while(1)
		{
				//显示个位
				P2 = 0xC0;
				P0 = 0x80;
				//显示数字
				P2 = 0xE0;
				P0 = 0xff;
				P0 = data_pros[9];
				delay();
				P2 = 0x00;
				//显示十位
				P2 = 0xC0;
				P0 = 0x40;
				//显示数字
				P2 = 0xE0;
				P0 = data_pros[2];
				delay();
		}
}