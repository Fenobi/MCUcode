#include "usart.h"//串口通信函数头文件
 

//***************串口初始化设置******************************************
void Init_Uart()
{
	AUXR=0x00;  
	SCON=0x50;  //0101 0000；工作在方式1，异步8位UART并且允许接收 即REN=1
	TMOD=0x20;  //设置定时器T1工作在方式2，8位自动重装，可用作波特率发生器
	TH1=0xfd;   //设置波特率为9600kbps，数值可查表找到
	TL1=0xfd;   //
	EA=1;       //打开中断总开关
	ES=1;       // 允许串口中断
	TR1=1;      //启动T0
}

//***************发送一个字节******************************************
void SendByte(unsigned char dat)
{
	SBUF=dat;
	while(TI==0);
	TI=0;
}


//重定向，否则无法使用printf函数
char putchar(char ch)
{	
	SendByte(ch);
  return ch;	
}

//***************发送一个字符串******************************************
void SendString(unsigned char *str)
{
	while(*str !='\0')		
		SendByte(*str++);
}

//***************串口中断服务子程序******************************************

unsigned char Rdata_flag;//字符串接收完成标志（接收完成Rdata_flag置1）
unsigned char Rdata;//接收缓存变量
unsigned char R_data[15];//接收缓存数组
unsigned char Rdata_count;//计次变量

void ServiceUart() interrupt 4
{
	if(RI==1)
	{
		Rdata=SBUF;//从上位机接收到的数据
		RI=0;//软件清除接收完成标志
		
		if(Rdata !='\n')//判断接收到的数据是否是 \n
		{
			R_data[Rdata_count]=Rdata;//将接收到的数据储存到数组中
			Rdata_count++;//计次加1
		}
		else //接收到的数据是 \n 准备重新接收
		{
			R_data[Rdata_count]=Rdata;//将接收到的数据储存到数组中
			Rdata_count=0;//清除计次，准备数组从头开始装
			Rdata_flag=1;
		}
	}
}
