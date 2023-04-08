#include "led.h"

unsigned char data_pros[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};


void Display(unsigned char da)
{
	//显示个位
	P0 = 0x80;
	P2 = 0xC0;
	_nop_();_nop_();
	_nop_();_nop_();
	P2 = 0x00;
	//显示数字
	P0 = data_pros[da];
	P2 = 0xE0;
	_nop_();_nop_();
	_nop_();_nop_();
	P2 = 0x00;
}