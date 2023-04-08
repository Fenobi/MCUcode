#include "led.h"//led�ƺ���ͷ�ļ�
#include "delay.h"//��ʱ����ͷ�ļ�


//LED�Ƴ�ʼ������������������Ϊ���������
void LED_Init(void)
{
	P27=1;P26=0;P25=0;//���ƻ����Y4C����ߵ�ƽ
	
	P0M1=0x00;P0M0=0x00;//����P0��GPIOģʽΪ׼˫��ڣ���ͳ51GPIOģʽ��
}

//����ָ��һ��LED�ƺ���
//���磺LED_One(3);  ֻ��L3����
//���磺LED_One(0);  L1~L8ȫϨ��
void LED_One(u8 Lx)
{
	switch(Lx)
	{
		case 0: P0=0xff;break;//LED��ȫϨ��
		case 1: P0=0xfe;break;
		case 2: P0=0xfd;break;
		case 3: P0=0xfb;break;
		case 4: P0=0xf7;break;
		case 5: P0=0xef;break;
		case 6: P0=0xdf;break;
		case 7: P0=0xbf;break;
		case 8: P0=0x7f;break;
	}
}

//led��ˮ�ƺ���
void LED_LSD1(u16 ms)//��������ˮ
{
	u8 i;
	for(i=1;i<9;i++)
	{
		LED_One(i);
	  Delay_ms(ms);
	}
}

void LED_LSD2(u16 ms)//���ҵ�����ˮ
{
	u8 i;
	for(i=8;i>0;i--)
	{
		LED_One(i);
	  Delay_ms(ms);
	}
}

//������ˮ����
void LED_HY(void)
{
	u16 ms;
	
	ms=50;//���ÿ����ٶ�
	P0=0x00;Delay_ms(ms);P0=0xff;Delay_ms(ms);//LED����
	P0=0x00;Delay_ms(ms);P0=0xff;Delay_ms(ms);
	P0=0x00;Delay_ms(ms);P0=0xff;Delay_ms(ms);
	P0=0x00;Delay_ms(ms);P0=0xff;Delay_ms(ms);
	P0=0x00;Delay_ms(ms);P0=0xff;Delay_ms(ms);
	
	ms=300;//������ˮʱ��
	LED_LSD1(ms);//LED������ˮ
	LED_LSD2(ms);
	
	
	
	//�����Ƴ���û��д�꣩
//	ms=100;
//	for(i;i<100;i++) //LED������
//	{
//		P0=0x00;
//		Delay_ms(ms);//��
//		P0=0xff;
//		Delay_ms(20-ms);//��
//		ms--;
//	}		
//	
//	for(i;i<100;i++) //LED������
//	{
//		P0=0x00;
//		Delay_ms(20-ms);//��
//		P0=0xff;
//		Delay_ms(ms);//��
//		ms--;
//	}	
	
	
	
	
	
	

}
