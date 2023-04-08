#ifndef __SMG_H__
#define __SMG_H__
#include <STC15F2K60S2.H>

sbit HC138_A=P2^5; //74hc138��Ƭ����������
sbit HC138_B=P2^6;
sbit HC138_C=P2^7;

#define SMG_GPIO  P0 //����ܵ�Ƭ����������

#define u8 unsigned char
#define u16 unsigned int

void HC138_Y(u8 Yx);//74hc138оƬ��������
void SMG_Display_Digital(u8 num,u8 point);//�������ʾ���ֺ���(��ѡ)
void SMG_Display_Wei(u8 wei);//ѡ��ڼ�λ�������ʾ����(λѡ)

void Display_1_WEI(u8 wei,u8 num,u8 point);//�����ָ��һλ��ʾһλ���ֺ���
void Display_2_WEI(u8 wei,u8 num);//�����ָ���ӵڼ�λ��ʾ��λ��������
void Display_4_WEI(u8 wei,u16 num);//�����ָ���ӵڼ�λ��ʾ��λ���ֺ���
void Display_1_2Wei_XS(u8 wei,float num);//��ʾС��10����λС������
void Display_2_2Wei_XS(u8 wei,float num);//��ʾС��100����λС������

#endif


//��������ܶ���
//0	--	0xc0
//1	--	0xf9
//2	--	0xa4
//3	--	0xb0
//4	--	0x99
//5	--	0x92
//6	--	0x82
//7	--	0xf8
//8	--	0x80
//9	--	0x90