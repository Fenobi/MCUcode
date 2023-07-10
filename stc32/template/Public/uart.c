#include "uart.h"

bit busy;
int wptr;
char rptr;
char buffer[64];

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

void UART4_int (void) interrupt 18
{
	if(S4CON & 0x02)
	{
		S4CON &= ~0x02;  //Clear Tx flag  清楚发送标志位
		busy=0;
	}
	if(S4CON & 0x01)
	{
		S4CON &= ~0x01;  //Clear Rx flag	清楚接收标志位
		buffer[wptr++]= S4BUF;
		wptr &= 0xff;
	}
}

//串口初始化
void UART1_config()
{
	SCON= 0x50;		//可变波特率 8位数据方式 允许串口接收数据
	T2L = Baudrate1;		//定时器2
	T2H = Baudrate1>>8;
	AUXR= 0x15;		//选择定时器2作为波特率发射器
	wptr = 0x00;
	rptr = 0x00;
	busy= 0;

		// TR1 = 0;
		// AUXR &= ~0x01;                                        //S1 tmr Use Timer1;
		// AUXR |=  (1<<6);                                      //Timer1 set as 1T mode
		// TMOD &= ~(1<<6);                                      //Timer1 set As Timer
		// TMOD &= ~0x30;                                        //Timer1_16bitAutoReload;
		// TH1 = (u8)(Baudrate1 / 256);
		// TL1 = (u8)(Baudrate1 % 256);
		// ET1 = 0;    				                           	//禁止中断
		// INTCLKO &= ~0x02;		                               	//不输出时钟
		// TR1  = 1;


    SCON = (SCON & 0x3f) | 0x40;                              	//UART1模式, 0x00: 同步移位输出, 0x40: 8位数据,可变波特率, 0x80: 9位数据,固定波特率, 0xc0: 9位数据,可变波特率
//  PS  = 1;                                                  	//高优先级中断
    ES  = 1;                                                  	//允许中断
    REN = 1;                                                 	 //允许接收
    P_SW1 &= 0x3f;
//  P_SW1 |= 0x00;                                            	//UART1 switch to, 0x00: P3.0 P3.1, 0x40: P3.6 P3.7, 0x80: P1.6 P1.7, 0xC0: P4.3 P4.4

}

void SetTimer2Baudraye(u32 dat)
{
	S4CON = 0x10;                       //8位数据, 使用Timer2做波特率发生器, 允许接收
	T2H = dat>>8;
	T2L = dat;
	AUXR = 0x14;
}

void UART4_config(u16 tmr)              // 选择时钟源, 2: 使用Timer2做波特率, 其它值: 使用Timer4做波特率.
{
	if(tmr == 2)													//使用TIM2作为波特率时钟源
	{
		SetTimer2Baudraye(Baudrate4);
	}
	else
	{
		S4CON = 0x50;                       //8位数据, 使用Timer4做波特率发生器, 允许接收
		T4H = Baudrate4>>8;
		T4L = Baudrate4;
		T4T3M = 0xA0;												//定时器4开始工作，不分频
	}
//		P_SW2 &= ~0x04;                   //UART4 switch bit2 to: 0: P0.2 P0.3选择引脚
	P_SW2 |= 0x04;                      //UART4 switch bit2 to: 1: P5.2 P5.3选择引脚 P52:RX P53:TX 
	wptr = 0x00;												//三个标志位清零
	rptr = 0x00;
	busy= 0;

	IE2 |= 0x10;                        //允许UART4中断
	
}

//发送单个字符
void UART1_PutChar(char dat)
{
    while(busy);
    busy=1;
    SBUF=dat;
}

void UART4_PutChar(char ch)
{
	while(busy);
	busy=1;
	S4BUF = ch;
}

//接收单个字符
char UART1_GetChar()
{
    return SBUF;
}

char UART4_GetChar(void)
{  
  return (S4BUF);
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

void UART4_PutStr(char *st)
{
  while(*st)
  {
    UART4_PutChar(*st++);
  }
}