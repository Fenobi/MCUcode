#ifndef __LED_H
#define __LED_H

void LED_Init(void);//初始化LED引脚函数
void LED1_ON(void);//LED1点亮函数
void LED1_OFF(void);//LED1熄灭函数
void LED1_Turn(void);//LED1翻转函数
void Running_water_LED(uint32_t ms);//流水灯函数

#endif
