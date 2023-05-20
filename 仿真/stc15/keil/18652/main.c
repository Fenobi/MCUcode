
#include "IIC_LCD12864.h"
#include <STC15F2K60S2.H>


void main()
{

	int val=1314;
	oled_init();//OLED初始化
	
  while (1)
	{	
		OLED_Display_Num(0,0,-284);//显示小号数字函数
		OLED_Display_NumPint(0,1,-36.9);//显示小号小数数字函数
		oled_shownum(0,2,val,5,16);//显示大号数字函数-----  x,y:坐标,num数值,len显示位数,size2是字体，默认填16就行
		oled_showchinese(0,4,0);//显示汉字,x y为坐标，no为编号	
		oled_showstring(0,6,"Hello W!",32);//显示字符串
		
		
		LCD12864_delay_ms(100);
	}
}                                                                