#include <STC15F2K60S2.h>
#include "smg.h"//����ܺ���ͷ�ļ�
#include "PCF8591.h"//PCF8591оƬA/D D/Aת������ͷ�ļ�


void main()
{
	int Digital;
	while(1)
	{
		
		//�ɵ�����
		Digital=PCF8591_Read(AIN3);
		Display_4_WEI(1,Digital);//�������ʾADת��ֵ���������4λ��ʾ��
		
		
//*******���´����һ������Ϊ�������������4λ��ʾ��������г�ͻ����ʾ����
		
		//1.�������� 
		Digital=PCF8591_Read(AIN1);
		Display_4_WEI(5,Digital);//�������ʾADת��ֵ���������4λ��ʾ��
		
		//2.����Ŵ���
//		Digital=PCF8591_Read(AIN2);
//		Display_4_WEI(5,Digital);//�������ʾADת��ֵ���������4λ��ʾ��
		
		//3.����(A/D)���ͨ��AIN0
//		Digital=PCF8591_Read(AIN0);
//		Display_4_WEI(5,Digital);//�������ʾADת��ֵ���������4λ��ʾ��
	}
}
