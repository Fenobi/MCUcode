#include"time.h"
#include "intrins.h"
unsigned char Write_addr[7] = { 0x8C/*��*/, 0x8A/*��*/, 0x88/*��*/, 0x86/*��*/, 0x84/*Сʱ*/, 0x82/*��*/, 0x80/*��*/}; 
unsigned char Read_addr[7] = { 0x8D/*��*/, 0x8B/*��*/, 0x89/*��*/, 0x87/*��*/, 0x85/*Сʱ*/, 0x83/*��*/, 0x81/*��*/}; 

//2019�� �ܶ� һ��  21�� ����9��30��0��
unsigned char Time[7] = { 0x19, 0x02, 0x01, 0x21, 0x09, 0x30, 0x00};
unsigned char burst_Time[8] = { 0x01/*��*/, 0x02/*ʱ*/, 0x03/*��*/, 0x04/*��*/, 0x05/*��*/, 0x06/*��*/, 0x07/**/, 0x00/**/};

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