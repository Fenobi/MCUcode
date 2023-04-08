#include "BYZ_48.h"//BYZ-48步进电机函数头文件
#include "delay.h"//延时函数头文件

//控制驱动BYZ-48步进电机的四个GPIO
sbit STEPA=P0^0;
sbit STEPB=P0^1;
sbit STEPC=P0^2;
sbit STEPD=P0^3;

//精度5.625/64度，一圈 4096 个换相

void BYZ_48_MOTOR1(u8 speed,bit FX)//控制步进电机旋转
{
	char i;
	if(FX==1)//顺时针旋转
	{
		for(i=0;i<8;i++)
		{
			switch(i)
			{
				case 0:STEPD=0;STEPC=0;STEPB=0;STEPA=1;break;
				case 1:STEPD=0;STEPC=0;STEPB=1;STEPA=1;break;
				case 2:STEPD=0;STEPC=0;STEPB=1;STEPA=0;break;
				case 3:STEPD=0;STEPC=1;STEPB=1;STEPA=0;break;
				case 4:STEPD=0;STEPC=1;STEPB=0;STEPA=0;break;
				case 5:STEPD=1;STEPC=1;STEPB=0;STEPA=0;break;
				case 6:STEPD=1;STEPC=0;STEPB=0;STEPA=0;break;
				case 7:STEPD=1;STEPC=0;STEPB=0;STEPA=1;break;			
			}
			Delay_ms(speed);
		}
	}
	else if(FX==0)//逆时针旋转
	{
		for(i=7;i>=0;i--)
		{
			switch(i)
			{
				case 0:STEPD=0;STEPC=0;STEPB=0;STEPA=1;break;
				case 1:STEPD=0;STEPC=0;STEPB=1;STEPA=1;break;
				case 2:STEPD=0;STEPC=0;STEPB=1;STEPA=0;break;
				case 3:STEPD=0;STEPC=1;STEPB=1;STEPA=0;break;
				case 4:STEPD=0;STEPC=1;STEPB=0;STEPA=0;break;
				case 5:STEPD=1;STEPC=1;STEPB=0;STEPA=0;break;
				case 6:STEPD=1;STEPC=0;STEPB=0;STEPA=0;break;
				case 7:STEPD=1;STEPC=0;STEPB=0;STEPA=1;break;			
			}
			Delay_ms(speed);
		}		
	}
}


void BYZ_48_MOTOR2(float Angle,bit FX)//控制步进电机以最快速度旋转特定角度
{
	char i;
	int MOTOR_count;
	
	MOTOR_count=Angle/0.703; //5.625/64*8=0.703, 计算换向次数
	
	if(FX==1)//顺时针旋转
	{
		while(MOTOR_count>0)
		{
			for(i=0;i<8;i++)
			{
				switch(i)
				{
					case 0:STEPD=0;STEPC=0;STEPB=0;STEPA=1;break;
					case 1:STEPD=0;STEPC=0;STEPB=1;STEPA=1;break;
					case 2:STEPD=0;STEPC=0;STEPB=1;STEPA=0;break;
					case 3:STEPD=0;STEPC=1;STEPB=1;STEPA=0;break;
					case 4:STEPD=0;STEPC=1;STEPB=0;STEPA=0;break;
					case 5:STEPD=1;STEPC=1;STEPB=0;STEPA=0;break;
					case 6:STEPD=1;STEPC=0;STEPB=0;STEPA=0;break;
					case 7:STEPD=1;STEPC=0;STEPB=0;STEPA=1;break;			
				}
				Delay_ms(1);
			}
			MOTOR_count--;
		}
	}
	else if(FX==0)//逆时针旋转
	{
		while(MOTOR_count>0)
		{
			for(i=7;i>=0;i--)
			{
				switch(i)
				{
					case 0:STEPD=0;STEPC=0;STEPB=0;STEPA=1;break;
					case 1:STEPD=0;STEPC=0;STEPB=1;STEPA=1;break;
					case 2:STEPD=0;STEPC=0;STEPB=1;STEPA=0;break;
					case 3:STEPD=0;STEPC=1;STEPB=1;STEPA=0;break;
					case 4:STEPD=0;STEPC=1;STEPB=0;STEPA=0;break;
					case 5:STEPD=1;STEPC=1;STEPB=0;STEPA=0;break;
					case 6:STEPD=1;STEPC=0;STEPB=0;STEPA=0;break;
					case 7:STEPD=1;STEPC=0;STEPB=0;STEPA=1;break;			
				}
				Delay_ms(1);
			}
			MOTOR_count--;			
		}			
	}
}

