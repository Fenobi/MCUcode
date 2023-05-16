#include "include.h"

uint16_t num = 0;


void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
        //LED1_Turn();
		OLED_ShowNum(1, 1, num, 4);
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		++num;
	}
}

void EXTI9_5_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line6) == SET)
	{
		LED1_Turn();
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
}

int main()
{
	LED_Init();
	OLED_Init();
	Timer_Init();
	OLED_Clear();
	EXIT_Init();
	while (1)
	{
        
	}
}
