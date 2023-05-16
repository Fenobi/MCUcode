#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 时钟使能
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//io模式：推挽
	GPIO_InitStructure.GPIO_Pin = 0x00ff; // 引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//频率

	GPIO_Init(GPIOA, &GPIO_InitStructure); // 将数据写入
	while(1)
	{
		
	}
}
