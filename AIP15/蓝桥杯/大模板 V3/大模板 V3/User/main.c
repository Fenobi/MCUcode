/* 
		��ģ�� V3 ����˵�� ������������ ����ʹ�ô˰汾 ����Ϊ�Ҿ���������������������΢�е���鷳�ģ�
		
		�Ż���ƴ��ڳ���ʱ �ڴ��������������
		
		���̵������£�
		
		-------------Led���-------------
		Led X �� -> Function_Buf[X] |= 1
		Led X �� -> Function_Buf[X] &= 0
		Led X �����л� -> Function_Buf[X] ^= 1
		
		-------------Seg���-------------
		Point X �� -> Function_Buf[X] |= 1  << 4
		Point X �� -> Function_Buf[X] &= 0  << 4
		Point X �����л� -> Function_Buf[X] ^= 1  << 4
		
*/

/* �궨���������� */
#define Key_Slow 10 //��������ʱ��
#define Seg_Slow 500 //����ܼ���ʱ��
#define Uart_Slow 200 //���ڼ���ʱ��
#define Uart_Max_Commad 10 //����ָ�������

/* ͷ�ļ��������� */
#include <Init.h> //��ʼ��ר��ͷ�ļ�
#include <Key.h> //����ר��ͷ�ļ�
#include <Seg.h> //�����ר��ͷ�ļ�
#include <Led.h> //Ledר��ͷ�ļ�
#include <Uart.h> //����ר��ͷ�ļ�

/* ������������ */
unsigned int Proc_Slow_Down;//��������ר�ñ���
unsigned char Key_Val,Key_Old;//����ɨ��ר�ñ���
unsigned char Scan_Pos;//��̬ɨ��ר�ñ���
unsigned char Seg_Buf[8] = {10,10,10,10,10,10,10,10};//��ʾ���ݴ������ Ĭ��Ϩ��
unsigned char Function_Buf[8] = {0,0,0,0,0,0,0,0};//�������ݴ������ ��λ-Led״̬ ��λ-С����״̬
unsigned char Uart_Recv[10];//���ڽ������ݴ������� Ĭ��10���ֽ� ���������ݽϳ� �ɸ�������ֽ���
unsigned char Uart_Recv_Index;//���ڽ�������ָ��
unsigned char Uart_Send[10];//���ڽ������ݴ������� Ĭ��10���ֽ� ���������ݽϳ� �ɸ�������ֽ���

/* ���������� */
void Key_Proc()
{
	unsigned char Key_Up,Key_Down;//����ֲ�������С�ڴ�ռ��
	if(Proc_Slow_Down % Key_Slow) return;//�������ٳ���
	
	Key_Val = Key_KBD_Read();//��ȡ��������ֵ
	Key_Down = Key_Val & (Key_Val ^ Key_Old);//��׽�����½���
	Key_Up = ~Key_Val & (Key_Val ^ Key_Old);//��׽�����Ͻ���
	Key_Old = Key_Val;//����ɨ�����
	

}

/* ��Ϣ������ */
void Seg_Proc()
{
	if(Proc_Slow_Down % Seg_Slow) return;//��Ϣ���ٳ���
	
}

/* ���������� */
void Led_Proc()
{
	
}

/* ���ڴ����� */
void Uart_Proc()
{
	if(Proc_Slow_Down % Uart_Slow) return;//���ڼ��ٳ���	
	
}

/* ��ʱ��0��ʼ������ */
void Timer0Init(void)		//1����@12.000MHz
{
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0x18;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	ET0 = 1;		//��ʱ��0�жϴ�
	EA = 1;			//���жϴ�
}

/* ��ʱ��0�жϷ����� */
void Timer0Server() interrupt 1
{
	if(++Proc_Slow_Down == 500) Proc_Slow_Down = 0;//����ר��
	if(++Scan_Pos == 8) Scan_Pos = 0;//ɨ��ר��
	Seg_Disp(Scan_Pos,Seg_Buf[Scan_Pos],Function_Buf[Scan_Pos] & 0xF0);//�������ʾ
	Led_Disp(Scan_Pos,Function_Buf[Scan_Pos] & 0x0F);//Led��ʾ
}

/* ����1�жϷ����� */
void Uart1Server() interrupt 4
{
	if(RI == 1 && Uart_Recv_Index < Uart_Max_Commad) //���ڽ�������
	{
		Uart_Recv[Uart_Recv_Index] = SBUF;
		Uart_Recv_Index++;
		RI = 0;
	}
}

void main()
{
	Sys_Init();//�ϵ�ϵͳ��ʼ��
	UartInit();	//���ڳ�ʼ��
	Timer0Init();//��ʱ��0��ʼ��
	while(1)
	{
		Key_Proc();
		Seg_Proc();
		Led_Proc();
		Uart_Proc();
	}
}
