#include <Uart.h>

/* ���ڳ�ʼ������ */
void UartInit(void)		//9600bps@12.000MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x01;		//����1ѡ��ʱ��2Ϊ�����ʷ�����
	AUXR |= 0x04;		//��ʱ��ʱ��1Tģʽ
	T2L = 0xC7;		//���ö�ʱ��ʼֵ
	T2H = 0xFE;		//���ö�ʱ��ʼֵ
	AUXR |= 0x10;		//��ʱ��2��ʼ��ʱ
	ES = 1;					//�����жϴ�
	EA = 1;					//���жϴ�
}

/* �ֽڷ��ͺ��� */
void SendByte(unsigned char dat)
{
	SBUF = dat;//��dat���ݸ���SBUF�������ݷ��ͳ�ȥ
	while(TI == 0);//�ȴ����ݷ���
	TI = 0;//�����ͱ�־λ����
}

/* �ַ������ͺ��� */
void Uart_Send_String(unsigned char *dat)
{
	while(*dat != '\0')//���ַ���Ϊ��ʱ����������
		SendByte(*dat++);//���ͺ�ָ��dat��1��ָ����һ���ֽ�
}