#include "smg.h"
#include "pcf8591.h"

float VOL=0;
u8 gsmg_code[8]=0;
u8 flag=0;
u8 time=0;

void Timer0_Isr(void) interrupt 1
{
	
}

void Timer0_Init(void)		//50毫秒@12.000MHz
{
	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0xB0;				//设置定时初始值
	TH0 = 0x3C;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;				//使能定时器0中断
}

void Timer1_Isr(void) interrupt 3
{
}

void Timer1_Init(void)		//50毫秒@12.000MHz
{
	AUXR &= 0xBF;			//定时器时钟12T模式
	TMOD &= 0x0F;			//设置定时器模式
	TL1 = 0xB0;				//设置定时初始值
	TH1 = 0x3C;				//设置定时初始值
	TF1 = 0;				//清除TF1标志
	TR1 = 1;				//定时器1开始计时
	ET1 = 1;				//使能定时器1中断
	EA = 1;
}


void vol_display()
{
	u8 dat;
	dat=AD_read(0x43);//读电压
	//AD_write(dat);
	VOL=dat/51.0;
	gsmg_code[0]=(u8)VOL;
	gsmg_code[1]=(u16)(VOL*100)/10%10;
	gsmg_code[2]=(u16)(VOL*100)%10;

	HC138_Y(6); 
	SMG_Display_Wei(1);
	HC138_Y(7); 
	SMG_GPIO=0xc1;
	Delay_ms(2); 

	HC138_Y(6); 
	SMG_Display_Wei(6);
	HC138_Y(7); 
	SMG_Display_Digital(gsmg_code[0], 1);
	Delay_ms(2); 
	
	HC138_Y(6); 
	SMG_Display_Wei(7);
	HC138_Y(7); 
	SMG_Display_Digital(gsmg_code[1], 0);
	Delay_ms(2); 
	
	HC138_Y(6); 
	SMG_Display_Wei(8);
	HC138_Y(7); 
	SMG_Display_Digital(gsmg_code[2], 0);
	Delay_ms(2); 
}


void main()
{	
	while(1)
	{		
		vol_display();
			
	}		
}