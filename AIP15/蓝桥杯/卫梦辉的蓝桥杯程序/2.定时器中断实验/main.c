#include <STC15F2K60S2.H>
#include "delay.h"//��ʱ����ͷ�ļ�
#include "TIMERx.h"//��ʱ������ͷ�ļ�
#include "led.h"//led�ƺ���ͷ�ļ�

void main()
{
	
	LED_Init();//LED�Ƴ�ʼ������������������Ϊ���������
	
	TIM0_Init();//��ʱ��0��ʼ������
  TIM1_Init();//��ʱ��1��ʼ������
	TIM2_Init();//��ʱ��2��ʼ������
	while(1)
	{
		
	}
	
}
