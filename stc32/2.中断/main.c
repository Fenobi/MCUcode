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

void Timer0_Init(void)		//50΢��@12.000MHz
{
	AUXR |= 0x80;			//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TL0 = 0xA8;				//���ö�ʱ��ʼֵ
	TH0 = 0xFD;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
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