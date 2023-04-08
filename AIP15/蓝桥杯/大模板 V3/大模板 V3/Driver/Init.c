#include <Init.h>

/* 
		函数名称：系统初始化函数
		函数说明：上电后关闭系统外设
		入口参数：无
		返回数据：无
*/

void Sys_Init()
{
	P0 = 0xff;
	P2 = P2 & 0x1f | 0x80;
	P2 &= 0x1f;
	P0 = 0x00;
	P2 = P2 & 0x1f | 0xa0;
	P2 &= 0x1f;
}