#include <STC15F2K60S2.H>
#include "delay.h"
#include "INTx.h"
#include "led.h"//led�ƺ���ͷ�ļ�


void main()
{
	//LED��ʼ��
	LED_Init();//LED�Ƴ�ʼ������������������Ϊ���������
	
	//��Ƭ����ʼ��
	INT0_Init();//�ⲿ�ж�0��ʼ������
//	INT1_Init();//�ⲿ�ж�1��ʼ������
//	INT2_Init();//�ⲿ�ж�3��ʼ������
//	INT3_Init();//�ⲿ�ж�3��ʼ������
//	INT4_Init();//�ⲿ�ж�4��ʼ������

	while(1)
	{
	}
}


