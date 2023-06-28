#include <STC32G.H>

typedef unsigned char uint_8;
typedef unsigned int uint_16;
typedef unsigned char u8;
typedef unsigned int u16;
typedef char int8_t;
typedef int int16_t;

#define MAIN_Fosc 35000000UL
#define PWMB_CLOCK 35000000 //35M

void Delay10us()		//@35MHz
{
	unsigned long i;

	_nop_();
	i = 86UL;
	while (i) i--;
}

void Delay1ms()		//@35MHz
{
	unsigned long i;

	_nop_();
	_nop_();
	_nop_();
	i = 8748UL;
	while (i) i--;
}

void DelayMs(uint_16 n)
{
    while(n--)
        Delay1ms();
}

void Delay10Nus(uint_16 n)
{
    while(n--)
        Delay10us();
}

void MotorInit(u16 freq)
{

  P_SW2 |= 0x80;                           // ʹ�ܷ����ⲿ�Ĵ���
  PWMB_PSCRL = (MAIN_Fosc/PWMB_CLOCK)-1;   //��ƵΪ35M,PWM��Ƶ��10M��Χ

  // ����/�Ƚ�ʹ�ܼĴ���n(PWMx_CCRn)
  PWMB_CCER1 = 0x00; // д CCMRx ǰ���������� CCxE �ر�ͨ��
  PWMB_CCER2 = 0x00;

  // ����/�Ƚ�ģʽ�Ĵ���n(PWMx_CCRn)
  PWMB_CCMR1 = 0x64; //ͨ��ģʽ���� PWM1ģʽ
  PWMB_CCMR2 = 0x64;
  PWMB_CCMR3 = 0x60;
  PWMB_CCMR4 = 0x60;
  
  PWMB_CCER1 = 0x55; //����ͨ�����ʹ�ܺͼ���
  PWMB_CCER2 = 0x55;

  PWMB_ARRH  = (u8)((PWMB_CLOCK/freq)>>8);  //��������ʱ�䣬��0�������趨��ֵ
  PWMB_ARRL  = (u8)(PWMB_CLOCK/freq); //

  PWMB_CR1 |= 0x80;		//�Զ�Ԥװ������
  PWMB_CR1 &= ~0x70;	//���ض���  ���ϼ���
  
  PWMB_ENO = 0x00;
  PWMB_ENO = 0x01 | 0x04 | 0x10 | 0x40;//ENO5��ENO6��ENO7��ENO8ʹ��

  //�߼� PWM ͨ�� 4P �����ѡ��λ, 0x00:P1.6, 0x40:P2.6, 0x80:P6.6, 0xC0:P3.4
  PWMB_PS = 0x00;   	//�߼� PWM ͨ�������ѡ��λ
  PWMB_PS = 0x03 | 0x0c | 0x30 | 0xc0;	// ѡ�� PWM5_3 PWM6_3  PWM7_3 PWM8_3 ͨ��

  PWMB_BKR = 0x80;			//ʹ�������
  PWMB_CR1 |= 0x01;  		//��ʼ��ʱ

  P7M0 = 0xf0;        // P74,P75,P76,P77����Ϊ�������
  P7M1 = 0x00;

  //P7������������ƼĴ��� -- 0:��ֹ�˿��ڲ���4.1K��������; 1:ʹ�ܶ˿��ڲ���4.1K��������
  //P7PU |= 0xA0; // �����ʾP77��P75ʹ��
  P7PU |= 0xF0; // �����ʾP77��P75��P76��P74ʹ��

  P_SW2 &= 0x7f; // ��ֹʹ�ܷ����ⲿ�Ĵ���
}

void PWMCtrl1(int16_t motor)
{
    P_SW2 |= 0x80;
    PWMB_CCR5H = (u8)(motor >> 8); // ����ռ�ձ�ʱ��p7.4
    PWMB_CCR5L = (u8)(motor);
    P_SW2 &= 0x7f;
}

void PWMCtrl2(int16_t motor)
{
    P_SW2 |= 0x80;
    PWMB_CCR6H = (u8)(motor >> 8); // ����ռ�ձ�ʱ��p7.5
    PWMB_CCR6L = (u8)(motor);
    P_SW2 &= 0x7f;
}
void PWMCtrl3(int16_t motor)
{
    P_SW2 |= 0x80;
    PWMB_CCR7H = (u8)(motor >> 8); // ����ռ�ձ�ʱ��p7.6
    PWMB_CCR7L = (u8)(motor);
    P_SW2 &= 0x7f;
}

void PWMCtrl4(int16_t motor)
{
    P_SW2 |= 0x80;
    PWMB_CCR8H = (u8)(motor >> 8); // ����ռ�ձ�ʱ��p7.7
    PWMB_CCR8L = (u8)(motor);
    P_SW2 &= 0x7f;
}

void main()
{
    int i=0;
    MotorInit(12500);
    while(1)
    {
        PWMCtrl1(200);
        PWMCtrl2(400);
        PWMCtrl3(800);
        for(i=100;i<2000;++i)
        {    
            PWMCtrl4(i);
            Delay10Nus(10);
        }
        for(i=2000;i>100;--i)
        {
            PWMCtrl4(i);
            Delay10Nus(10);
        }
    }
}