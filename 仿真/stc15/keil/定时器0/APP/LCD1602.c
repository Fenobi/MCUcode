#include "lcd1602.h"
#include <stdio.h>
#include <STC15F2K60S2.H>

sbit LCD1602_RS=P1^0;
sbit LCD1602_RW=P1^1;
sbit LCD1602_E=P1^2;

#define LCD1602_DATAPINS P0  //����

/*******************************************************************************
* �� �� ��         : Lcd1602_Delay1ms
* ��������		   : ��ʱ��������ʱ1ms
* ��    ��         : c
* ��    ��         : ��
* ˵    ��         : �ú�������12MHZ�����£�12��Ƶ��Ƭ������ʱ��
*******************************************************************************/

void Lcd1602_Delay1ms(uint ms)   //��� 0us
{
	unsigned char i, j;
	while(ms--)
	{
		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} while (--i);
	}
}
void Lcd1602_Delay50us()		//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	_nop_();
	i = 147;
	while (--i);
}
/*******************************************************************************
* �� �� ��         : LcdWriteCom
* ��������		   : ��LCDд��һ���ֽڵ�����
* ��    ��         : com
* ��    ��         : ��
*******************************************************************************/
//#ifndef 	LCD1602_4PINS	 //��û�ж������LCD1602_4PINSʱ
//void LcdWriteCom(uchar com)	  //д������
//{
//	LCD1602_E = 0;     //ʹ��
//	LCD1602_RS = 0;	   //ѡ��������
//	LCD1602_RW = 0;	   //ѡ��д��
//	
//	LCD1602_DATAPINS = com;     //��������
//	Lcd1602_Delay1ms(1);		//�ȴ������ȶ�

//	LCD1602_E = 1;	          //д��ʱ��
//	Lcd1602_Delay1ms(5);	  //����ʱ��
//	LCD1602_E = 0;
//}
//#else 
void LcdWriteCom(uchar com)	  //д������
{
	LCD1602_E = 0;	 //ʹ������
	LCD1602_RS = 0;	 //ѡ��д������
	LCD1602_RW = 0;	 //ѡ��д��

	LCD1602_DATAPINS = com;	//����4λ�Ľ����ǽӵ�P0�ڵĸ���λ�����Դ��͸���λ���ø�
//	Lcd1602_Delay1ms(1);
	Lcd1602_Delay50us();


	LCD1602_E = 1;	 //д��ʱ��
//	Lcd1602_Delay1ms(5);
	Lcd1602_Delay50us();
	LCD1602_E = 0;

	LCD1602_DATAPINS = com << 4; //���͵���λ
//	Lcd1602_Delay1ms(1);
	Lcd1602_Delay50us();

	LCD1602_E = 1;	 //д��ʱ��
//	Lcd1602_Delay1ms(5);
	Lcd1602_Delay50us();
	LCD1602_E = 0;
}
//#endif
/*******************************************************************************
* �� �� ��         : LcdWriteData
* ��������		   : ��LCDд��һ���ֽڵ�����
* ��    ��         : dat
* ��    ��         : ��
*******************************************************************************/		   
//#ifndef 	LCD1602_4PINS		   
//void LcdWriteData(uchar dat)			//д������
//{
//	LCD1602_E = 0;	//ʹ������
//	LCD1602_RS = 1;	//ѡ����������
//	LCD1602_RW = 0;	//ѡ��д��

//	LCD1602_DATAPINS = dat; //д������
//	Lcd1602_Delay1ms(1);

//	LCD1602_E = 1;   //д��ʱ��
//	Lcd1602_Delay1ms(5);   //����ʱ��
//	LCD1602_E = 0;
//}
//#else
void LcdWriteData(uchar dat)			//д������
{
	LCD1602_E = 0;	  //ʹ������
	LCD1602_RS = 1;	  //ѡ��д������
	LCD1602_RW = 0;	  //ѡ��д��

	LCD1602_DATAPINS = dat;	//����4λ�Ľ����ǽӵ�P0�ڵĸ���λ�����Դ��͸���λ���ø�
//	Lcd1602_Delay1ms(1);
	Lcd1602_Delay50us();

	LCD1602_E = 1;	  //д��ʱ��
//	Lcd1602_Delay1ms(5);
	Lcd1602_Delay50us();
	LCD1602_E = 0;

	LCD1602_DATAPINS = dat << 4; //д�����λ
//	Lcd1602_Delay1ms(1);
	Lcd1602_Delay50us();

	LCD1602_E = 1;	  //д��ʱ��
//	Lcd1602_Delay1ms(5);
	Lcd1602_Delay50us();
	LCD1602_E = 0;
}
//#endif
/*******************************************************************************
* �� �� ��       : LcdInit()
* ��������		 : ��ʼ��LCD��
* ��    ��       : ��
* ��    ��       : ��
*******************************************************************************/		   
//#ifndef		LCD1602_4PINS
//void LcdInit()						  //LCD��ʼ���ӳ���
//{
// 	LcdWriteCom(0x38);  //����ʾ
//	LcdWriteCom(0x0c);  //����ʾ����ʾ���
//	LcdWriteCom(0x06);  //дһ��ָ���1
//	LcdWriteCom(0x01);  //����
//	LcdWriteCom(0x80);  //��������ָ�����
//}
//#else
void LcdInit()						  //LCD��ʼ���ӳ���
{
	LcdWriteCom(0x32);	 //��8λ����תΪ4λ����
	LcdWriteCom(0x28);	 //����λ���µĳ�ʼ��
	LcdWriteCom(0x0c);  //����ʾ����ʾ���
	LcdWriteCom(0x06);  //дһ��ָ���1
	LcdWriteCom(0x01);  //����
	LcdWriteCom(0x80);  //��������ָ�����
}
//#endif

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


/**********************************************************
ע�⣺lcd1602 ��ʾ����ʾ��Χһ�� 0~1��2��  0~15��16��
����	Display_Num(5, 0, -552);//��5�е�0�п�ʼ��ʾ-552
************************************************************/
void Display_Num(uchar X, uchar Y, int num)//���������� ��Χ-32768~32767
{
	uchar num_txt[20];
	sprintf(num_txt,"%4d",num);
	DisplayListChar(X, Y, num_txt);
}

/**********************************************************
ע�⣺lcd1602 ��ʾ����ʾ��Χһ�� 0~1��2��  0~15��16��
����	Display_NumPoint(0, 1, -24.2);//��0�е�1�п�ʼ��ʾ-24.2
************************************************************/
void Display_NumPoint(uchar X, uchar Y, float decimal)//��С������ ��Χ
{
	uchar decimal_txt[20];
	sprintf(decimal_txt,"%0.1f",decimal);//%0.xf  x�Ǽ�������Ҫ��ʾС�����λ�������������
	DisplayListChar(X, Y, decimal_txt);
}

void LCD1602_test(void)//LCD1602���Գ���
{
	uchar lcd_1602_txt[20];
	int lcd_1602=543;
	
	LcdInit(); //LCD1602��ʼ��
	while(1)
	{
		DisplayListChar(0, 0, " ABC");//�ӵ�0�е�0�п�ʼ��ʾ����
		Display_Num(7, 0, -552);//���������� ��Χ-32768~32767
		Display_NumPoint(0, 1, -25.8);//��С������
		
		sprintf(lcd_1602_txt,"WMH:%d",lcd_1602);
		DisplayListChar(7,1,lcd_1602_txt);//��ʾ�ַ���
		
		
		Lcd1602_Delay1ms(500);//500msˢ��һ����ʾ
	}
}




