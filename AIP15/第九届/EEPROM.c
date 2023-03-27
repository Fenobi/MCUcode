#include "EEPROM.h"
/******************
**1.MCU先发送一个开始信号(START)启动总线
**2.接着跟上首字节，发送器件写操作地址(DEVICE ADDRESS)+写数据(0xA0)
**3.等待应答信号(ACK)
**4.发送数据的存储地址。24C02一共有256个字节的存储空间，地址从0x00~0xFF，想把数据存储>在哪个位置，此刻写的就是哪个地址。
**5.发送要存储的数据第一字节、第二字节、…注意在写数据的过程中，E2PROM每个字节都会>回应一个“应答位0”，老告诉我们写E2PROM数据成功，如果没有回应答位，说明写入不成功。
**6.发送结束信号（STOP）停止总线
*************************************************************************************************
**说明：AT24C02 EEPROM芯片一共有2Kbit空间，也就是最大可以储存256个字节数据，储存地址为0x00~0xff;
*******************/
void Write_EEPROM(unsigned char addr,unsigned char Data)
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

unsigned char Read_EEPROM(unsigned char addr)
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
