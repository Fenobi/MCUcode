#include <STC15F2K60S2.H>
#include "delay.h"//��ʱ����ͷ�ļ�
#include "smg.h"//����ܺ���ͷ�ļ�
#include "key.h"//��������ͷ�ļ�

void main()
{
	u8 key_value;
	while(1)
	{
		//ʵ��1 ������������ע������ð�ò��ڶ���������
//		key_value=DL_key1();//��ȡ����ֵ
//		Display_2_WEI(1,key_value);//�������ʾ��ֵ
		
//////		//ʵ��2 ������������ע������ð�ò��ڶ���������xxxxxxû��д��
////////		key_value=DL_key2();//��ȡ����ֵ
////////		Display_2_WEI(1,key_value);//�������ʾ��ֵ
//////		
		
		//ʵ��3 �����󰴼���ע������ð�ò��ھ��󰴼���
		key_value=JZ_key();//��ȡ����ֵ
		Display_2_WEI(1,key_value);//�������ʾ��ֵ

	}
}
