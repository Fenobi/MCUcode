/**************************************************************************************
实验现象：LED&交通灯模块上的D1指示灯闪烁
		  
接线说明：1，STM8S单片机-->LED&交通灯模块
		   		PC1-->D1	
	
注意事项：程序下载完成后再次按下STM8S单片机上的复位按钮RST即可运行程序																			  
***************************************************************************************/



#include "stm8s.h"      /*  添加库函数头文件 */
#include "led.h"



/*******************************************************************************
**函数名称：void delay(unsigned int ms)     Name: void delay(unsigned int ms)
**功能描述：大概延时
**入口参数：unsigned int ms   输入大概延时数值
**输出：无
*******************************************************************************/
void delay(unsigned int ms)
{
    unsigned int x , y;
    for(x = ms; x > 0; x--)           /*  通过一定周期循环进行延时*/
      for(y = 3000 ; y > 0 ; y--);
}



/* 主函数 */
int main(void)
{
    //内部时钟为1分频 = 16Mhz
    CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);
    InitLED();              //调用LED初始化函数
    while(1)
    {
        GPIO_WriteLow(GPIOA , GPIO_PIN_ALL); 
          GPIO_WriteLow(GPIOB , GPIO_PIN_ALL); 
        GPIO_WriteLow(GPIOC , GPIO_PIN_ALL);
        GPIO_WriteLow(GPIOD , GPIO_PIN_ALL);
          GPIO_WriteLow(GPIOE , GPIO_PIN_ALL); 
        //LED1_ON();     //点亮LED1
        delay(200);   //空跑大概延时
        GPIO_WriteHigh(GPIOA , GPIO_PIN_ALL); 
          GPIO_WriteHigh(GPIOB , GPIO_PIN_ALL); 
        GPIO_WriteHigh(GPIOC , GPIO_PIN_ALL);
        GPIO_WriteHigh(GPIOD , GPIO_PIN_ALL);
          GPIO_WriteHigh(GPIOE , GPIO_PIN_ALL); 
        //LED1_OFF();    //点灭LED1
        delay(200);   //空跑大概延时
    }
}
//是一个宏定义；在固件库中，它的作用就是检测传递给函数的参数是否是有效的参数
void assert_failed(u8* file, u32 line)
{ 
    while (1)
    {
        
    }
}