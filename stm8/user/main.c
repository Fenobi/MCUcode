/**************************************************************************************
ʵ������LED&��ͨ��ģ���ϵ�D1ָʾ����˸
		  
����˵����1��STM8S��Ƭ��-->LED&��ͨ��ģ��
		   		PC1-->D1	
	
ע���������������ɺ��ٴΰ���STM8S��Ƭ���ϵĸ�λ��ťRST�������г���																			  
***************************************************************************************/



#include "stm8s.h"      /*  ��ӿ⺯��ͷ�ļ� */
#include "led.h"



/*******************************************************************************
**�������ƣ�void delay(unsigned int ms)     Name: void delay(unsigned int ms)
**���������������ʱ
**��ڲ�����unsigned int ms   ��������ʱ��ֵ
**�������
*******************************************************************************/
void delay(unsigned int ms)
{
    unsigned int x , y;
    for(x = ms; x > 0; x--)           /*  ͨ��һ������ѭ��������ʱ*/
      for(y = 3000 ; y > 0 ; y--);
}



/* ������ */
int main(void)
{
    //�ڲ�ʱ��Ϊ1��Ƶ = 16Mhz
    CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);
    InitLED();              //����LED��ʼ������
    while(1)
    {
        GPIO_WriteLow(GPIOA , GPIO_PIN_ALL); 
          GPIO_WriteLow(GPIOB , GPIO_PIN_ALL); 
        GPIO_WriteLow(GPIOC , GPIO_PIN_ALL);
        GPIO_WriteLow(GPIOD , GPIO_PIN_ALL);
          GPIO_WriteLow(GPIOE , GPIO_PIN_ALL); 
        //LED1_ON();     //����LED1
        delay(200);   //���ܴ����ʱ
        GPIO_WriteHigh(GPIOA , GPIO_PIN_ALL); 
          GPIO_WriteHigh(GPIOB , GPIO_PIN_ALL); 
        GPIO_WriteHigh(GPIOC , GPIO_PIN_ALL);
        GPIO_WriteHigh(GPIOD , GPIO_PIN_ALL);
          GPIO_WriteHigh(GPIOE , GPIO_PIN_ALL); 
        //LED1_OFF();    //����LED1
        delay(200);   //���ܴ����ʱ
    }
}
//��һ���궨�壻�ڹ̼����У��������þ��Ǽ�⴫�ݸ������Ĳ����Ƿ�����Ч�Ĳ���
void assert_failed(u8* file, u32 line)
{ 
    while (1)
    {
        
    }
}