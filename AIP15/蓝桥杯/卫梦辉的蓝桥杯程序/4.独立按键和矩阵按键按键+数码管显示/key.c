#include "key.h"//��������ͷ�ļ�
#include "delay.h"//��ʱ����ͷ�ļ�

//�򵥵Ķ�����������(���ض�Ӧ��ֵ)
char DL_key1(void)
{
	if(S4==0)//����S7
	{
		Delay_ms(5);//��ʱ����
		if(S4==0)
			return 1;//����ֵ1
	}	
	else if(S5==0)//����S6
	{
		Delay_ms(5);//��ʱ����
		if(S5==0)
			return 2;//����ֵ2
	}
	
	else if(S6==0)//����S5
	{
		Delay_ms(5);//��ʱ����
		if(S6==0)
			return 3;//����ֵ3
	}
	else	if(S7==0)//����S4
	{
		Delay_ms(5);//��ʱ����
		if(S7==0)
			return 4;//����ֵ4
	}
	return 0;//��û�а�������ʱ����ֵΪ0
}

//���ӵĶ�����������
void DL_key2()
{
	
}


//���󰴼���������(���ض�Ӧ��ֵ)
char JZ_key(void)
{
	char key_value = 0;
	
	P34 = 1;P35 = 1;P42 = 1;P44 = 1;//�����󰴼�����GPIO����,�Ա��ȡ���ŵ�ƽ
	P30 = 0;P31 = 0;P32 = 0;P33 = 0;//�����󰴼�����GPIO����,�Ա㱻��ȡ�͵�ƽ
	
	//��ɨ��
	if ((P34 == 0) || (P35 == 0) || (P42 == 0) || (P44 == 0))
	{
		Delay_ms(5);//��ʱ����
		if ((P34 == 0) || (P35 == 0) || (P42 == 0) || (P44 == 0))
		{
			if(P34 == 0){key_value=4;}
			else	if(P35 == 0){key_value=3;}
			else	if(P42 == 0){key_value=2;}
			else	if(P44 == 0){key_value=1;}			
		}
	}
	
	P34 = 0;P35 = 0;P42 = 0;P44 = 0;//�����󰴼�����GPIO����,�Ա㱻��ȡ�͵�ƽ
	P30 = 1;P31 = 1;P32 = 1;P33 = 1;//�����󰴼�����GPIO����,�Ա��ȡ���ŵ�ƽ
	
	//��ɨ��
	if ((P30 == 0) || (P31 == 0) || (P32 == 0) || (P33 == 0))
	{
		Delay_ms(5);//��ʱ����
		if ((P30 == 0) || (P31 == 0) || (P32 == 0) || (P33 == 0))
		{
			if(P30 == 0){key_value+=0;}
			else	if(P31 == 0){key_value+=4;}
			else	if(P32 == 0){key_value+=8;}
			else	if(P33 == 0){key_value+=12;}			
		}
	}
	return key_value;
}
