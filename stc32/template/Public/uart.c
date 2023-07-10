#include "uart.h"

bit busy;
int wptr;
char rptr;
char buffer[64];

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

void UART4_int (void) interrupt 18
{
	if(S4CON & 0x02)
	{
		S4CON &= ~0x02;  //Clear Tx flag  ������ͱ�־λ
		busy=0;
	}
	if(S4CON & 0x01)
	{
		S4CON &= ~0x01;  //Clear Rx flag	������ձ�־λ
		buffer[wptr++]= S4BUF;
		wptr &= 0xff;
	}
}

//���ڳ�ʼ��
void UART1_config()
{
	SCON= 0x50;		//�ɱ䲨���� 8λ���ݷ�ʽ �����ڽ�������
	T2L = Baudrate1;		//��ʱ��2
	T2H = Baudrate1>>8;
	AUXR= 0x15;		//ѡ��ʱ��2��Ϊ�����ʷ�����
	wptr = 0x00;
	rptr = 0x00;
	busy= 0;

		// TR1 = 0;
		// AUXR &= ~0x01;                                        //S1 tmr Use Timer1;
		// AUXR |=  (1<<6);                                      //Timer1 set as 1T mode
		// TMOD &= ~(1<<6);                                      //Timer1 set As Timer
		// TMOD &= ~0x30;                                        //Timer1_16bitAutoReload;
		// TH1 = (u8)(Baudrate1 / 256);
		// TL1 = (u8)(Baudrate1 % 256);
		// ET1 = 0;    				                           	//��ֹ�ж�
		// INTCLKO &= ~0x02;		                               	//�����ʱ��
		// TR1  = 1;


    SCON = (SCON & 0x3f) | 0x40;                              	//UART1ģʽ, 0x00: ͬ����λ���, 0x40: 8λ����,�ɱ䲨����, 0x80: 9λ����,�̶�������, 0xc0: 9λ����,�ɱ䲨����
//  PS  = 1;                                                  	//�����ȼ��ж�
    ES  = 1;                                                  	//�����ж�
    REN = 1;                                                 	 //�������
    P_SW1 &= 0x3f;
//  P_SW1 |= 0x00;                                            	//UART1 switch to, 0x00: P3.0 P3.1, 0x40: P3.6 P3.7, 0x80: P1.6 P1.7, 0xC0: P4.3 P4.4

}

void SetTimer2Baudraye(u32 dat)
{
	S4CON = 0x10;                       //8λ����, ʹ��Timer2�������ʷ�����, �������
	T2H = dat>>8;
	T2L = dat;
	AUXR = 0x14;
}

void UART4_config(u16 tmr)              // ѡ��ʱ��Դ, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer4��������.
{
	if(tmr == 2)													//ʹ��TIM2��Ϊ������ʱ��Դ
	{
		SetTimer2Baudraye(Baudrate4);
	}
	else
	{
		S4CON = 0x50;                       //8λ����, ʹ��Timer4�������ʷ�����, �������
		T4H = Baudrate4>>8;
		T4L = Baudrate4;
		T4T3M = 0xA0;												//��ʱ��4��ʼ����������Ƶ
	}
//		P_SW2 &= ~0x04;                   //UART4 switch bit2 to: 0: P0.2 P0.3ѡ������
	P_SW2 |= 0x04;                      //UART4 switch bit2 to: 1: P5.2 P5.3ѡ������ P52:RX P53:TX 
	wptr = 0x00;												//������־λ����
	rptr = 0x00;
	busy= 0;

	IE2 |= 0x10;                        //����UART4�ж�
	
}

//���͵����ַ�
void UART1_PutChar(char dat)
{
    while(busy);
    busy=1;
    SBUF=dat;
}

void UART4_PutChar(char ch)
{
	while(busy);
	busy=1;
	S4BUF = ch;
}

//���յ����ַ�
char UART1_GetChar()
{
    return SBUF;
}

char UART4_GetChar(void)
{  
  return (S4BUF);
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

void UART4_PutStr(char *st)
{
  while(*st)
  {
    UART4_PutChar(*st++);
  }
}