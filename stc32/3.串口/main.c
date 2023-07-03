#include <STC32G.H>
#include "stdio.h"
bit busy;
int wptr;
char rptr;
char buffer[64];

void Delay200ms()		//@35MHz
{
	unsigned long i;

	_nop_();
	_nop_();
	i = 1749998UL;
	while (i) i--;
}

void UART1_int (void) interrupt 4
{
	if(TI)// TI:����1��������ж������־����Ҫ������㡣
	{
		TI= 0;
		busy= 0;
	}
	if(RI)// RI:����1��������ж������־����Ҫ������㡣
	{
		RI= 0;
		buffer[wptr++]= SBUF;
		wptr &= 0x0f;
	}
}

//���ڳ�ʼ��
void UartInit()//������:115200
{
	SCON= 0x50;		//�ɱ䲨���� 8λ���ݷ�ʽ �����ڽ�������
	T2L = (65536 - 35000000UL / 115200 / 4);//��ʱ��2
	T2H = (65536 - 35000000UL / 115200 / 4) >> 8;
	AUXR= 0x15;		//ѡ��ʱ��2��Ϊ�����ʷ�����
	wptr = 0x00;
	rptr = 0x00;
	busy= 0;
    SCON = (SCON & 0x3f) | 0x40;//UART1ģʽ, 0x00: ͬ����λ���, 0x40: 8λ����,�ɱ䲨����, 0x80: 9λ����,�̶�������, 0xc0: 9λ����,�ɱ䲨����

    ES  = 1;//�����ж�
    REN = 1;//�������
    P_SW1 &= 0x3f;
}

//���͵����ַ�
void UART1_PutChar(char dat)
{
    while(busy);
    busy=1;
    SBUF=dat;
}

//���յ����ַ�
char UART1_GetChar()
{
    return SBUF;
}

//�����ַ���
void UART1_PutStr(char *p)
{
	char *p1;
	p1=p;
	while(*p1)
	{
		UART1_PutChar(*p1++);
	}
}

void main()
{
    int num=0;
    char txt[32];
    P1M1 = 0;   P1M0 = 0;   //����Ϊ׼˫���
    P3M1 = 0;   P3M0 = 0;   //����Ϊ׼˫���
    P4M1 = 0;   P4M0 = 0;   //����Ϊ׼˫���
    P5M1 = 0;   P5M0 = 0;   //����Ϊ׼˫���
    P6M1 = 0;   P6M0 = 0;   //����Ϊ׼˫���
    P7M1 = 0;   P7M0 = 0;   //����Ϊ׼˫��� 
    EAXFR=1;
    CKCON= 0x00;
    WTST= 0x00;
    UartInit();
    EA = 1;
    ES = 1;
    while(1)
    {
        if(rptr != wptr)
	 	{
	 		UART1_PutChar(buffer[rptr++]);
	 		rptr &= 0x0f;
	 	}
        sprintf(txt, "num:%d",num++);
        UART1_PutStr(txt);
        Delay200ms();
    }
}