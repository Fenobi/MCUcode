#include <STC15F2K60S2.H>
#include "delay.h"//��ʱ����ͷ�ļ�
#include "Buzz_Relay.h"//�̵��������������ͷ�ļ�


void main()
{
	
	while(1)
	{
		
		BUZZ(1);//��������
		Delay_ms(500);
		BUZZ(0);//�������ر�
		Delay_ms(500);
		
		RELAY(1);//�̵�����
		Delay_ms(500);
		RELAY(0);//�̵����ر�
		Delay_ms(500);
		
	}
}
