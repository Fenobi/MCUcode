#include "lcd1602.h"
#include <stdio.h>

/*******************************************************************************
* �� �� ��         : Lcd1602_Delay1ms
* ��������		   : ��ʱ��������ʱ1ms
* ��    ��         : c
* ��    ��         : ��
* ˵    ��         : �ú�������12MHZ�����£�12��Ƶ��Ƭ������ʱ��
*******************************************************************************/
void Lcd1602_Delay1ms(uint c)   //��� 0us
{
  uchar a,b;
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	}   	
}

/*******************************************************************************
* �� �� ��         : LcdWriteCom
* ��������		   : ��LCDд��һ���ֽڵ�����
* ��    ��         : com
* ��    ��         : ��
*******************************************************************************/
void LcdWriteCom(uchar com)	  //д������
{
	LCD1602_E = 0;     //ʹ��
	LCD1602_RS = 0;	   //ѡ��������
	LCD1602_RW = 0;	   //ѡ��д��
	
	LCD1602_DATAPINS = com;     //��������
	Lcd1602_Delay1ms(1);		//�ȴ������ȶ�

	LCD1602_E = 1;	          //д��ʱ��
	Lcd1602_Delay1ms(5);	  //����ʱ��
	LCD1602_E = 0;
}
/*******************************************************************************
* �� �� ��         : LcdWriteData
* ��������		   : ��LCDд��һ���ֽڵ�����
* ��    ��         : dat
* ��    ��         : ��
*******************************************************************************/		      
void LcdWriteData(uchar dat)			//д������
{
	LCD1602_E = 0;	//ʹ������
	LCD1602_RS = 1;	//ѡ����������
	LCD1602_RW = 0;	//ѡ��д��

	LCD1602_DATAPINS = dat; //д������
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;   //д��ʱ��
	Lcd1602_Delay1ms(5);   //����ʱ��
	LCD1602_E = 0;
}

/*******************************************************************************
* �� �� ��       : LcdInit()
* ��������		 : ��ʼ��LCD��
* ��    ��       : ��
* ��    ��       : ��
*******************************************************************************/		   
void LcdInit()						  //LCD��ʼ���ӳ���
{
 	LcdWriteCom(0x38);  //����ʾ
	LcdWriteCom(0x0c);  //����ʾ����ʾ���
	LcdWriteCom(0x06);  //дһ��ָ���1
	LcdWriteCom(0x01);  //����
	LcdWriteCom(0x80);  //��������ָ�����
}
/**************************************
����������LCD1602��ָ��λ����ʾһ���ַ�
��ڲ�����uint8 X, uint8 Y, uint8 DData
����ֵ����
***************************************/
void DisplayOneChar(uchar X, uchar Y, uchar DData)
{
	Y &= 0x1;
	X &= 0xF; //����X���ܴ���15��Y���ܴ���1
	if (Y) X |= 0x40; //��Ҫ��ʾ�ڶ���ʱ��ַ��+0x40;
	X |= 0x80; //���ָ����
	LcdWriteCom(X); //��������
	LcdWriteData(DData); //������
}

/**************************************
����������LCD1602��ָ��λ����ʾһ���ַ�
��ڲ�����uint8 X, uint8 Y, uint8 DData  X�����X+1�У�Y�����Y+1��
����ֵ����
***************************************/
void DisplayListChar(uchar X, uchar Y, uchar *DData)
{
	uchar ListLength;

  ListLength = 0;
	Y &= 0x1;
	X &= 0xF; //����X���ܴ���15��Y���ܴ���1
	while (DData[ListLength]>0x19) //�������ִ�β���˳�
		{
			if (X <= 0xF)        //X����ӦС��0xF
				{
					DisplayOneChar(X, Y, DData[ListLength]); //��ʾ�����ַ�
					ListLength++;
					X++;
				}
		}
}


uchar txt[20];
void Display_XS(uchar X, uchar Y,float XS,uchar XS_wei)//��ʾָ��С����
{
	switch(XS_wei)
	{
		case 0: sprintf(txt,"%0.0f",XS); break;
		case 1: sprintf(txt,"%0.1f",XS); break;
		case 2: sprintf(txt,"%0.2f",XS); break;
		case 3: sprintf(txt,"%0.3f",XS); break;
	}
	DisplayListChar(X, Y,txt);//��ʾС��������ֵ****4	
}

uint lcd_1602=9845;
float XS=23.48;
uchar code Disp1[]={"0123456789"};

void LCD1602_test(void)//LCD1602���Գ���
{
	LcdInit(); //LCD1602��ʼ��
	
	while(1)
	{
		DisplayListChar(0, 0, "WMH");     //�ӵ�һ�е�0�п�ʼ��ʾ����****1
		DisplayListChar(6, 0, Disp1);  //��ʾ�ַ���������****2
		
		lcd_1602=41;	
		sprintf(txt,"num:%d",lcd_1602);
		DisplayListChar(0,1,txt);//��ʾ����������ֵ****3
		
		sprintf(txt,"xs:%0.2f",XS);
		DisplayListChar(8,1,txt);//��ʾС��������ֵ****4
	}
}



////		LcdWriteCom(0x01);//����



