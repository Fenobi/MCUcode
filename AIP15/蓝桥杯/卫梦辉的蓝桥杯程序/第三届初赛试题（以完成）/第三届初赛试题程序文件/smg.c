#include "smg.h"//数码管函数头文件
#include "delay.h"//延时函数头文件


//*********************************0    1    2    3    4    5    6    7    8    9    .    -
unsigned char Display_Digital[13]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x7f,0xbf,0xff};
unsigned char Display_WEI[9]={0,1,2,4,8,16,32,64,128};


//74hc138芯片驱动函数
//例如：HC138_Y(2);  则74hc138芯片的Y2引脚输出低电平，则将或非门Y2C对应的74hc573芯片输出数据锁存。
void HC138_Y(u8 Yx)
{
	switch(Yx)
	{
		case 0: HC138_C=0;HC138_B=0;HC138_A=0;break;
		case 1: HC138_C=0;HC138_B=0;HC138_A=1;break;
		case 2: HC138_C=0;HC138_B=1;HC138_A=0;break;
		case 3: HC138_C=0;HC138_B=1;HC138_A=1;break;
		case 4: HC138_C=1;HC138_B=0;HC138_A=0;break;
		case 5: HC138_C=1;HC138_B=0;HC138_A=1;break;
		case 6: HC138_C=1;HC138_B=1;HC138_A=0;break;
		case 7: HC138_C=1;HC138_B=1;HC138_A=1;break;
	}
}

//数码管显示数字函数(段选)
//例如： SMG_Display(2,0);  则数码管显示数字2  没有小数点
//例如： SMG_Display(2,1);  则数码管显示数字2. 有小数点
void SMG_Display_Digital(u8 num,u8 point)
{
	switch(point)
	{
		case 0: SMG_GPIO=Display_Digital[num];break;
		case 1: SMG_GPIO=Display_Digital[num]&0x7f;break;
	}
}


//选择第几位数码管显示函数(位选)
//例如： WEI(2); 则八个数码管从左到右第2个数码管可以显示。
void SMG_Display_Wei(u8 wei)
{
	SMG_GPIO=Display_WEI[wei];
}

/*****************************************
					八位数码管显示驱动思路

********************数码管显示一位
**	1.打开对应74hc57跟随输出Y6C，输入位选（选择第几位数码管显示数字）。
**	2.打开对应74hc57跟随输出Y7C，输入对应断码(写入要显示的数字)。
**	3.延时一会儿（比如：2ms），这里要选择一个合适的延时时间（时间大了显示会闪，太小了显示太暗）
**
**	要显示多位依次循环1~4步即可
*********************************************/

//数码管指定一位显示一位数字函数
//例如：Display_1_WEI(2,3,0);  表示第二位数码管显示3 ，数字3下面没有显示小数点
//例如：Display_1_WEI(2,3,1);  表示第二位数码管显示3. ，数字3下面有显示小数点
void Display_1_WEI(u8 wei,u8 num,u8 point)
{
	HC138_Y(6);//1
	SMG_Display_Wei(wei);
	
	HC138_Y(7);//2
	SMG_Display_Digital(num,point);
	
	Delay_ms(2);//3
}

//数码管指定从第几位显示两位整数函数
void Display_2_WEI(u8 wei,u8 num)
{
	Display_1_WEI(wei, num%100/10,0);//显示十位
	Display_1_WEI(wei+1, num%10,0);//显示个位
}

//数码管指定从第几位显示四位整数函数
void Display_4_WEI(u8 wei,u16 num)
{
	Display_1_WEI(wei, num/1000,0);//显示千位
	Display_1_WEI(wei+1, num%1000/100,0);//显示百位
	Display_1_WEI(wei+2, num%100/10,0);//显示十位
	Display_1_WEI(wei+3, num%10,0);//显示个位
}

//显示小于10的两位小数函数
void Display_1_2Wei_XS(u8 wei,float num)
{
	num=num*100;//将小数扩大100倍
	Display_1_WEI(wei, (int)num%1000/100,1);//显示百位
	Display_1_WEI(wei+1, (int)num%100/10,0);//显示十位
	Display_1_WEI(wei+2, (int)num%10,0);//显示个位
}

//显示小于100的两位小数函数
void Display_2_2Wei_XS(u8 wei,float num)
{
	num=num*100;//将小数扩大100倍
	Display_1_WEI(wei, num/1000,0);//显示千位
	Display_1_WEI(wei+1, (int)num%1000/100,1);//显示百位
	Display_1_WEI(wei+2, (int)num%100/10,0);//显示十位
	Display_1_WEI(wei+3, (int)num%10,0);//显示个位
}

//比赛数码管显示程序
void Display_water(float num)
{
	//前四位显示单价
	Display_1_WEI(1,12,0);//不显示(消隐)
	Display_1_WEI(2,0,1);
	Display_1_WEI(3,5,0);
	Display_1_WEI(4,0,0);
	
	Display_2_2Wei_XS(5,num);
}

