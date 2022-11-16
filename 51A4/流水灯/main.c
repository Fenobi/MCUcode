#include <REGX51.H>

#include "intrins.h"

//sbit led1=P0;

typedef unsigned int u16;
typedef unsigned char u8;

#define led P0

void delay(void)   //?? 0us
{
	unsigned char a,b,c;
	for(c=19;c>0;c--)
		for(b=20;b>0;b--)
			for(a=130;a>0;a--);
}

void main()
{
	u8 i=0;
	led=0x01;

	while(1)
	{
		for(i=0;i<7;i++)
		{
			led=_crol_(led,1);
			delay();
		}
		for(i=0;i<7;i++)
		{
			led=_cror_(led,1);
			delay();
		}
	}
}


//#include <reg51.h> 
//#include<intrins.h>
//typedef unsigned int u16; 
//typedef unsigned char u8;
//sbit RCLK=P3^5;
//sbit SRCLK=P3^6;
//sbit SER=P3^4;
//sbit LED=P0^7;

//void Hc595SendByte(u8 dat1,u8 dat2)
//{
//        u8 i;
//        SRCLK = 1;
//        RCLK = 1;
//        for(i=0;i<8;i++)
//        {
//                SER = dat1 >> 7;
//                dat1 <<= 1;
//                SRCLK =0;       
//                _nop_();
//                _nop_();
//                SRCLK =1;       
//        }
//        for(i=0;i<8;i++)             
//        {
//                SER = dat2 >> 7;
//                dat2 <<= 1;
//                SRCLK = 0;                      
//                _nop_();
//                _nop_();
//                SRCLK = 1;      
//        }
// 
//        RCLK =0;
//        _nop_();
//        _nop_();
//        RCLK =1;
//}

//void main()
//{       
//   LED=0;
//        while(1)
//        {       
//            Hc595SendByte(0xfe,0x01);
//        }               
//}