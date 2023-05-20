#include <STC15F2K60S2.H>
#include "pwm.h"
#include "DS1302.h"
#include "IIC_LCD12864.h"


sbit L=P0^0;
sbit M=P0^1;
sbit R=P0^2;

unsigned char speed1=20;
unsigned char speed2=20;



void main()
{
	
	
    pwminit();


    while (1)
    { 
       
    }
}

