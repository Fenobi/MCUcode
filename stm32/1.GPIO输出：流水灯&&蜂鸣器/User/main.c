#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE); // 时钟使能
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructureb;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//io模式：推挽
	GPIO_InitStructure.GPIO_Pin = 0x00ff; // 引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//频率

	GPIO_InitStructureb = GPIO_InitStructure;
	GPIO_InitStructureb.GPIO_Pin &= GPIO_Pin_5;
	GPIO_Init(GPIOA, &GPIO_InitStructure); // 将数据写入
	GPIO_Init(GPIOB, &GPIO_InitStructureb); // 将数据写入
	// GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
	while (1)
	{
		// int i = 100;
		// while((i-=1))
		// {
		// 	GPIO_WriteBit(GPIOB, GPIO_Pin_5, Bit_SET);
		// 	Delay_ms(i);
		// 	GPIO_WriteBit(GPIOB, GPIO_Pin_5, Bit_RESET);
		// 	Delay_ms(i);
			
		// }
		char i;
		for (i = 0; i < 8;++i)
		{
			GPIO_WriteBit(GPIOA, (0X0001 << i), Bit_SET);
			Delay_s(1);
			GPIO_WriteBit(GPIOA, (0X0001 << i), Bit_RESET);
		}
	}
}
