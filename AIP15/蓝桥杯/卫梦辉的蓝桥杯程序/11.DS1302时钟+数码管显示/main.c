#include <STC15F2K60S2.h>
#include "smg.h"//����ܺ���ͷ�ļ�
#include "time.h"//DS1302����ͷ�ļ�


void main()
{
//	Init_DS1302_Time();
//	burst_Init_time();
	while(1)
	{
		Read_DS1302_Time();//��ȡDS1302ʱ�䣬ˢ�µ�����Time[7]��
		Display_2_WEI(1,Time[4]/16*10+Time[4]%16);//�������ʾʱ
		Display_1_WEI(3,11,0);//�������ʾ��-��
		Display_2_WEI(4,Time[5]/16*10+Time[5]%16);//�������ʾ��
		Display_1_WEI(6,11,0);//�������ʾ��-��
		Display_2_WEI(7,Time[6]/16*10+Time[6]%16);//�������ʾ��
	}
}
