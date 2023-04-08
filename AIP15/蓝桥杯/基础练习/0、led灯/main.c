#include<STC15F2K60S2.h>
#include<intrins.h>
void delay(void)
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 9;
	j = 104;
	k = 139;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void ledinit()
{
	int i;
	P0 = 0xff;
	for(i=0; i<9; i++)
	{
		delay();
		P0 = P0>>1;
	}
}
	
void main()
{
	//单片机初始化
	P2 = 0xa0;
	P0 = 0x00;
	P2 = 0x80;
	P0 = 0xff;
	
	//实验程序
	while(1)
	{
		ledinit();
	}
	
}