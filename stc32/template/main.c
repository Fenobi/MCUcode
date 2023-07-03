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
    P1M1 = 0;   P1M0 = 0;   //����Ϊ׼˫���
    P3M1 = 0;   P3M0 = 0;   //����Ϊ׼˫���
    P4M1 = 0;   P4M0 = 0;   //����Ϊ׼˫���
    P5M1 = 0;   P5M0 = 0;   //����Ϊ׼˫���
    P6M1 = 0;   P6M0 = 0;   //����Ϊ׼˫���
    P7M1 = 0;   P7M0 = 0;   //����Ϊ׼˫��� 
    EAXFR=1;
    CKCON= 0x00;
    WTST= 0x00;
}