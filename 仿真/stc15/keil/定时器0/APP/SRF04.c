#include "SRF04.h"

sbit TR = P6^2;    //发射控制引脚
sbit ECHO = P6^3;  //接收引脚

/************************初始化*****************************/
void SRF04_Init(void)//SRF04初始化函数（使用定时器0）
{
		AUXR &= 0x7F;			//定时器时钟12T模式
    TMOD |= 0x01;
    TH0 = 0x00;
    TL0 = 0x00;
    TR0 = 0;//先关闭定时器0
		TR=0;//出发引脚首先拉低
}

void SRF04_Delay20us()//@11.0592MHz
{
	unsigned char data i;
	_nop_();
	_nop_();
	i = 57;
	while (--i);
}


/********************读距离值函数***********************/
u16 Get_Distance(void)
{
	float temp;
	u16 result;
	TR=1;//触发引脚发出11us的触发信号（至少10us）
	SRF04_Delay20us();
	TR=0;
	while(!ECHO );//度过回响信号的低电平
	TR0=1;//开启定时器0
	while(ECHO && TH0<0x13);//度过回响信号高电平
	TR0=0;//关闭定时器0
	temp=TH0*256+TL0;//最终us时间
	temp/=1000.0;//最终ms时间
	temp*=17.3;//距离(cm) (17=光速34cm/ms 除2)
	result=temp;//四舍五入
	if(temp-result>=0.5)
	{
		result+=1;
	}
	TH0=0;//清除定时器0计数值
	TL0=0;
	return result;
}





