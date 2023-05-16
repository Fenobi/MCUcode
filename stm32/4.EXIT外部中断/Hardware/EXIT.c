#include "include.h"

void EXIT_Init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//设置时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//设置AFIO使能

	//GPIO配置
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);//初始化

	//AFIO配置
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource6); // 选择 GPIO 管脚用作外部中断线路

	//EXTI配置
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line6; // 外部线路
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	   // 中断请求
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
	EXTI_Init(&EXTI_InitStructure);
	
	//配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//选择通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//先占优先级和从优先级值
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}

