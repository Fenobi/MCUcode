#include <STC15F2K60S2.h>
#include <stdio.h>//����printf();����ͷ�ļ�
#include <string.h>//����strcmp(,);����ͷ�ļ�
#include "delay.h"//��ʱ����ͷ�ļ�
#include "usart.h"//����ͨ�ź���ͷ�ļ�


//strcmp(str1,str2);//�Ƚ������ַ����Ƿ���ͬ����ͬ�򷵻�0


//���ڽ���Э��˵�����ѽ��յ��ַ�����涨������1������2�ַ������Ƚϣ������ͬ����ж�Ӧ����

unsigned char order1[8]="ST\r\n";		//����1����ѯ����ָ��:��ST\r\n"
unsigned char order2[8]="PARA\r\n";	//����2����ѯ����ָ��:"PARA\r\n"
char i,Rdata1=1,Rdata2=1;

void main()
{
	Init_Uart();//���ڳ�ʼ��	
	printf("--WMH--");
	while(1)
	{
		
		if(Rdata_flag==1)//�ж��ַ����Ƿ�������
		{
			Rdata_flag=0;//����ַ������ձ�־
			
			Rdata1=strcmp(order1,R_data);  //����1�Ƚϵķ���ֵ 
			Rdata2=strcmp(order2,R_data);  //����1�Ƚϵķ���ֵ 
			
			if(Rdata1==0)//�ж��Ƿ��������1
			{
				printf("ST ST ST\r\n");
			}
			else if(Rdata2==0)//�ж��Ƿ��������2
			{
				printf("PARA PARA PARA\r\n");
			}
			else//�����������
			{
				printf("ERROR...\r\n");
			}
			
			for(i=0;i<8;i++)//��ս������飬Ϊ�´ν���������׼��
			{
				R_data[i]='\0';
			}		
		}

	}
}
