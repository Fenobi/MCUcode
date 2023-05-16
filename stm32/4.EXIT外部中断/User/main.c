#include "include.h"

char KeyNum;
char led=0;
void EXTI9_5_IRQHandler(void)
{
  led = ~led;
  GPIO_WriteBit(GPIOA, GPIO_Pin_1, (BitAction)led);
  EXTI_ClearITPendingBit(EXTI_Line6);
}

int main(void)
{
  OLED_Init();
  Key_Init();
  OLED_Clear();
  LED_Init();
  EXIT_Init();
  while (1)
  {
    
  }
}
