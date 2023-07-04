#include "public.h"
#include "12864_st7920c.h"
#include "time.h"
#include "uart.h"

void system();

extern int wptr;
extern char rptr;
extern char buffer[64];

void main()
{
    char txt[32];
    int num;
    
    system();
    Timer0_init();
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
        DelayMs(200);
    }
}

void system()
{
    P1M1 = 0;   P1M0 = 0;   //设置为准双向口
    P3M1 = 0;   P3M0 = 0;   //设置为准双向口
    P4M1 = 0;   P4M0 = 0;   //设置为准双向口
    P5M1 = 0;   P5M0 = 0;   //设置为准双向口
    P6M1 = 0;   P6M0 = 0;   //设置为准双向口
    P7M1 = 0;   P7M0 = 0;   //设置为准双向口 
    EAXFR=1;
    CKCON= 0x00;
    WTST= 0x00;
}