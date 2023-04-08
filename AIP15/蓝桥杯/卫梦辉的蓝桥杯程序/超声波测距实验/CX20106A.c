#include "CX20106A.h"

//超声波模块初始化函数
void US_init(void)
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//c设置定时器模式
	TL0 = 0x00;		
	TH0 = 0x00;		
	TF0 = 0;		
}

//软件延时函数
void Delay10us()		//@12.000MHz
{
	unsigned char i;
	_nop_();
	_nop_();
	i = 27;
	while (--i);
}

//超声波模块获得距离函数（函数还回距离值 单位：cm）
u16 Get_distance(void)    //12M
{
	u8 i = 8;
	u16 distance;
	while(i--)
	{
		P10 = 1;
		Delay10us();      //延时时间有待探究
		P10 = 0;
		Delay10us();
	}
	
	TL0 = 0;		
	TH0 = 0;
	TR0 = 1;
	while(P11 && (TF0 == 0));
	TR0 = 0;
	
	if(TF0)
	{
		TF0 = 0; distance = 99;
	}
	else
	{
		distance = ((TH0<<8)|(TL0))*0.0014167;    //得到<100cm的测量距离
	}
    return distance;           
}

//————————————————
//版权声明：本文为CSDN博主「Dream_言十」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
//原文链接：https://blog.csdn.net/weixin_43487914/article/details/107498385