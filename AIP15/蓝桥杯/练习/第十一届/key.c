#include "key.h"

u8 Key_KBD_Read(u8 mode)
{
	u8 temp = 0;
	static u8 key=1;
	u8 flag=0;
	AUXR &= 0xEF; //关闭T2R 即 定时器2 （串口波特率发生所用的定时器）
	if(mode) key=1;
	
	if(key==1)
	{
		key=0;

		P44 = 0;P42 = 1;P35 = 1;P34 = 1;
		if(P33 == 0) temp = 4;
		if(P32 == 0) temp = 5;
		if(P31 == 0) temp = 6;
		if(P30 == 0) temp = 7;

		P44 = 1;P42 = 0;P35 = 1;P34 = 1;
		if(P33 == 0) temp = 8;
		if(P32 == 0) temp = 9;
		if(P31 == 0) temp = 10;
		if(P30 == 0) temp = 11;
		
		P44 = 1;P42 = 1;P35 = 0;P34 = 1;
		if(P33 == 0) temp = 12;
		if(P32 == 0) temp = 13;
		if(P31 == 0) temp = 14;
		if(P30 == 0) temp = 15;
		
		P44 = 1;P42 = 1;P35 = 1;P34 = 0;
		if(P33 == 0) temp = 16;
		if(P32 == 0) temp = 17;
		if(P31 == 0) temp = 18;
		if(P30 == 0) temp = 19;
		
		P3 = 0xff;
	}
	else if(temp==0)
	{
		key=1;	
	}
	AUXR |= 0x10; //打开T2R 即 定时器2 （串口波特率发生所用的定时器）
	
	return temp;
}