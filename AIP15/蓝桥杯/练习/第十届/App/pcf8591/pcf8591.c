#include "pcf8591.h"
#include "iic.h"

u8 AD_read(u8 addr)
{
	u8 temp;
	
	IIC_Start();
	IIC_SendByte(0x90);//读
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_WaitAck();
	
	IIC_Start();
	IIC_SendByte(0x91);//写
	IIC_WaitAck();
	temp = IIC_RecByte();
	IIC_SendAck(1);
	IIC_Stop();
	
	return temp;
}

void AD_write(u8 dat)
{
	IIC_Start();
	IIC_SendByte(0x90);//读
	IIC_WaitAck();
	IIC_SendByte(0x41);//使能
	IIC_WaitAck();
	
	IIC_SendByte(dat);
	IIC_WaitAck();

	IIC_Stop();
}