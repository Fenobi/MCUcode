#include "e2prom.h"

void Write_EEPROM(u8 addr,u8 Data)
{
	unsigned char i=0, t=10;
	IIC_Start();
	IIC_SendByte(0xA0);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_WaitAck();
	IIC_SendByte(Data);
	IIC_WaitAck();
	IIC_Stop();
		
//	operate_delay(10);
	while(t--){
		for(i=0; i<112; i++);
	}
}

u8 Read_EEPROM(u8 addr)
{
	unsigned char Data;
	
	IIC_Start();
	IIC_SendByte(0xA0);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_WaitAck();	
	IIC_Start();
	IIC_SendByte(0xA1);
	IIC_WaitAck();	
	Data = IIC_RecByte();
	IIC_SendAck(0);
	IIC_Stop();
	
	return Data;
}
