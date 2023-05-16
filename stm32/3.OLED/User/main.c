#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Key.h"
#include "OLED.h"

 char KeyNum;

int main(void)
{
  OLED_Init();
  Key_Init();
  OLED_Clear();
  //LED_Init();
  int32_t num = 1;
  while (1)
  {
    KeyNum = Key_GetNum();
	OLED_ShowString(1,1,"Hello World!");
	OLED_ShowString(2,1,"A=+ B=- C=0");
	OLED_ShowString(3,1,"count:");
    OLED_ShowSignedNum(3, 7, num, 3);
    if (KeyNum == 1)
    {
      ++num;
    }
    else if (KeyNum == 2)
    {
      --num;
    }
    else if (KeyNum == 3)
    {
      num = 0;
    }
  }
}
