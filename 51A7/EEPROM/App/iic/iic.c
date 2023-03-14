#include "iic.h"

void iic_start(void)//scl��sda�Ӹߵ���ʹ������
{
	IIC_SCL=1;
	IIC_SDA=1;
	delay_10us(1);
	IIC_SDA=0;
	delay_10us(1);
	IIC_SCL=0;
}

void iic_stop(void)//sda�ӵ͵���ֹͣʹ������
{
	IIC_SCL=1;
	IIC_SDA=0;
	delay_10us(1);
	IIC_SDA=1;
	delay_10us(1);
}

void iic_ack(void)//Ӧ���ź�
{
	IIC_SCL=0;
	IIC_SDA=0;
	delay_10us(1);
	IIC_SCL=1;
	delay_10us(1);
	IIC_SCL=0;
}

void iic_nack(void)//��Ӧ��
{
	IIC_SCL=0;
	IIC_SDA=1;
	delay_10us(1);
	IIC_SCL=1;
	delay_10us(1);
	IIC_SCL=0;
}

u8 iic_wait_ack(void)
{
	u8 time_temp=0;
	IIC_SCL=1;
	delay_10us(1);
	while(IIC_SDA)
	{
		++time_temp;
		if(time_temp>100)
		{
			iic_stop();
			return 1;
		}
	}
	IIC_SCL=0;
	return 0;
}


void iic_write_byte(u8 dat)
{
	u8 i=0;
	
	IIC_SCL=0;
	for(i=0;i<8;++i)
	{
		if((dat&0x80)>0)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		
		dat<<=1;
		IIC_SCL=1;//�ȶ�
		delay_10us(1);
		IIC_SCL=0;//��ʼ�´δ���
		delay_10us(1);
	}
}

u8 iic_read_byte(u8 ack)
{
	u8 i=0;
	u8 receive=0;
	
	for(i=0;i<8;++i)
	{
		IIC_SCL=0;
		delay_10us(1);
		IIC_SCL=1;
		delay_10us(1);
		
		receive<<=1;
		if(IIC_SDA)	++receive;
	}
	
	if(!ack) 
		iic_nack();
	else
		iic_ack();
	
	return receive;
}



