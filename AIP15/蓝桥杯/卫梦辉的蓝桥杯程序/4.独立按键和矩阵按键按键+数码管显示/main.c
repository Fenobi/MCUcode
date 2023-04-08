#include <STC15F2K60S2.H>
#include "delay.h"//延时函数头文件
#include "smg.h"//数码管函数头文件
#include "key.h"//按键函数头文件

void main()
{
	u8 key_value;
	while(1)
	{
		//实验1 （独立按键，注意跳线冒得插在独立按键）
//		key_value=DL_key1();//读取按键值
//		Display_2_WEI(1,key_value);//数码管显示键值
		
//////		//实验2 （独立按键，注意跳线冒得插在独立按键）xxxxxx没有写完
////////		key_value=DL_key2();//读取按键值
////////		Display_2_WEI(1,key_value);//数码管显示键值
//////		
		
		//实验3 （矩阵按键，注意跳线冒得插在矩阵按键）
		key_value=JZ_key();//读取按键值
		Display_2_WEI(1,key_value);//数码管显示键值

	}
}
