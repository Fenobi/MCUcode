#include"time.h"
#include "intrins.h"
unsigned char Write_addr[7] = { 0x8C/*年*/, 0x8A/*周*/, 0x88/*月*/, 0x86/*日*/, 0x84/*小时*/, 0x82/*分*/, 0x80/*秒*/}; 
unsigned char Read_addr[7] = { 0x8D/*年*/, 0x8B/*周*/, 0x89/*月*/, 0x87/*日*/, 0x85/*小时*/, 0x83/*分*/, 0x81/*秒*/}; 

//2019年 周二 一月  21日 上午9点30分0秒
unsigned char Time[7] = { 0x19, 0x02, 0x01, 0x21, 0x09, 0x30, 0x00};
unsigned char burst_Time[8] = { 0x01/*分*/, 0x02/*时*/, 0x03/*日*/, 0x04/*月*/, 0x05/*周*/, 0x06/*年*/, 0x07/**/, 0x00/**/};

void ds1302_wrie(unsigned char da)
{
	unsigned char i;
	
	for (i=0; i<8; i++)
	{
		SCLK = 0;
		
		DA = da & 0x01;
		da >>= 1;
		
		SCLK = 1;
	}
}

unsigned char ds1302_read()
{
	unsigned char i,da;
	
	for (i=0; i<8; i++)
	{
		SCLK = 0;
		
		da >>= 1;
		if (DA)
		{
			da |= 0x80;
		}
		
		SCLK = 1;
	}
	return da;
}


void ds1302_write_byte(unsigned char addr,unsigned char da)
{
	RST = 0; _nop_();
	SCLK = 0; _nop_();
	RST = 1; _nop_();
	
	ds1302_wrie(addr);
	ds1302_wrie(da);
	
	RST = 0; _nop_();
}

unsigned char ds1302_read_byte(unsigned char addr)
{
	unsigned char temp;
	RST = 0; _nop_();
	SCLK = 0; _nop_();
	RST = 1; _nop_();

	ds1302_wrie(addr);
	temp = ds1302_read();
	
	RST = 0; _nop_();
	SCLK = 0; _nop_();
	SCLK = 1; _nop_();
	DA = 0; _nop_();
	DA = 1; _nop_();
	
	return temp;
}

void Init_DS1302_Time()
{
	unsigned char i;
	
	for (i=0; i<7; i++)
	{
		ds1302_write_byte(Write_addr[i],Time[i]);
	}
	
}


void burst_Init_time()
{
	unsigned char i;
	
	RST = 0; _nop_();
	SCLK = 0; _nop_();
	RST = 1; _nop_();

	ds1302_wrie(0xBE);
//	ds1302_wrie(0x80);
	for (i=0; i<8; i++)
	{
		ds1302_wrie(burst_Time[i]);
	}		
	
	RST = 0; _nop_();	
}

void Read_DS1302_Time()
{
	unsigned char i;
	
	for (i=0; i<7; i++)
	{
		Time[i] = ds1302_read_byte(Read_addr[i]);
	}
}