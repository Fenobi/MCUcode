#include <STC32G.H>

sbit PWM=P0^0;

static unsigned char i;
static unsigned char ZKB,count;

void tm0_isr() interrupt 1
{
    count++;
	if(count>100)
    {
        count=0;
    }
    
    if(count==0)
    {
        PWM=1;
    }
    else if(count==ZKB)
    {
        PWM=0;    
    }
    
}

void Timer0_Init(void)		//50微秒@12.000MHz
{
	AUXR |= 0x80;			//定时器时钟1T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0xA8;				//设置定时初始值
	TH0 = 0xFD;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
}

void Delay1ms()		//@12.000MHz
{
	unsigned long i;

	_nop_();
	_nop_();
	_nop_();
	i = 2998UL;
	while (i) i--;
}

void main()
{
 char i;
    WTST = 0;
    EAXFR = 1;
    CKCON = 0;
       P0M0 = 0x01; P0M1 = 0x00; 


	Timer0_Init();
    ET0 = 1;
	EA = 1;
	while(1)
    {
        for(i=1;i<100;i++)
        {
            ZKB=i;
            Delay1ms();		//@12.000MHz
            Delay1ms();		//@12.000MHz
            Delay1ms();		//@12.000MHz
            Delay1ms();		//@12.000MHz
            Delay1ms();		//@12.000MHz
            Delay1ms();		//@12.000MHz
            Delay1ms();		//@12.000MHz
            Delay1ms();		//@12.000MHz
            Delay1ms();		//@12.000MHz
            Delay1ms();		//@12.000MHz

        }
         for(i=99;i>0;i--)
        {
            ZKB=i;
            Delay1ms();		//@12.000MHz
            Delay1ms();		//@12.000MHz
            Delay1ms();		//@12.000MHz
            Delay1ms();		//@12.000MHz
            Delay1ms();		//@12.000MHz
            Delay1ms();		//@12.000MHz
            Delay1ms();		//@12.000MHz
            Delay1ms();		//@12.000MHz
            Delay1ms();		//@12.000MHz
            Delay1ms();		//@12.000MHz

        }

    }
}