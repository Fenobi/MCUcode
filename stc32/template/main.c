#include <STC32G.H>

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
    while(1)
    {}
}