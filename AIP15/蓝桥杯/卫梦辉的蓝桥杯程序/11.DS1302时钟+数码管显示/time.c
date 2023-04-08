#include "time.h"//DS1302����ͷ�ļ�


//����ΪDS1302оƬ��д�Ͷ� �ꡢ�¡��ܡ��ա�ʱ���֡��� �ĵ�ַ
unsigned char Write_addr[7] = { 0x8C/*��*/, 0x8A/*��*/, 0x88/*��*/, 0x86/*��*/, 0x84/*Сʱ*/, 0x82/*��*/, 0x80/*��*/}; 
unsigned char Read_addr[7] = { 0x8D/*��*/, 0x8B/*��*/, 0x89/*��*/, 0x87/*��*/, 0x85/*Сʱ*/, 0x83/*��*/, 0x81/*��*/}; 


//��������Time[7]�ǳ�ʼ�����ú�ˢ������ʱ��Ĵ�������
//2022�� ��һ 12��  19�� ����12��07��30��
//************************��****��****��****��****ʱ****��****��*/
unsigned char Time[7] = {0x22, 0x01, 0x12, 0x19, 0x01, 0x17, 0x50};




//��DS1302д��һ���ֽ����ݺ���
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

//��DS1302����һ���ֽ����ݺ���
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

//��DS1302��ָ����ַд��һ���ֽ����ݺ���
void ds1302_write_byte(unsigned char addr,unsigned char da)
{
	RST = 0; _nop_();
	SCLK = 0; _nop_();
	RST = 1; _nop_();
	
	ds1302_wrie(addr);
	ds1302_wrie(da);
	
	RST = 0; _nop_();
}

//��DS1302��ָ����ַ����һ���ֽ����ݺ����������������ݣ�
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

//��ʼ������DS1302оƬʱ�亯����������Time[7]�е�ʱ������д��DS1302оƬ��
void Init_DS1302_Time()
{
	unsigned char i;
	ds1302_write_byte(0x8E,0x00);		 //��ֹд���������ǹر�д��������
	for (i=0; i<7; i++)
	{
		ds1302_write_byte(Write_addr[i],Time[i]);
	}
	ds1302_write_byte(0x8E,0x80);		 //��д��������
}


//��ȡDS1302оƬʱ�亯������DS1302оƬ��ʱ������д������Time[7]�У�
void Read_DS1302_Time()
{
	unsigned char i;
	
	for (i=0; i<7; i++)
	{
		Time[i] = ds1302_read_byte(Read_addr[i]);
	}
}

