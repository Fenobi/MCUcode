#include "led.h"//led灯函数头文件
#include "delay.h"//延时函数头文件


//LED灯初始化函数（设置锁存器为跟随输出）
void LED_Init(void)
{
	P27=1;P26=0;P25=0;//控制或非门Y4C输出高电平
	
	P0M1=0x00;P0M0=0x00;//设置P0组GPIO模式为准双向口（传统51GPIO模式）
}

//点亮指定一个LED灯函数
//例如：LED_One(3);  只有L3点亮
//例如：LED_One(0);  L1~L8全熄灭
void LED_One(u8 Lx)
{
	switch(Lx)
	{
		case 0: P0=0xff;break;//LED灯全熄灭
		case 1: P0=0xfe;break;
		case 2: P0=0xfd;break;
		case 3: P0=0xfb;break;
		case 4: P0=0xf7;break;
		case 5: P0=0xef;break;
		case 6: P0=0xdf;break;
		case 7: P0=0xbf;break;
		case 8: P0=0x7f;break;
	}
}

//led流水灯函数
void LED_LSD1(u16 ms)//从左到右流水
{
	u8 i;
	for(i=1;i<9;i++)
	{
		LED_One(i);
	  Delay_ms(ms);
	}
}

void LED_LSD2(u16 ms)//从右到左流水
{
	u8 i;
	for(i=8;i>0;i--)
	{
		LED_One(i);
	  Delay_ms(ms);
	}
}

//花样流水函数
void LED_HY(void)
{
	u16 ms;
	
	ms=50;//设置快闪速度
	P0=0x00;Delay_ms(ms);P0=0xff;Delay_ms(ms);//LED快闪
	P0=0x00;Delay_ms(ms);P0=0xff;Delay_ms(ms);
	P0=0x00;Delay_ms(ms);P0=0xff;Delay_ms(ms);
	P0=0x00;Delay_ms(ms);P0=0xff;Delay_ms(ms);
	P0=0x00;Delay_ms(ms);P0=0xff;Delay_ms(ms);
	
	ms=300;//设置流水时间
	LED_LSD1(ms);//LED左右流水
	LED_LSD2(ms);
	
	
	
	//呼吸灯程序（没有写完）
//	ms=100;
//	for(i;i<100;i++) //LED呼吸灯
//	{
//		P0=0x00;
//		Delay_ms(ms);//亮
//		P0=0xff;
//		Delay_ms(20-ms);//暗
//		ms--;
//	}		
//	
//	for(i;i<100;i++) //LED呼吸灯
//	{
//		P0=0x00;
//		Delay_ms(20-ms);//亮
//		P0=0xff;
//		Delay_ms(ms);//暗
//		ms--;
//	}	
	
	
	
	
	
	

}
