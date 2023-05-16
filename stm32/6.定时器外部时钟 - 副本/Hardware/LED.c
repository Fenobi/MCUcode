#include "include.h"


void LED_Init(void)//初始化LED引脚函数
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能打开GPIOA时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;  //定义GPIO结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //选择GPIO模式:推挽
	GPIO_InitStructure.GPIO_Pin = 0x00ff;//选择GPIO初始化引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //选择GPIO输出速度
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //最后初始化GPIO
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_0 |GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7);//初始化GPIO引脚为低电平
}

void LED1_ON(void)//LED1点亮函数
{
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
}

void LED1_OFF(void)//LED1熄灭函数
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
}

void LED1_Turn(void)//LED1翻转函数
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	}
}

void Running_water_LED(uint32_t ms)//流水灯函数
{
	char i;
	for (i = 0; i < 8;++i)
	{
		GPIO_WriteBit(GPIOA, (0X0001 << i), Bit_SET);
		Delay_ms(ms);
		GPIO_WriteBit(GPIOA, (0X0001 << i), Bit_RESET);
	}
}
