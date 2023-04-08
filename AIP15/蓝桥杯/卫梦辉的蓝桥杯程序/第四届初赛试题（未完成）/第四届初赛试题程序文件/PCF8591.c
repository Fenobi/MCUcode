#include "PCF8591.h"//PCF8591芯片A/D D/A转换函数头文件
#include "iic.h"


u8 PCF8591_Read(u8 AINx)//返回PCF8591芯片ADC转换值
{
	u8 temp;
	IIC_Start();
	IIC_SendByte(0x90);//写操作地址
	IIC_WaitAck();
	IIC_SendByte(AINx);//选择AD转换通道AINx
	IIC_WaitAck();
	IIC_Stop();
	
	IIC_Start();
	IIC_SendByte(0x91);
	IIC_WaitAck();
	temp = IIC_RecByte();
	IIC_SendAck(1);
	IIC_Stop();
	return temp;
}