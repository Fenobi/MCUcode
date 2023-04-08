#include "CX20106A.h"//����������ͷ�ļ�

//�мǣ�������벻ʹ�÷�Ƶ
sbit TX = P1^0;  //��������
sbit RX = P1^1;  //��������

//12us
void Delay12us(void)//@11.0592MHz
{
	unsigned char i;
	_nop_();
	_nop_();
	_nop_();
	i = 30;
	while (--i);
}

void send_wave(void)//���Ͱ˶����岨(40Khz)
{
	unsigned char i = 8;
	while(i --)
	{
		TX = 1;
		Delay12us();
		TX = 0;
		Delay12us();
	}
}

void CSB_Init(void)//��������ʱ����ʼ��
{
	AUXR |= 0x80;
  TMOD |= 0x10;  //���ö�ʱ������ģʽ 
  TH1 = 0;
  TL1 = 0;  
//  EA = 1;	
}

//������ģ���þ��뺯�����������ؾ���ֵ ��λ��cm��
u16 Get_Distance(void) //@11.0592MHz
{
	u16 distance,time;
  send_wave();  //���ͷ����ź�
  TR1 = 1;  //������ʱ
	while((RX == 1) && (TF1 == 0));  //�ȴ��յ����壬û�м������
	TR1 = 0;  //�رռ�ʱ

	//�������
	if(TF1 == 1)
	{
		TF1 = 0;
		distance = 100;  //�޷���
	}
	else
	{
		/**  ����ʱ��  */
		time=TH1*256+TL1;
		distance = (unsigned int)(time*0.017);  //�������ȡ��������λCM��				
	}
	TH1 = 0;
	TL1 = 0;
			
  return distance;           
}
