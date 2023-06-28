#include <STC32G.H>

bit busy;
int wptr;
char rptr;
char buffer[64];

void Delay200ms()		//@22.1184MHz
{
	unsigned long i;

	_nop_();
	_nop_();
	i = 1105918UL;
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
		wptr &= 0xff;
	}
}

//串口初始化
void UartInit()//波特率:115200
{
	SCON= 0x50;		//可变波特率 8位数据方式 允许串口接收数据
	T2L = 0xD0;		//定时器2
	T2H = 0xFF;
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
    EAXFR=1;
    CKCON= 0x00;
    WTST= 0x00;
    UartInit();
    EA = 1;
    ES = 1;
    while(1)
    {
        UART1_PutStr(buffer);
        Delay200ms();
        
    }
}