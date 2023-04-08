#include "smg.h"//����ܺ���ͷ�ļ�
#include "delay.h"//��ʱ����ͷ�ļ�


//*********************************0    1    2    3    4    5    6    7    8    9    .    -
unsigned char Display_Digital[13]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x7f,0xbf,0xff};
unsigned char Display_WEI[9]={0,1,2,4,8,16,32,64,128};


//74hc138оƬ��������
//���磺HC138_Y(2);  ��74hc138оƬ��Y2��������͵�ƽ���򽫻����Y2C��Ӧ��74hc573оƬ����������档
void HC138_Y(u8 Yx)
{
	switch(Yx)
	{
		case 0: HC138_C=0;HC138_B=0;HC138_A=0;break;
		case 1: HC138_C=0;HC138_B=0;HC138_A=1;break;
		case 2: HC138_C=0;HC138_B=1;HC138_A=0;break;
		case 3: HC138_C=0;HC138_B=1;HC138_A=1;break;
		case 4: HC138_C=1;HC138_B=0;HC138_A=0;break;
		case 5: HC138_C=1;HC138_B=0;HC138_A=1;break;
		case 6: HC138_C=1;HC138_B=1;HC138_A=0;break;
		case 7: HC138_C=1;HC138_B=1;HC138_A=1;break;
	}
}

//�������ʾ���ֺ���(��ѡ)
//���磺 SMG_Display(2,0);  ���������ʾ����2  û��С����
//���磺 SMG_Display(2,1);  ���������ʾ����2. ��С����
void SMG_Display_Digital(u8 num,u8 point)
{
	switch(point)
	{
		case 0: SMG_GPIO=Display_Digital[num];break;
		case 1: SMG_GPIO=Display_Digital[num]&0x7f;break;
	}
}


//ѡ��ڼ�λ�������ʾ����(λѡ)
//���磺 WEI(2); ��˸�����ܴ����ҵ�2������ܿ�����ʾ��
void SMG_Display_Wei(u8 wei)
{
	SMG_GPIO=Display_WEI[wei];
}

/*****************************************
					��λ�������ʾ����˼·

********************�������ʾһλ
**	1.�򿪶�Ӧ74hc57�������Y6C������λѡ��ѡ��ڼ�λ�������ʾ���֣���
**	2.�򿪶�Ӧ74hc57�������Y7C�������Ӧ����(д��Ҫ��ʾ������)��
**	3.��ʱһ��������磺2ms��������Ҫѡ��һ�����ʵ���ʱʱ�䣨ʱ�������ʾ������̫С����ʾ̫����
**
**	Ҫ��ʾ��λ����ѭ��1~4������
*********************************************/

//�����ָ��һλ��ʾһλ���ֺ���
//���磺Display_1_WEI(2,3,0);  ��ʾ�ڶ�λ�������ʾ3 ������3����û����ʾС����
//���磺Display_1_WEI(2,3,1);  ��ʾ�ڶ�λ�������ʾ3. ������3��������ʾС����
void Display_1_WEI(u8 wei,u8 num,u8 point)
{
	HC138_Y(6);//1
	SMG_Display_Wei(wei);
	
	HC138_Y(7);//2
	SMG_Display_Digital(num,point);
	
	Delay_ms(2);//3
}

//�����ָ���ӵڼ�λ��ʾ��λ��������
void Display_2_WEI(u8 wei,u8 num)
{
	Display_1_WEI(wei, num%100/10,0);//��ʾʮλ
	Display_1_WEI(wei+1, num%10,0);//��ʾ��λ
}

//�����ָ���ӵڼ�λ��ʾ��λ��������
void Display_4_WEI(u8 wei,u16 num)
{
	Display_1_WEI(wei, num/1000,0);//��ʾǧλ
	Display_1_WEI(wei+1, num%1000/100,0);//��ʾ��λ
	Display_1_WEI(wei+2, num%100/10,0);//��ʾʮλ
	Display_1_WEI(wei+3, num%10,0);//��ʾ��λ
}

//��ʾС��10����λС������
void Display_1_2Wei_XS(u8 wei,float num)
{
	num=num*100;//��С������100��
	Display_1_WEI(wei, (int)num%1000/100,1);//��ʾ��λ
	Display_1_WEI(wei+1, (int)num%100/10,0);//��ʾʮλ
	Display_1_WEI(wei+2, (int)num%10,0);//��ʾ��λ
}

//��ʾС��100����λС������
void Display_2_2Wei_XS(u8 wei,float num)
{
	num=num*100;//��С������100��
	Display_1_WEI(wei, num/1000,0);//��ʾǧλ
	Display_1_WEI(wei+1, (int)num%1000/100,1);//��ʾ��λ
	Display_1_WEI(wei+2, (int)num%100/10,0);//��ʾʮλ
	Display_1_WEI(wei+3, (int)num%10,0);//��ʾ��λ
}

//�����������ʾ����
void Display_water(float num)
{
	//ǰ��λ��ʾ����
	Display_1_WEI(1,12,0);//����ʾ(����)
	Display_1_WEI(2,0,1);
	Display_1_WEI(3,5,0);
	Display_1_WEI(4,0,0);
	
	Display_2_2Wei_XS(5,num);
}

