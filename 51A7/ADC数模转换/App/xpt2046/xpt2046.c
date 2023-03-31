#include "xpt2046.h"

void xpt2046_wirte_data(u8 dat)
{
	u8 i;

	CLK = 0;
	_nop_();
	for(i=0;i<8;i++)//循环8次，每次传输一位，共一个字节
	{
		DIN = dat >> 7;//先传高位再传低位
		dat <<= 1;//将低位移到高位
		CLK = 0;//CLK由低到高产生一个上升沿，从而写入数据
		_nop_();	
		CLK = 1;
		_nop_();
	}
}

u16	xpt2046_read_data(void)
{
	u8 i;
	u16 dat=0;

	CLK = 0;
	_nop_();
	for(i=0;i<12;i++)//循环12次，每次读取一位，大于一个字节数，所以返回值类型是u16
	{
		dat <<= 1;
		CLK = 1;
		_nop_();
		CLK = 0; //CLK由高到低产生一个下降沿，从而读取数据
		_nop_();
		dat |= DOUT;//先读取高位，再读取低位。	
	}
	return dat;	
}

u16 xpt2046_read_adc_value(u8 cmd)
{
	u8 i;
	u16 adc_value=0;

	CLK = 0;//先拉低时钟
	CS  = 0;//使能XPT2046
	xpt2046_wirte_data(cmd);//发送命令字
	for(i=6; i>0; i--);//延时等待转换结果
	CLK = 1;
	_nop_();
	CLK = 0;//发送一个时钟，清除BUSY
	_nop_();
	adc_value=xpt2046_read_data();
	CS = 1;//关闭XPT2046
	return adc_value;
}