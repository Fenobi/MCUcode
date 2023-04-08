#include <Led.h>

/* 
		�������ƣ�Led��ʾ����
		����˵��������/Ϩ������һ��Led
		��ڲ�����addr-��Ҫ������Led flag-1����/0Ϩ��
		�������ݣ���
*/
void Led_Disp(unsigned char addr,flag)
{
	static unsigned char temp = 0x00;
	static unsigned char temp_old = 0xff;
	
	if(flag)
		temp |= 0x01 << addr;
	else
		temp &= ~(0x01 << addr);
	if(temp != temp_old)
	{
		P0 = ~temp;
		P2 = P2 & 0x1f | 0x80;
		P2 &= 0x1f;
		temp_old = temp;
	}
}

unsigned char temp = 0x00;
unsigned char temp_old = 0xff;

/* 
		�������ƣ��̵���ʹ�ܺ���
		����˵��������/�رռ̵���
		��ڲ�����flag-1����/0�ر�
		�������ݣ���
*/
void Relay(unsigned char flag)
{
	if(flag)
		temp |= 0x10;
	else
		temp &= ~0x10;	
	if(temp != temp_old)
	{
		P0 = temp;
		P2 = P2 & 0x1f | 0xa0;
		P2 &= 0x1f;
		temp_old = temp;
	}	
}

/* 
		�������ƣ�������ʹ�ܺ���
		����˵��������/�رռ̵���
		��ڲ�����flag-1����/0�ر�
		�������ݣ���
*/
void Beep(unsigned char flag)
{
	if(flag)
		temp |= 0x40;
	else
		temp &= ~0x40;	
	if(temp != temp_old)
	{
		P0 = temp;
		P2 = P2 & 0x1f | 0xa0;
		P2 &= 0x1f;
		temp_old = temp;
	}	
}