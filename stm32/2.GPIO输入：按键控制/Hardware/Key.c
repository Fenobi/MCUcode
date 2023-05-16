#include "stm32f10x.h"  // Device header
#include "Delay.h"

void Key_Init(void)//按键引脚初始化函数
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//打开GPIO时钟
	GPIO_InitTypeDef GPIO_InitStructure1;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_Out_OD; // 选择输出开漏模式
	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure1);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//选择输入上拉模式IPU
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t Key_GetNum(void)//按键读取函数
{
	uint8_t KeyNum = 0;
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_RESET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,Bit_RESET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_RESET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_13,Bit_RESET);
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) == 0)//判断按键是否按下
	{
		Delay_ms(20);//按键延时消抖	
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) == 0);//如果按键按下，程序停留在这里
		Delay_ms(20);
		KeyNum = 1;
	}
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == 0)
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == 0);
		Delay_ms(20);
		KeyNum = 2;
	}
	
	return KeyNum;
}
