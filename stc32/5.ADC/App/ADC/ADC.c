#include "ADC.h"

void ADC_Init()
{
    P1M0 = 0x00; P1M1 = 0x03; //P10��P11����̬
    
    P_SW2 |= 0x80;
    ADCTIM = 0x3f;					//���� ADC �ڲ�ʱ��ADC����ʱ�������ֵ
    P_SW2 &= 0x7f;
    ADCCFG = 0x2f;					//���� ADC ʱ��Ϊϵͳʱ��/2/16/16��ת������Ҷ���
    ADC_CONTR = 0x80; 			    //ʹ�� ADC ģ��

}

u16 ADC_Read(u8 ADC_Channel_x)//xΪ0~1
{  
    ADC_RES = 0;
    ADC_RESL = 0;

	ADC_CONTR = (ADC_CONTR & 0xF0) | 0x40 | ADC_Channel_x;//���� AD ת��
	_nop_();
    _nop_();
    _nop_();
    _nop_();

    while((ADC_CONTR & 0x20) == 0);          //�ȴ�ADC���
    ADC_CONTR &= ~0x20;     		         //���ADC������־
    return  (((u16)ADC_RES << 8) | ADC_RESL);//Ĭ����12λ
}

float ADC_Vol(u16 vol)
{
    return ADC_Vref * vol / 4096;
}