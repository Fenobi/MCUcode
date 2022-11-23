#include <STC15F2K60S2.H>
#include <intrins.h>

typedef unsigned char u8;
typedef unsigned int u16;

unsigned char data_pros[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

void delay()
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

int find_butten()
{
	int col = 0;
	int key_value = 0;
	int key_press = 0; //消抖处理
	
	//检测列，得出col值
	P3 = 0xF0;
	P42 = 1;
	P44 = 1;
	if ((P3 != 0xF0) || (P42 == 0) || (P44 == 0))
	{
		delay();		//消抖	
		if ((P3 != 0xF0) || (P42 == 0) || (P44 == 0))
		{
			if ((P3&0x10) == 0)		col = 4;
			if ((P3&0x20) == 0)		col = 3;
			if (P42 == 0)		col = 2;
			if (P44 == 0)		col = 1;
		}
	}	
	//检测行，得出key_value，return key_value，如果不成功则返回0
	P3 = 0x0F;
	P44 = 0;
	P42 = 0;
	if (col != 0)
	{
		if ((P3&0x01) == 0)		key_value = col + 0;
		if ((P3&0x02) == 0)		key_value = col + 4;
		if ((P3&0x04) == 0)		key_value = col + 8;
		if ((P3&0x08) == 0)		key_value = col + 12;
		
		P2 = 0x00;
		return key_value;
	}
	P2 = 0x00;
	return 0;
}

//数码管函数
void display(int value)
{
	int i = 0;
	int temp1,temp2;
	temp1 = value/10;
	temp2 = value%10;
	
				P2 = 0xC0;
				P0 = 0x80;
				//显示数字
				P2 = 0xE0;
				P0 = 0xff;
				P0 = data_pros[temp2];
				delay();
				P2 = 0x00;
				//显示十位
				P2 = 0xC0;
				P0 = 0x40;
				//显示数字
				P2 = 0xE0;
				P0 = data_pros[temp1];
				delay();
}

void main()
{
	int value = 0;
	while(1)
	{
		value = find_butten();
		display(value);
	}
}