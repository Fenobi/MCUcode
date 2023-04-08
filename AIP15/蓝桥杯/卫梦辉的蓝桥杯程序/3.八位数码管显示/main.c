#include <STC15F2K60S2.H>
#include "delay.h"//延时函数头文件
#include "smg.h"//数码管函数头文件

void main()
{
	while(1)
	{
		
		//实验程序1
		Display_1_WEI(1,1,1);//数码管指定一位显示一位数字函数
		Display_1_WEI(2,2,0);//数码管指定一位显示一位数字函数
		Display_1_WEI(3,3,0);//数码管指定一位显示一位数字函数
		Display_1_WEI(4,4,1);//数码管指定一位显示一位数字函数
		Display_1_WEI(5,5,0);//数码管指定一位显示一位数字函数
		Display_1_WEI(6,6,0);//数码管指定一位显示一位数字函数
		Display_1_WEI(7,7,0);//数码管指定一位显示一位数字函数
		Display_1_WEI(8,8,0);//数码管指定一位显示一位数字函数		
		
		//实验程序2
//		Display_2_WEI(2,68);
		
		//实验程序2
//		Display_4_WEI(2,5739);

		//实验程序3
//		Display_1_2Wei_XS(1,7.82);
		
		//实验程序4
//		Display_2_2Wei_XS(5,29.82);
		
		
	}
}
