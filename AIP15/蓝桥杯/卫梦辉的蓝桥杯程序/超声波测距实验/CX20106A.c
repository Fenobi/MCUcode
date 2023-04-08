#include "CX20106A.h"

//������ģ���ʼ������
void US_init(void)
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//c���ö�ʱ��ģʽ
	TL0 = 0x00;		
	TH0 = 0x00;		
	TF0 = 0;		
}

//�����ʱ����
void Delay10us()		//@12.000MHz
{
	unsigned char i;
	_nop_();
	_nop_();
	i = 27;
	while (--i);
}

//������ģ���þ��뺯�����������ؾ���ֵ ��λ��cm��
u16 Get_distance(void)    //12M
{
	u8 i = 8;
	u16 distance;
	while(i--)
	{
		P10 = 1;
		Delay10us();      //��ʱʱ���д�̽��
		P10 = 0;
		Delay10us();
	}
	
	TL0 = 0;		
	TH0 = 0;
	TR0 = 1;
	while(P11 && (TF0 == 0));
	TR0 = 0;
	
	if(TF0)
	{
		TF0 = 0; distance = 99;
	}
	else
	{
		distance = ((TH0<<8)|(TL0))*0.0014167;    //�õ�<100cm�Ĳ�������
	}
    return distance;           
}

//��������������������������������
//��Ȩ����������ΪCSDN������Dream_��ʮ����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
//ԭ�����ӣ�https://blog.csdn.net/weixin_43487914/article/details/107498385