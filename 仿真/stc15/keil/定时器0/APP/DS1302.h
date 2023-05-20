#ifndef _DS1302_H_
#define _DS1302_H_

#include "public.h"
	
//---����ds1302ʹ�õ�IO��---//
sbit DSIO=P1^5;
sbit SCLK=P1^6;
sbit RST =P1^7;

extern uchar *week_str[7];                    //�ܵ�Ӣ����д
extern uchar TIME[7];

void Ds1302Init();                            //DS1302��ʼ����
void Ds1302ReadTime();                        //��ȡʱ����Ϣ��
uchar DS1302_sec();                           //����
uchar DS1302_min();                           //����
uchar DS1302_hour();													//��ʱ
uchar DS1302_date();													//����
uchar DS1302_month();                         //����
uchar DS1302_week();                          //����
uint DS1302_year();                           //����

/*================================================================*/
void Ds1302Write(uchar addr, uchar dat);      //��DS1302д�������ַ+���ݣ�
uchar Ds1302Read(uchar addr);                 //��ȡһ����ַ������

#endif




