#include <STC32G.H>

typedef unsigned char uint_8;
typedef unsigned int uint_16;
typedef unsigned char u8;
typedef unsigned int u16;
typedef char int8_t;
typedef int int16_t;

#define MAIN_Fosc 35000000UL
#define PWMB_CLOCK 35000000 //35M

void Delay10us()		//@35MHz
{
	unsigned long i;

	_nop_();
	i = 86UL;
	while (i) i--;
}

void Delay1ms()		//@35MHz
{
	unsigned long i;

	_nop_();
	_nop_();
	_nop_();
	i = 8748UL;
	while (i) i--;
}

void DelayMs(uint_16 n)
{
    while(n--)
        Delay1ms();
}

void Delay10Nus(uint_16 n)
{
    while(n--)
        Delay10us();
}

void MotorInit(u16 freq)
{

  P_SW2 |= 0x80;                           // 使能访问外部寄存器
  PWMB_PSCRL = (MAIN_Fosc/PWMB_CLOCK)-1;   //主频为35M,PWM分频到10M范围

  // 捕获/比较使能寄存器n(PWMx_CCRn)
  PWMB_CCER1 = 0x00; // 写 CCMRx 前必须先清零 CCxE 关闭通道
  PWMB_CCER2 = 0x00;

  // 捕获/比较模式寄存器n(PWMx_CCRn)
  PWMB_CCMR1 = 0x64; //通道模式配置 PWM1模式
  PWMB_CCMR2 = 0x64;
  PWMB_CCMR3 = 0x60;
  PWMB_CCMR4 = 0x60;
  
  PWMB_CCER1 = 0x55; //配置通道输出使能和极性
  PWMB_CCER2 = 0x55;

  PWMB_ARRH  = (u8)((PWMB_CLOCK/freq)>>8);  //设置周期时间，从0计数到设定数值
  PWMB_ARRL  = (u8)(PWMB_CLOCK/freq); //

  PWMB_CR1 |= 0x80;		//自动预装载允许
  PWMB_CR1 &= ~0x70;	//边沿对齐  向上计数
  
  PWMB_ENO = 0x00;
  PWMB_ENO = 0x01 | 0x04 | 0x10 | 0x40;//ENO5、ENO6、ENO7、ENO8使能

  //高级 PWM 通道 4P 输出脚选择位, 0x00:P1.6, 0x40:P2.6, 0x80:P6.6, 0xC0:P3.4
  PWMB_PS = 0x00;   	//高级 PWM 通道输出脚选择位
  PWMB_PS = 0x03 | 0x0c | 0x30 | 0xc0;	// 选择 PWM5_3 PWM6_3  PWM7_3 PWM8_3 通道

  PWMB_BKR = 0x80;			//使能主输出
  PWMB_CR1 |= 0x01;  		//开始计时

  P7M0 = 0xf0;        // P74,P75,P76,P77设置为推挽输出
  P7M1 = 0x00;

  //P7口上拉电阻控制寄存器 -- 0:禁止端口内部的4.1K上拉电阻; 1:使能端口内部的4.1K上拉电阻
  //P7PU |= 0xA0; // 这里表示P77和P75使能
  P7PU |= 0xF0; // 这里表示P77和P75和P76和P74使能

  P_SW2 &= 0x7f; // 禁止使能访问外部寄存器
}

void PWMCtrl1(int16_t motor)
{
    P_SW2 |= 0x80;
    PWMB_CCR5H = (u8)(motor >> 8); // 设置占空比时间p7.4
    PWMB_CCR5L = (u8)(motor);
    P_SW2 &= 0x7f;
}

void PWMCtrl2(int16_t motor)
{
    P_SW2 |= 0x80;
    PWMB_CCR6H = (u8)(motor >> 8); // 设置占空比时间p7.5
    PWMB_CCR6L = (u8)(motor);
    P_SW2 &= 0x7f;
}
void PWMCtrl3(int16_t motor)
{
    P_SW2 |= 0x80;
    PWMB_CCR7H = (u8)(motor >> 8); // 设置占空比时间p7.6
    PWMB_CCR7L = (u8)(motor);
    P_SW2 &= 0x7f;
}

void PWMCtrl4(int16_t motor)
{
    P_SW2 |= 0x80;
    PWMB_CCR8H = (u8)(motor >> 8); // 设置占空比时间p7.7
    PWMB_CCR8L = (u8)(motor);
    P_SW2 &= 0x7f;
}

void main()
{
    int i=0;
    MotorInit(12500);
    while(1)
    {
        PWMCtrl1(200);
        PWMCtrl2(400);
        PWMCtrl3(800);
        for(i=100;i<2000;++i)
        {    
            PWMCtrl4(i);
            Delay10Nus(10);
        }
        for(i=2000;i>100;--i)
        {
            PWMCtrl4(i);
            Delay10Nus(10);
        }
    }
}