
#include "IIC_LCD12864.h"
#include <STC15F2K60S2.H>


void main()
{

	int val=1314;
	oled_init();//OLED��ʼ��
	
  while (1)
	{	
		OLED_Display_Num(0,0,-284);//��ʾС�����ֺ���
		OLED_Display_NumPint(0,1,-36.9);//��ʾС��С�����ֺ���
		oled_shownum(0,2,val,5,16);//��ʾ������ֺ���-----  x,y:����,num��ֵ,len��ʾλ��,size2�����壬Ĭ����16����
		oled_showchinese(0,4,0);//��ʾ����,x yΪ���꣬noΪ���	
		oled_showstring(0,6,"Hello W!",32);//��ʾ�ַ���
		
		
		LCD12864_delay_ms(100);
	}
}                                                                