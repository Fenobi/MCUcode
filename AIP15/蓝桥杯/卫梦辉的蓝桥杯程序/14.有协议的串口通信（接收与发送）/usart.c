#include "usart.h"//����ͨ�ź���ͷ�ļ�
 

//***************���ڳ�ʼ������******************************************
void Init_Uart()
{
	AUXR=0x00;  
	SCON=0x50;  //0101 0000�������ڷ�ʽ1���첽8λUART����������� ��REN=1
	TMOD=0x20;  //���ö�ʱ��T1�����ڷ�ʽ2��8λ�Զ���װ�������������ʷ�����
	TH1=0xfd;   //���ò�����Ϊ9600kbps����ֵ�ɲ���ҵ�
	TL1=0xfd;   //
	EA=1;       //���ж��ܿ���
	ES=1;       // �������ж�
	TR1=1;      //����T0
}

//***************����һ���ֽ�******************************************
void SendByte(unsigned char dat)
{
	SBUF=dat;
	while(TI==0);
	TI=0;
}


//�ض��򣬷����޷�ʹ��printf����
char putchar(char ch)
{	
	SendByte(ch);
  return ch;	
}

//***************����һ���ַ���******************************************
void SendString(unsigned char *str)
{
	while(*str !='\0')		
		SendByte(*str++);
}

//***************�����жϷ����ӳ���******************************************

unsigned char Rdata_flag;//�ַ���������ɱ�־���������Rdata_flag��1��
unsigned char Rdata;//���ջ������
unsigned char R_data[15];//���ջ�������
unsigned char Rdata_count;//�ƴα���

void ServiceUart() interrupt 4
{
	if(RI==1)
	{
		Rdata=SBUF;//����λ�����յ�������
		RI=0;//������������ɱ�־
		
		if(Rdata !='\n')//�жϽ��յ��������Ƿ��� \n
		{
			R_data[Rdata_count]=Rdata;//�����յ������ݴ��浽������
			Rdata_count++;//�ƴμ�1
		}
		else //���յ��������� \n ׼�����½���
		{
			R_data[Rdata_count]=Rdata;//�����յ������ݴ��浽������
			Rdata_count=0;//����ƴΣ�׼�������ͷ��ʼװ
			Rdata_flag=1;
		}
	}
}
