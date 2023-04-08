#include <Led.h>

/* 
		函数名称：Led显示函数
		函数说明：点亮/熄灭任意一个Led
		入口参数：addr-需要点亮的Led flag-1点亮/0熄灭
		返回数据：无
*/
void Led_Disp(unsigned char addr,flag)
{
	static unsigned char temp = 0x00;
	static unsigned char temp_old = 0xff;
	
	if(flag)
		temp |= 0x01 << addr;
	else
		temp &= ~(0x01 << addr);
	if(temp != temp_old)
	{
		P0 = ~temp;
		P2 = P2 & 0x1f | 0x80;
		P2 &= 0x1f;
		temp_old = temp;
	}
}

unsigned char temp = 0x00;
unsigned char temp_old = 0xff;

/* 
		函数名称：继电器使能函数
		函数说明：开启/关闭继电器
		入口参数：flag-1开启/0关闭
		返回数据：无
*/
void Relay(unsigned char flag)
{
	if(flag)
		temp |= 0x10;
	else
		temp &= ~0x10;	
	if(temp != temp_old)
	{
		P0 = temp;
		P2 = P2 & 0x1f | 0xa0;
		P2 &= 0x1f;
		temp_old = temp;
	}	
}

/* 
		函数名称：蜂鸣器使能函数
		函数说明：开启/关闭继电器
		入口参数：flag-1开启/0关闭
		返回数据：无
*/
void Beep(unsigned char flag)
{
	if(flag)
		temp |= 0x40;
	else
		temp &= ~0x40;	
	if(temp != temp_old)
	{
		P0 = temp;
		P2 = P2 & 0x1f | 0xa0;
		P2 &= 0x1f;
		temp_old = temp;
	}	
}