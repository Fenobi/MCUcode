#include <STC15F2K60S2.H>
#include "delay.h"//��ʱ����ͷ�ļ�
#include "smg.h"//����ܺ���ͷ�ļ�
#include "CX20106A.h"//����������ͷ�ļ�

void main()
{
	u8 JL;
	CSB_Init();//��������ʱ����ʼ��
	while(1)
	{
		JL=Get_Distance();
		Display_2_WEI(1,JL);
	}
}
