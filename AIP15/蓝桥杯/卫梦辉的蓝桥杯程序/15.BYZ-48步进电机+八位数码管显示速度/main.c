#include <STC15F2K60S2.H>
#include "delay.h"//延时函数头文件
#include "smg.h"//数码管函数头文件
#include "BYZ_48.h"//BYZ-48步进电机函数头文件


void main()
{
	P27=1;P26=0;P25=1;
	while(1)
	{	
		
		//实验1
//		BYZ_48_MOTOR1(1,0);//以速度值1逆时针（速度值越小旋转越快）控制步进电机旋转
		
		//实验2
		BYZ_48_MOTOR2(180,1);//顺时针旋转180度
		Delay_ms(500);
		BYZ_48_MOTOR2(180,0);//逆时针旋转180度
		Delay_ms(500);

	}
}
