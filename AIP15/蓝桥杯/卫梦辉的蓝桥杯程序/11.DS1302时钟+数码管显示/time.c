#include "time.h"//DS1302函数头文件


//以下为DS1302芯片的写和读 年、月、周、日、时、分、秒 的地址
unsigned char Write_addr[7] = { 0x8C/*年*/, 0x8A/*周*/, 0x88/*月*/, 0x86/*日*/, 0x84/*小时*/, 0x82/*分*/, 0x80/*秒*/}; 
unsigned char Read_addr[7] = { 0x8D/*年*/, 0x8B/*周*/, 0x89/*月*/, 0x87/*日*/, 0x85/*小时*/, 0x83/*分*/, 0x81/*秒*/}; 


//以下数组Time[7]是初始化设置和刷新日期时间的储存数组
//2022年 周一 12月  19日 上午12点07分30秒
//************************年****周****月****日****时****分****秒*/
unsigned char Time[7] = {0x22, 0x01, 0x12, 0x19, 0x01, 0x17, 0x50};




//向DS1302写入一个字节数据函数
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

//向DS1302读出一个字节数据函数
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

//向DS1302的指定地址写入一个字节数据函数
void ds1302_write_byte(unsigned char addr,unsigned char da)
{
	RST = 0; _nop_();
	SCLK = 0; _nop_();
	RST = 1; _nop_();
	
	ds1302_wrie(addr);
	ds1302_wrie(da);
	
	RST = 0; _nop_();
}

//向DS1302的指定地址读出一个字节数据函数（函数返回数据）
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

//初始化设置DS1302芯片时间函数（把数组Time[7]中的时间数据写入DS1302芯片）
void Init_DS1302_Time()
{
	unsigned char i;
	ds1302_write_byte(0x8E,0x00);		 //禁止写保护，就是关闭写保护功能
	for (i=0; i<7; i++)
	{
		ds1302_write_byte(Write_addr[i],Time[i]);
	}
	ds1302_write_byte(0x8E,0x80);		 //打开写保护功能
}


//读取DS1302芯片时间函数（把DS1302芯片的时间数据写入数组Time[7]中）
void Read_DS1302_Time()
{
	unsigned char i;
	
	for (i=0; i<7; i++)
	{
		Time[i] = ds1302_read_byte(Read_addr[i]);
	}
}

