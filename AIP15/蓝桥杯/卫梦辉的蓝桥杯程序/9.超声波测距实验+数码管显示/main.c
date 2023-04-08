#include <STC15F2K60S2.H>
#include "delay.h"//延时函数头文件
#include "smg.h"//数码管函数头文件
#include "CX20106A.h"//超声波函数头文件

void main()
{
	u8 JL;
	CSB_Init();//超声波定时器初始化
	while(1)
	{
		JL=Get_Distance();
		Display_2_WEI(1,JL);
	}
}
