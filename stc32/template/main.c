#include <STC32G.H>

void system();

void Delay10us()		//@35MHz
{
	unsigned long i;

	_nop_();
	i = 86UL;
	while (i) i--;
}

void Delay1ms()		//@35MHz
{
	unsigned long i;

	_nop_();
	_nop_();
	_nop_();
	i = 8748UL;
	while (i) i--;
}

void DelayMs(unsigned int n)
{
    while(n--)
        Delay1ms();
}

void Delay10Nus(unsigned int n)
{
    while(n--)
        Delay10us();
}



void main()
{
    system();
    while(1)
    {}
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