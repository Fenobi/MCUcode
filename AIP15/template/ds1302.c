#include "ds1302.h"

sbit SCK=P1^7;		
sbit SDA=P2^3;		
sbit RST = P1^3;  										

u8 gWRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
u8 gREAD_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};

u8 gDS1302_TIME[7] = {0x20, 0x00, 0x22, 0x16, 0x04, 0x03, 0x23};

void Write_Ds1302(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK=0;
		SDA=temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

void Write_Ds1302_Byte( unsigned char address,unsigned char dat )     
{
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1; 	_nop_();  
 	Write_Ds1302(address);	
 	Write_Ds1302(dat);		
 	RST=0; 
}

unsigned char Read_Ds1302_Byte ( unsigned char address )
{
 	unsigned char i,temp=0x00;
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1;	_nop_();
 	Write_Ds1302(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
	SCK=1;	_nop_();
	SDA=0;	_nop_();
	SDA=1;	_nop_();
	return (temp);			
}

void ds1302_init(void)
{
    u8 i = 0;

    Write_Ds1302_Byte(0x8e, 0x00); // 开启写保护
    for (i = 0; i < 7; ++i)
    {
        Write_Ds1302_Byte(gWRITE_RTC_ADDR[i], gDS1302_TIME[i]);
    }
    Write_Ds1302_Byte(0x8e, 0x80); // 关闭写保护
}

void ds1302_read_time(void)
{
    u8 i = 0;

    for (i = 0; i < 7; ++i)
    {
        gDS1302_TIME[i] = Read_Ds1302_Byte(gREAD_RTC_ADDR[i]);
    }
}