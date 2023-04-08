/* 头文件声明区 */
#include <STC15F2K60S2.H>//单片机寄存器专用头文件
#include <Init.h>//初始化底层驱动专用头文件
#include <Led.h>//Led底层驱动专用头文件
#include <Key.h>//按键底层驱动专用头文件
#include <Seg.h>//数码管底层驱动专用头文件
#include "onewire.h"//温度底层驱动专用头文件
#include "ds1302.h"//时钟底层驱动专用头文件

/* 变量声明区 */
unsigned char Key_Val,Key_Down,Key_Old,Key_Up;//按键专用变量
unsigned char Key_Slow_Down;//按键减速专用变量
unsigned char Seg_Buf[8] = {10,10,10,10,10,10,10,10};//数码管显示数据存放数组
unsigned char Seg_Point[8] = {0,0,0,0,0,0,0,0};//数码管小数点数据存放数组
unsigned char Seg_Pos;//数码管扫描专用变量
unsigned int Seg_Slow_Down;//数码管减速专用变量
unsigned char ucLed[8] = {0,0,0,0,0,0,0,0};//Led显示数据存放数组
unsigned char Seg_Disp_Mode;//数码管显示模式变量 0-温度显示 1-时间显示 2-参数设置
unsigned char ucRtc[3] = {0x23,0x59,0x55};//系统时钟数据储存数组
unsigned char Temperature_Parameter_Disp = 23;//温度参数显示值
unsigned char Temperature_Parameter_Ctrol = 23;//温度参数控制值
unsigned char Timer_100Ms;//一百毫秒计时变量
float Temperature;//实时温度变量
bit Time_Flag;//时钟显示标志位 0-显示小时分钟 1-显示分钟秒钟
bit Relay_Work_Mode;//继电器工作模式变量 0-温度控制 1-时钟控制
bit Relay_Enable_Flag;//继电器使能标志位 0-不使能 1-使能
bit Hour_Flag;//系统整点标志位
bit Led_Star_Flag;//Led闪烁标志位

/* 键盘处理函数 */
void Key_Proc()
{
	if(Key_Slow_Down) return;
	Key_Slow_Down = 1;//键盘减速程序

	Key_Val = Key_Read();//实时读取键码值
	Key_Down = Key_Val & (Key_Old ^ Key_Val);//捕捉按键下降沿
	Key_Up = ~Key_Val & (Key_Old ^ Key_Val);//捕捉按键上降沿
	Key_Old = Key_Val;//辅助扫描变量
	
	if(Seg_Disp_Mode == 1) //处于时钟显示模式
	{
		if(Key_Old == 17) //长按按键S17
			Time_Flag = 1;//显示分钟秒钟
		else
			Time_Flag = 0;//显示小时分钟
	}
	
	switch(Key_Down)
	{
		case 12://切换按键
			if(++Seg_Disp_Mode == 3) //循环切换数码管显示模式
			{
				Seg_Disp_Mode = 0;//返回温度显示界面
				Temperature_Parameter_Ctrol = Temperature_Parameter_Disp;//设置参数生效
			}
		break;
		case 16://自加按键
			if(Seg_Disp_Mode == 2) //处于参数设置模式
			{
				if(++Temperature_Parameter_Disp == 100) //限制上限
					Temperature_Parameter_Disp = 99;
			}
		break;
		case 17://自减按键
			if(Seg_Disp_Mode == 2) //处于参数设置模式
			{
				if(--Temperature_Parameter_Disp == 9) //限制下限
					Temperature_Parameter_Disp = 10;
			}
		break;
		case 13://切换按键
			Relay_Work_Mode ^= 1;//切换继电器工作模式
		break;
	}
}

/* 信息处理函数 */
void Seg_Proc()
{
	if(Seg_Slow_Down) return;
	Seg_Slow_Down = 1;//数码管减速程序
	
	/* 信息读取区域 */
	Temperature = rd_temperature();//实时读取温度值
	Read_Rtc(ucRtc);//实时读取时钟数据
	
	/* 数据显示区域 */
	Seg_Buf[0] = 11;//统一标识符 U
	Seg_Buf[1] = Seg_Disp_Mode + 1;//界面编号
	switch(Seg_Disp_Mode)
	{
		case 0://温度显示
			Seg_Point[6] = 1;//使能小数点
			Seg_Buf[5] = (unsigned char)Temperature / 10 % 10;
			Seg_Buf[6] = (unsigned char)Temperature % 10;
			Seg_Buf[7] = (unsigned int)(Temperature * 10) % 10;
		break;
		case 1://时间显示
			Seg_Point[6] = 0;//熄灭小数点
			Seg_Buf[3] = ucRtc[0 + (unsigned char)Time_Flag] / 16;
			Seg_Buf[4] = ucRtc[0 + (unsigned char)Time_Flag] % 16;
			Seg_Buf[5] = 12;//标识符 -
			Seg_Buf[6] = ucRtc[1 + (unsigned char)Time_Flag] / 16;
			Seg_Buf[7] = ucRtc[1 + (unsigned char)Time_Flag] % 16;			
		break;
		case 2://参数设置
			Seg_Buf[3] = Seg_Buf[4] = Seg_Buf[5] = 10;//熄灭数码管
			Seg_Buf[6] = Temperature_Parameter_Disp / 10;
			Seg_Buf[7] = Temperature_Parameter_Disp % 10;
		break;
	}
}

/* 其他显示函数 */
void Led_Proc()
{
	if(ucRtc[1] == 0 && ucRtc[2] == 0) //系统达到整点
		Hour_Flag = 1;
	if(ucRtc[2] == 0x05)
		Hour_Flag = 0;
	
	/* Led显示区域 */
	ucLed[0] = Hour_Flag;
	ucLed[1] = !Relay_Work_Mode;
	ucLed[2] = Led_Star_Flag?Relay_Enable_Flag:0;
	
	/* 继电器使能区域 */
	if(Relay_Work_Mode == 0) //处于温度控制模式
		Relay_Enable_Flag = (unsigned char)Temperature / Temperature_Parameter_Ctrol;
	else //处于时钟控制模式
		Relay_Enable_Flag = Hour_Flag;
}

/* 定时器0中断初始化函数 */
void Timer0Init(void)		//1毫秒@12.000MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x18;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;    //定时器中断0打开
	EA = 1;     //总中断打开
}

/* 定时器0中断服务函数 */
void Timer0Server() interrupt 1
{  
	if(++Key_Slow_Down == 10) Key_Slow_Down = 0;//键盘减速专用
	if(++Seg_Slow_Down == 500) Seg_Slow_Down = 0;//数码管减速专用
	if(++Seg_Pos == 8) Seg_Pos = 0;//数码管显示专用
	Seg_Disp(Seg_Pos,Seg_Buf[Seg_Pos],Seg_Point[Seg_Pos]);
	Led_Disp(Seg_Pos,ucLed[Seg_Pos]);
	Relay(Relay_Enable_Flag);
	if(++Timer_100Ms == 100)
	{
		Timer_100Ms = 0;
		Led_Star_Flag ^= 1;
	}
}

/* 延时函数 */
void Delay750ms()		//@12.000MHz
{
	unsigned char i, j, k;
	i = 35;
	j = 51;
	k = 182;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


/* Main */
void main()
{
	rd_temperature();//上电读取一次温度
	Delay750ms();//延时750毫秒避免显示错误数据
	Set_Rtc(ucRtc);//上电设置时钟数据
	System_Init();
	Timer0Init();
	while (1)
	{
		Key_Proc();
		Seg_Proc();
		Led_Proc();
	}
}