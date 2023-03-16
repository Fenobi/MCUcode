#include "EEPROM.h"
/******************
**1.MCU�ȷ���һ����ʼ�ź�(START)��������
**2.���Ÿ������ֽڣ���������д������ַ(DEVICE ADDRESS)+д����(0xA0)
**3.�ȴ�Ӧ���ź�(ACK)
**4.�������ݵĴ洢��ַ��24C02һ����256���ֽڵĴ洢�ռ䣬��ַ��0x00~0xFF��������ݴ洢>���ĸ�λ�ã��˿�д�ľ����ĸ���ַ��
**5.����Ҫ�洢�����ݵ�һ�ֽڡ��ڶ��ֽڡ���ע����д���ݵĹ����У�E2PROMÿ���ֽڶ���>��Ӧһ����Ӧ��λ0�����ϸ�������дE2PROM���ݳɹ������û�л�Ӧ��λ��˵��д�벻�ɹ���
**6.���ͽ����źţ�STOP��ֹͣ����
*************************************************************************************************
**˵����AT24C02 EEPROMоƬһ����2Kbit�ռ䣬Ҳ���������Դ���256���ֽ����ݣ������ַΪ0x00~0xff;
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
