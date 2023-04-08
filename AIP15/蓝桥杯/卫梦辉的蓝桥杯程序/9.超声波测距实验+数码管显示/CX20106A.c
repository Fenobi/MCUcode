#include "CX20106A.h"//超声波函数头文件

//切记，计算距离不使用分频
sbit TX = P1^0;  //发射引脚
sbit RX = P1^1;  //接收引脚

//12us
void Delay12us(void)//@11.0592MHz
{
	unsigned char i;
	_nop_();
	_nop_();
	_nop_();
	i = 30;
	while (--i);
}

void send_wave(void)//发送八段脉冲波(40Khz)
{
	unsigned char i = 8;
	while(i --)
	{
		TX = 1;
		Delay12us();
		TX = 0;
		Delay12us();
	}
}

void CSB_Init(void)//超声波定时器初始化
{
	AUXR |= 0x80;
  TMOD |= 0x10;  //配置定时器工作模式 
  TH1 = 0;
  TL1 = 0;  
//  EA = 1;	
}

//超声波模块获得距离函数（函数还回距离值 单位：cm）
u16 Get_Distance(void) //@11.0592MHz
{
	u16 distance,time;
  send_wave();  //发送方波信号
  TR1 = 1;  //启动计时
	while((RX == 1) && (TF1 == 0));  //等待收到脉冲，没有计满溢出
	TR1 = 0;  //关闭计时

	//发生溢出
	if(TF1 == 1)
	{
		TF1 = 0;
		distance = 100;  //无返回
	}
	else
	{
		/**  计算时间  */
		time=TH1*256+TL1;
		distance = (unsigned int)(time*0.017);  //计算距离取整数（单位CM）				
	}
	TH1 = 0;
	TL1 = 0;
			
  return distance;           
}
