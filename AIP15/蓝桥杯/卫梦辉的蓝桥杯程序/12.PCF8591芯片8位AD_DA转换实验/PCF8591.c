#include "PCF8591.h"//PCF8591оƬA/D D/Aת������ͷ�ļ�
#include "iic.h"


u8 PCF8591_Read(u8 AINx)//����PCF8591оƬADCת��ֵ
{
	u8 temp;
	IIC_Start();
	IIC_SendByte(0x90);//д������ַ
	IIC_WaitAck();
	IIC_SendByte(AINx);//ѡ��ADת��ͨ��AINx
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