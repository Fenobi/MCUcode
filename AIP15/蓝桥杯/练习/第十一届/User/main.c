/* 
		大模板 V3 更新说明 若非特殊需求 无需使用此版本 （因为我觉得这样调用起来还是稍微有点儿麻烦的）
		
		优化设计串口程序时 内存容易溢出的问题
		
		例程调用如下：
		
		-------------Led相关-------------
		Led X 开 -> Function_Buf[X] |= 1
		Led X 关 -> Function_Buf[X] &= 0
		Led X 开关切换 -> Function_Buf[X] ^= 1
		
		-------------Seg相关-------------
		Point X 开 -> Function_Buf[X] |= 1  << 4
		Point X 关 -> Function_Buf[X] &= 0  << 4
		Point X 开关切换 -> Function_Buf[X] ^= 1  << 4
		
*/

/* 宏定义声明区域 */
#define Key_Slow 10 //按键减速时间
#define Seg_Slow 500 //数码管减速时间
#define Uart_Slow 200 //串口减速时间
#define Uart_Max_Commad 10 //串口指令长度上限

/* 头文件声明区域 */
#include <Init.h> //初始化专用头文件
#include <Key.h> //按键专用头文件
#include <Seg.h> //数码管专用头文件
#include <Led.h> //Led专用头文件
#include <Uart.h> //串口专用头文件
#include <pcf8591.h>
#include <ds18b20.h>

/* 变量声明区域 */
unsigned int Proc_Slow_Down;//函数减速专用变量
unsigned char Key_Val,Key_Old;//按键扫描专用变量
unsigned char Scan_Pos;//动态扫描专用变量
unsigned char Seg_Buf[8] = {10,10,10,10,10,10,10,10};//显示数据存放数组 默认熄灭
unsigned char Function_Buf[8] = {0,0,0,0,0,0,0,0};//功能数据存放数组 高位-Led状态 低位-小数点状态
unsigned char Uart_Recv[10];//串口接收数据储存数组 默认10个字节 若接收数据较长 可更改最大字节数
unsigned char Uart_Recv_Index;//串口接收数组指针
unsigned char Uart_Send[10];//串口接收数据储存数组 默认10个字节 若发送数据较长 可更改最大字节数
u8 Temperature;
u8 Temperature_A[] = {0, 0};
u8 Temperature_B[] = {30,20};
u8 mode = 1;
u8 mode_min=1;
u8 Temperature_Params_Index;
u8 error_flag;

/* 按键处理函数 */
void Key_Proc()
{
	unsigned char Key_Up,Key_Down;//定义局部变量减小内存占用
	if(Proc_Slow_Down % Key_Slow) return;//按键减速程序

	Key_Val = Key_BTN_Read(); // 读取按键键码值
	Key_Down = Key_Val & (Key_Val ^ Key_Old);//捕捉按键下降沿
	Key_Up = ~Key_Val & (Key_Val ^ Key_Old);//捕捉按键上降沿
	Key_Old = Key_Val;//辅助扫描变量
	switch(Key_Down)
	{
		case 4:
			mode ^= 1;
			if (mode==0)
			{
				Temperature_A[0] = Temperature_B[0];
				Temperature_A[1] = Temperature_B[1];
				Temperature_Params_Index = 0;
			}
			else
			{
				if(Temperature_A[0]>Temperature_A[1])
				{
					Temperature_B[0] = Temperature_A[0];
					Temperature_B[1] = Temperature_A[1];
					error_flag = 0;
				}
				else
				{
					error_flag = 1;
				}
				
			}	
			break;
		case 5:
			mode_min ^= 1;
			Temperature_Params_Index ^= 1;
			break;
		case 6:
			++Temperature_A[Temperature_Params_Index];
			if (Temperature_A[Temperature_Params_Index] > 100)
				Temperature_A[Temperature_Params_Index] = 99;
			break;
		case 7:
			--Temperature_A[Temperature_Params_Index];
			if (Temperature_A[Temperature_Params_Index] == 255 )
				Temperature_A[Temperature_Params_Index] = 0;
	}
		
}

/* 信息处理函数 */
void Seg_Proc()
{
	if (Proc_Slow_Down % Seg_Slow)
		return; // 信息减速程序
	Temperature = ds18b20_read_temperture();

	if(mode)
	{
		Seg_Buf[0] = 11; // 标识符C
		Seg_Buf[3] = 10;
		Seg_Buf[4] = 10;
		Seg_Buf[6] = (unsigned char)Temperature / 10 % 10;
		Seg_Buf[7] = (unsigned char)Temperature % 10;
	}
	else
	{
		Seg_Buf[0] = 12; // 标识符C
		Seg_Buf[3] = Temperature_A[0] / 10 % 10;
		Seg_Buf[4] = Temperature_A[0] % 10;
		Seg_Buf[6] = Temperature_A[1] / 10 % 10;
		Seg_Buf[7] = Temperature_A[1] % 10;
	}
	
}

/* 其他处理函数 */
void Led_Proc()
{
	u8 i;
	Function_Buf[0] = (Temperature > Temperature_A[0]);
	Function_Buf[1] = (Temperature <= Temperature_A[0] && Temperature >= Temperature_A[1]);
	Function_Buf[2] = (Temperature < Temperature_A[1]);
	Function_Buf[3] = error_flag;
	for (i = 0; i < 3; i++)
	{
		if (Function_Buf[i] == 1)
		{
			AD_write(51 * (4 - i));
			break;
		}
	}
}

/* 串口处理函数 */
void Uart_Proc()
{
	if(Proc_Slow_Down % Uart_Slow) return;//串口减速程序	
	
}

/* 定时器0初始化函数 */
void Timer0Init(void)		//1毫秒@12.000MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;		//定时器0中断打开
	EA = 1;			//总中断打开
}

/* 定时器0中断服务函数 */
void Timer0Server() interrupt 1
{
	if(++Proc_Slow_Down == 500) Proc_Slow_Down = 0;//减速专用
	if(++Scan_Pos == 8) Scan_Pos = 0;//扫描专用
	Seg_Disp(Scan_Pos,Seg_Buf[Scan_Pos],Function_Buf[Scan_Pos] & 0xF0);//数码管显示
	Led_Disp(Scan_Pos,Function_Buf[Scan_Pos] & 0x0F);//Led显示
}

/* 串口1中断服务函数 */
void Uart1Server() interrupt 4
{
	if(RI == 1 && Uart_Recv_Index < Uart_Max_Commad) //串口接收数据
	{
		Uart_Recv[Uart_Recv_Index] = SBUF;
		Uart_Recv_Index++;
		RI = 0;
	}
}

void main()
{
	ds18b20_read_temperture();
	Delay_ms(750);
	Sys_Init();//上电系统初始化
	//UartInit();	//串口初始化
	Timer0Init();//定时器0初始化
	while(1)
	{
		Key_Proc();
		Seg_Proc();
		Led_Proc();
		Uart_Proc();
	}
}
