#include <STC15F2K60S2.h>

void Close_BUZZ();
void Init_IO();

void main()
{
	Close_BUZZ();
	Init_IO();
	while(1);
}

void Close_BUZZ()
{
	P2 = 0xA0;
	P0 = 0x00;
	P2 = 0x00;
}

void Init_IO()
{	
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xB8;		//�趨��ʱ��ֵ
	TH1 = 0xB8;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
	ES = 1;
	EA = 1; 
}

void IO() interrupt 4
{
	unsigned char temp;
	temp = SBUF;
	RI = 0;
	SBUF = temp;
	while(!TI);
	TI = 0;	
}






