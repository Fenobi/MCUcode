#include "uart.h"

bit busy;
int wptr;
char rptr;
char buffer[64];

void UART1_int (void) interrupt 4
{
	if(TI)// TI:����1��������ж������־����Ҫ�������㡣
	{
		TI= 0;
		busy= 0;
	}
	if(RI)// RI:����1��������ж������־����Ҫ�������㡣
	{
		RI= 0;
		buffer[wptr++]= SBUF;
		wptr &= 0x0f;
	}
}

//���ڳ�ʼ��
void UartInit()//������:115200
{
	SCON= 0x50;		//�ɱ䲨���� 8λ���ݷ�ʽ �������ڽ�������
	T2L = (65536 - 35000000UL / 115200 / 4);//��ʱ��2
	T2H = (65536 - 35000000UL / 115200 / 4) >> 8;
	AUXR= 0x15;		//ѡ��ʱ��2��Ϊ�����ʷ�����
	wptr = 0x00;
	rptr = 0x00;
	busy= 0;
    SCON = (SCON & 0x3f) | 0x40;//UART1ģʽ, 0x00: ͬ����λ���, 0x40: 8λ����,�ɱ䲨����, 0x80: 9λ����,�̶�������, 0xc0: 9λ����,�ɱ䲨����

    ES  = 1;//�����ж�
    REN = 1;//��������
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