#include "led.h"


/*******************************************************************************
**�������ƣ�void InitLED()
**������������ʼ��LED����
**��ڲ�������
**�������
*******************************************************************************/
void InitLED(void)
{
    //����PC1Ϊ����������� ��LED1
  GPIO_Init(GPIOA , GPIO_PIN_ALL , GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOB , GPIO_PIN_ALL , GPIO_MODE_OUT_PP_LOW_FAST);
    GPIO_Init(GPIOC , GPIO_PIN_ALL , GPIO_MODE_OUT_PP_LOW_FAST);
    GPIO_Init(GPIOD , GPIO_PIN_ALL , GPIO_MODE_OUT_PP_LOW_FAST);
    GPIO_Init(GPIOE , GPIO_PIN_ALL , GPIO_MODE_OUT_PP_LOW_FAST);
}