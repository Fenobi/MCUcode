#include <STC15F2K60S2.H>
#include "delay.h"//��ʱ����ͷ�ļ�
#include "led.h"//led�ƺ���ͷ�ļ�


void main()
{
	LED_Init();//LED�Ƴ�ʼ�����������ÿ���LED��������Ϊ���������
	while(1)
	{
		
		//ʵ�����1��LED����˸��
		LED_One(1);//����L2��
		Delay_ms(500);
		LED_One(0);//Ϩ�����е�
		Delay_ms(500);
		
		
		//ʵ�����2 ��led��ˮ��
//		LED_LSD1(300);//��������ˮ
//		LED_LSD2(300);//���ҵ�����ˮ
		
		
		//ʵ�����3  ��һЩ������
//		LED_HY();//������ˮ����
		
		
	}
}
