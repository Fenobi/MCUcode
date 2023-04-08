#include <STC15F2K60S2.h>
#include <intrins.h>

//定时器/计数器T0用来计时，定时器/计数器T1用来计数
//T0为P3^4管脚，T1为P3^5管脚

long int Frequent = 0;
unsigned char timer1 = 0, timer2 = 0;
bit Flag = 0;
unsigned char wei = 0x80;

code unsigned char tab[10] = {0xc0, 0xf9, 0xa4, 0xb0, 
																0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
unsigned char dp[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char dpbuff[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void TimerInit(void)		//1毫秒@11.0592MHz
{
	TMOD |= 0x15;		//设置定时器模式
	TL0 = 0;		//设置定时初值
	TH0 = 0;		//设置定时初值
	
	TL1 = 0xCD;
	TH1 = 0xD4;
	
	TF0 = 0;		//清除TF0标志
	TF1 = 0;
	
	EA = 1;
	ET0 = 1;
	ET1 = 1;
	
	TR0 = 1;		//定时器0开始计时
	TR1 = 1;
}

void display()
{
	unsigned char i;
	for (i=0; i<8; i++)  
	{
		P2 = 0x00;              //选位
		P0 = wei>>i;
		P2 = 0xC0;
		_nop_();_nop_();
		P2 = 0x00;

		P0 = tab[dp[i]];
 		P2 = 0xE0;
		_nop_();_nop_();
		_nop_();_nop_();
		_nop_();_nop_();
		P2 = 0x00;
	}
}

void Close()
{
	P2 = 0xA0;
	P0 = 0x00;
	P2 = 0x00;
}

void main()
{
	Close();
	TimerInit();
	while(1)
	{
		if (Flag)
		{
			Flag = 0;
			TR0 = 0;
			TR1 = 0;
		
			
			Frequent = Frequent + TL0 + TH0*256;
			Frequent = Frequent*5;
			
			dpbuff[7] = Frequent/10000000;
			dpbuff[6] = Frequent/1000000%10;
			dpbuff[5] = Frequent/100000%10;
			dpbuff[4] = Frequent/10000%10;
			dpbuff[3] = Frequent/1000%10;
			dpbuff[2] = Frequent/100%10;
			dpbuff[1] = Frequent/10%10;
			dpbuff[0] = Frequent%10;
			
			dp[7] = dpbuff[7];
			dp[6] = dpbuff[6];
			dp[5] = dpbuff[5];
			dp[4] = dpbuff[4];
			dp[3] = dpbuff[3];
			dp[2] = dpbuff[2];
			dp[1] = dpbuff[1];
			dp[0] = dpbuff[0];	
			
			Frequent = 0;
			
			TL0 = 0;
			TH0 = 0;
			
			TL1 = 0xCD;		//设置定时初值
			TH1 = 0xD4;		//设置定时初值
			
			TR0 = 1;
			TR1 = 1;			
		}
		display();
	}
}


void Timer1inter() interrupt 3
{
	TL1 = 0xCD;		//设置定时初值
	TH1 = 0xD4;		//设置定时初值

	if (++timer1 == 200)
	{
		timer1 = 0;
		Flag = 1;
	}	
}

void Timer0inter() interrupt 1
{
	TL0 = 0;
	TH0 = 0;
	
	Frequent = Frequent + 65536;
}












