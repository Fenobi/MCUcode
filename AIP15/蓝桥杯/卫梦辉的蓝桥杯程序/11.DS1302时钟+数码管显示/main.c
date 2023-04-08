#include <STC15F2K60S2.h>
#include "smg.h"//数码管函数头文件
#include "time.h"//DS1302函数头文件


void main()
{
//	Init_DS1302_Time();
//	burst_Init_time();
	while(1)
	{
		Read_DS1302_Time();//读取DS1302时间，刷新到数组Time[7]中
		Display_2_WEI(1,Time[4]/16*10+Time[4]%16);//数码管显示时
		Display_1_WEI(3,11,0);//数码管显示”-“
		Display_2_WEI(4,Time[5]/16*10+Time[5]%16);//数码管显示分
		Display_1_WEI(6,11,0);//数码管显示”-“
		Display_2_WEI(7,Time[6]/16*10+Time[6]%16);//数码管显示秒
	}
}
