#include <STC15F2K60S2.h>

void Close_BUZZ();
void Init_IO();

void main()
{
	Close_BUZZ();
	Init_IO();
	while(1);
}

void Close_BUZZ()
{
	P2 = 0xA0;
	P0 = 0x00;
	P2 = 0x00;
}

void Init_IO()
{	
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xB8;		//设定定时初值
	TH1 = 0xB8;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	ES = 1;
	EA = 1; 
}

void IO() interrupt 4
{
	unsigned char temp;
	temp = SBUF;
	RI = 0;
	SBUF = temp;
	while(!TI);
	TI = 0;	
}






