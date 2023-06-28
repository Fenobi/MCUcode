#include <STC32G.H>
#include "stdio.h"
bit busy;
int wptr;
char rptr;
char buffer[64];

void Delay200ms()		//@35MHz
{
	unsigned long i;

	_nop_();
	_nop_();
	i = 1749998UL;
	while (i) i--;
}

void UART1_int (void) interrupt 4
{
	if(TI)// TI:串口1发送完成中断请求标志。需要软件清零。
	{
		TI= 0;
		busy= 0;
	}
	if(RI)// RI:串口1接收完成中断请求标志。需要软件清零。
	{
		RI= 0;
		buffer[wptr++]= SBUF;
		wptr &= 0x0f;
	}
}

//串口初始化
void UartInit()//波特率:115200
{
	SCON= 0x50;		//可变波特率 8位数据方式 允许串口接收数据
	T2L = (65536 - 35000000UL / 115200 / 4);//定时器2
	T2H = (65536 - 35000000UL / 115200 / 4) >> 8;
	AUXR= 0x15;		//选择定时器2作为波特率发射器
	wptr = 0x00;
	rptr = 0x00;
	busy= 0;
    SCON = (SCON & 0x3f) | 0x40;//UART1模式, 0x00: 同步移位输出, 0x40: 8位数据,可变波特率, 0x80: 9位数据,固定波特率, 0xc0: 9位数据,可变波特率

    ES  = 1;//允许中断
    REN = 1;//允许接收
    P_SW1 &= 0x3f;
}

//发送单个字符
void UART1_PutChar(char dat)
{
    while(busy);
    busy=1;
    SBUF=dat;
}

//接收单个字符
char UART1_GetChar()
{
    return SBUF;
}

//发送字符串
void UART1_PutStr(char *p)
{
	char *p1;
	p1=p;
	while(*p1)
	{
		UART1_PutChar(*p1++);
	}
}

void main()
{
    int num=0;
    char txt[32];
    P1M1 = 0;   P1M0 = 0;   //设置为准双向口
    P3M1 = 0;   P3M0 = 0;   //设置为准双向口
    P4M1 = 0;   P4M0 = 0;   //设置为准双向口
    P5M1 = 0;   P5M0 = 0;   //设置为准双向口
    P6M1 = 0;   P6M0 = 0;   //设置为准双向口
    P7M1 = 0;   P7M0 = 0;   //设置为准双向口 
    EAXFR=1;
    CKCON= 0x00;
    WTST= 0x00;
    UartInit();
    EA = 1;
    ES = 1;
    while(1)
    {
        if(rptr != wptr)
	 	{
	 		UART1_PutChar(buffer[rptr++]);
	 		rptr &= 0x0f;
	 	}
        sprintf(txt, "num:%d",num++);
        UART1_PutStr(txt);
        Delay200ms();
    }
}