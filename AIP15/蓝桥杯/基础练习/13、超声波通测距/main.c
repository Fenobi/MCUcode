#include <reg52.h>
#include <intrins.h>
#include "absacc.h"
#define somenop {_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_(); _nop_();}


sbit TX = P1^0;
sbit RX = P1^1;

code unsigned char tab[] = { 0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xFF};
unsigned char dspbuf[8] = {10,10,10,10,10,10,10,10};  //��ʾ������
unsigned char dspcom = 0;

bit S_Flag;
unsigned char mytimer = 0;
unsigned int t;

unsigned wei = 0x80;

void Display()
{
	unsigned char i;
	for (i=0; i<8; i++)  
	{
		P2 = 0x00;              //ѡλ
		P0 = wei>>i;
		P2 = 0xC0;
		_nop_();_nop_();
		P2 = 0x00;

		P0 = tab[dspbuf[i]];
 		P2 = 0xE0;
		_nop_();_nop_();
		_nop_();_nop_();
		P2 = 0x00;
	}
}

void SendWave();
void display(void);

void main()
{
	unsigned int distance;

	TMOD |= 0x11;  //���ö�ʱ������ģʽ
	TH0 = (65536-2000)/256;
	TL0 = (65536-2000)%256;  
	TH1 = 0;
	TL1 = 0;  
  
	EA = 1;
	ET0 = 1;  //�򿪶�ʱ��0�ж�
	TR0 = 1;  //������ʱ��   
	
	while(1)
	{
		if (S_Flag)
		{
			S_Flag = 0;
			SendWave();
			TR1 = 1;
//			while((RX == 1) && (TF1 == 1));
			while((RX == 1) && (TF1 == 0));
			TR1 = 0;
		
			if (TF1 == 1)
			{
				TF1 = 0;
				distance = 9999;
			}
			else
			{
				t = TH1;
				t <<= 8;
				t |= TL1;
				distance = (unsigned int)(t*0.017);
			}
			TH1 = 0;
			TL1 = 0;
		}
	
		dspbuf[2] = distance/100;
		dspbuf[1] = distance%100/10;
		dspbuf[0] = distance%10; 
	}

//	while(1)
//	{
//        /** 200�������һ������ */
//		if(S_Flag)
//		{
//			S_Flag = 0;
//			SendWave();  //���ͷ����ź�
//			TR1 = 1;  //������ʱ
//			while((RX == 1) && (TF1 == 0));  //�ȴ��յ�����
//			TR1 = 0;  //�رռ�ʱ

//			//�������
//			if(TF1 == 1)
//			{
//				TF1 = 0;
//				distance = 9999;  //�޷���
//			}
//			else
//			{
//				/**  ����ʱ��  */
//				t = TH1;
//				t <<= 8;
//				t |= TL1;
//				distance = (unsigned int)(t*0.017);  //�������			
//			}
//        }
//		/** ���ݴ���                      */
//                           
//	}
}
void SendWave()
{
	unsigned char i=8;
	do
	{
		TX = 1;
		somenop;somenop;somenop;somenop;somenop;somenop;
		somenop;somenop;somenop;somenop;		
		TX = 0;
		somenop;somenop;somenop;somenop;somenop;somenop;
		somenop;somenop;somenop;somenop;		
	}
	while(i--);
}

//void display(void)
//{
// 	XBYTE[0xE000] = 0xff;  //ȥ����Ӱ

// 	XBYTE[0xC000] = (1<<dspcom);
// 	XBYTE[0xE000] = tab[dspbuf[dspcom]]; 
//	
//	if(++dspcom == 8){
// 		dspcom = 0;
//	}	
//}
void Timer() interrupt 1
{	
  TH0 = (65536-2000)/256;
  TL0 = (65536-2000)%256;  
	
	Display();
	if(++mytimer == 200)
	{
		S_Flag = 1;
		mytimer = 0;
	}
}