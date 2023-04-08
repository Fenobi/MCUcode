#ifndef __BYZ_48_H__
#define __BYZ_48_H__
#include <STC15F2K60S2.H>

#define u8 unsigned char 
#define u16 unsigned int
	
void BYZ_48_MOTOR1(u8 speed,bit FX);//控制步进电机旋转
void BYZ_48_MOTOR2(float Angle,bit FX);//控制步进电机以最快速度旋转特定角度

#endif