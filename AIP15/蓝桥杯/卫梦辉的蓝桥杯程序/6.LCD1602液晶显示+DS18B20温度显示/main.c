#include <STC15F2K60S2.H>
#include "delay.h"//��ʱ����ͷ�ļ�
#include "lcd1602.h"
#include "DS18B20.h"

void main()
{
	float Temp;	
	
	LcdInit(); //LCD1602��ʼ��
	
	while(1)
	{
		Temp=DS18B20_Tem();//DS18B20�����¶�ֵ����
		DisplayListChar(0, 0, "Temp:");
		Display_XS(5, 0,Temp,2);//��ʾָ��С����
		Delay_ms(300);//DS18B20�¶�ת����Ҫ��ʱһ��ʱ��
	}
}
