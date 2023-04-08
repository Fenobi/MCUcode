#include "usart.h"//����ͨ�ź���ͷ�ļ�
 
unsigned char Rdat;

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
void ServiceUart() interrupt 4
{
	if(RI==1)
	{
		Rdat=SBUF;//����λ�����յ�������
		RI=0;
		
		SendByte(Rdat);//ʹ�ô��ڷ��ͺ������ͻ�ȥ

	}
}
