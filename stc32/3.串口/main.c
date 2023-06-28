#include <STC32G.H>

bit busy;
int wptr;
char rptr;
char buffer[64];

void Delay200ms()		//@22.1184MHz
{
	unsigned long i;

	_nop_();
	_nop_();
	i = 1105918UL;
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
		wptr &= 0xff;
	}
}

//���ڳ�ʼ��
void UartInit()//������:115200
{
	SCON= 0x50;		//�ɱ䲨���� 8λ���ݷ�ʽ �����ڽ�������
	T2L = 0xD0;		//��ʱ��2
	T2H = 0xFF;
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
    EAXFR=1;
    CKCON= 0x00;
    WTST= 0x00;
    UartInit();
    EA = 1;
    ES = 1;
    while(1)
    {
        UART1_PutStr(buffer);
        Delay200ms();
        
    }
}