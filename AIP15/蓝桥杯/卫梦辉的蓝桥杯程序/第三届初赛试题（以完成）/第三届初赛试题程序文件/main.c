#include <STC15F2K60S2.H>
#include "delay.h"//��ʱ����ͷ�ļ�
#include "TIMERx.h"//��ʱ������ͷ�ļ�
#include "led.h"//led�ƺ���ͷ�ļ�
#include "smg.h"//����ܺ���ͷ�ļ�
#include "Buzz_Relay.h"//�̵��������������ͷ�ļ�
#include "PCF8591.h"//PCF8591оƬA/D D/Aת������ͷ�ļ�


sbit S6=P3^1;//����
sbit S7=P3^0;
sbit L1=P0^0;


void main()
{
	char mode=0;
	unsigned char ADC;
	
	RELAY(0);//�رռ̵����ͷ�����
	TIM0_Init();//��ʱ��0��ʼ������

	while(1)
	{
		if(S7==0)//��ʼ��ˮ
		{
			mode= 0;
			TR0 = 1;		//ʹ�ܶ�ʱ��0�ж�
			Water_L=0;
			RELAY(1);//�򿪼̵���
		}
		if(S6==0)//��ͣ��ˮ
		{
			mode= 1;
			TR0 = 0;		//ʹ�ܶ�ʱ��0�ж�
			RELAY(0);//�رռ̵���
		}
		
		switch(mode)
		{
			case 0://ģʽ����ʾ��
				Display_water(Water_L);//��ʾ������	
			if(Water_L>=99.99)
			{
				mode=1;
				RELAY(0);//�رռ̵���
			}
			break;
			case 1://ģʽһ��ʾ�۸�
				Display_water(Water_L*0.5);//���㲢��ʾ������	
			break;
		}
		
		ADC = PCF8591_Read(AIN1);//����PCF8591оƬADCת��ֵ
		if(ADC<64)
		{
			P25=0;P27=1;P26=0;//��Y4C������			ʹ���������Ч����ȫ��һ��,   P27=1;P26=0;P25=0;
			L1=0;
			P27=0;P26=0;P25=0;
		}
		else
		{
			P25=0;P27=1;P26=0;//��Y4C������			ʹ���������Ч����ȫ��һ��,   P27=1;P26=0;P25=0;
			L1=1;
			P27=0;P26=0;P25=0;
		}
		
	}
}
