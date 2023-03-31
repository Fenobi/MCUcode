#include "led.h"


/*******************************************************************************
**函数名称：void InitLED()
**功能描述：初始化LED函数
**入口参数：无
**输出：无
*******************************************************************************/
void InitLED(void)
{
    //设置PC1为快速推挽输出 ，LED1
  GPIO_Init(GPIOA , GPIO_PIN_ALL , GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOB , GPIO_PIN_ALL , GPIO_MODE_OUT_PP_LOW_FAST);
    GPIO_Init(GPIOC , GPIO_PIN_ALL , GPIO_MODE_OUT_PP_LOW_FAST);
    GPIO_Init(GPIOD , GPIO_PIN_ALL , GPIO_MODE_OUT_PP_LOW_FAST);
    GPIO_Init(GPIOE , GPIO_PIN_ALL , GPIO_MODE_OUT_PP_LOW_FAST);
}