#include <STC15F2K60S2.H>
#include "delay.h"//��ʱ����ͷ�ļ�
#include "smg.h"//����ܺ���ͷ�ļ�
#include "BYZ_48.h"//BYZ-48�����������ͷ�ļ�


void main()
{
	P27=1;P26=0;P25=1;
	while(1)
	{	
		
		//ʵ��1
//		BYZ_48_MOTOR1(1,0);//���ٶ�ֵ1��ʱ�루�ٶ�ֵԽС��תԽ�죩���Ʋ��������ת
		
		//ʵ��2
		BYZ_48_MOTOR2(180,1);//˳ʱ����ת180��
		Delay_ms(500);
		BYZ_48_MOTOR2(180,0);//��ʱ����ת180��
		Delay_ms(500);

	}
}
