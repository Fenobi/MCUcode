#include "EEPROM.h"


void Write_EEPROM(unsigned char addr,unsigned char dat)
{
	unsigned char i=0, t=10;
	IIC_Start();
	IIC_SendByte(0xA0);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_WaitAck();
	IIC_SendByte(dat);
	IIC_WaitAck();
	IIC_Stop();
		
//	operate_delay(10);
	while(t--){
		for(i=0; i<112; i++);
	}
}

unsigned char Read_EEPROM(unsigned char addr)
{
	unsigned char da;
	
	IIC_Start();
	IIC_SendByte(0xA0);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_WaitAck();	
	IIC_Start();
	IIC_SendByte(0xA1);
	IIC_WaitAck();	
	da = IIC_RecByte();
	IIC_SendAck(0);
	IIC_Stop();
	
	return da;
}
