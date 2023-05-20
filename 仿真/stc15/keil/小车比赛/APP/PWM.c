#include "pwm.h"

void pwminit()
{   
    P3M0 = 0x80; P3M1 = 0x00; 
    P2M0 = 0x0e; P2M1 = 0x00; 

    P_SW2 |= 0x80; 
    
    PWMCFG = 0x00;                  //配置PWM的输出初始电平为低电平
    PWMCKS = 0x00;                  //选择PWM的时钟为Fosc/(0+1)
    PWMC = CYCLE;                   //设置PWM周期,定义PWM周期(最大值为32767)
    
    PWM2CR = 0x00;                  //选择PWM2输出到P3.7,不使能PWM2中断   
    PWM3CR = 0x00; 
    PWM4CR = 0x00;
    PWM5CR = 0x00;
    
    PWM2T1 = 0x0001;      
    PWM2T2 = 0;
    PWM3T1 = 0x0001;        
    PWM3T2 = 0;
    PWM4T1 = 0x0001;            
    PWM4T2 = 0;
    PWM5T1 = 0x0001;            
    PWM5T2 = 0;
    PWMCR |= 0x80;                  //使能PWM模块
    P_SW2 &=~0x80; 
}
void pwm2( unsigned int DUTY)
{   
    if(DUTY==0)
    {
        PWMCR &=~0x01;
        PWM2=0; 
    }
    else if(DUTY==100)
    {
        PWMCR &=~0x01;
        PWM2=1; 
    }
    else
    {
        P_SW2 |= 0x80;                  //使能访问PWM在扩展RAM区的特殊功能寄存器XSFR
        PWM2T1 = 0x0001;                //设置PWM2第1次反转的PWM计数
        PWM2T2 = CYCLE * DUTY / 100;    //设置PWM2第2次反转的PWM计数
        P_SW2 &=~0x80;                  //占空比为(PWM2T2-PWM2T1)/PWMC
        PWMCR |= 0x01;                  //使能PWM信号输出
    }
}
void pwm3(unsigned int DUTY)
{         
    if(DUTY==0)
    {
        PWMCR &=~0x02;
        PWM3=0; 
    }
    else if(DUTY==100)
    {
        PWMCR &=~0x02;
        PWM3=1; 
    }        
    else
    { 
        P_SW2 |= 0x80;
        PWM3T1 = 0x0001;   
        PWM3T2 = CYCLE * DUTY / 100;    
        P_SW2 &=~0x80;                 
        PWMCR |= 0x02;                   
    }        
}
void pwm4(unsigned int  DUTY)
{         
    if(DUTY==0)
    {
        PWMCR &=~0x04;
        PWM4=0; 
    }
    else if (DUTY==100)
    {
        PWMCR &=~0x04;
        PWM4=1; 
    }
    else
    {         
        P_SW2 |= 0x80;
        PWM4T1 = 0x0001;
        PWM4T2 = CYCLE * DUTY / 100;
        P_SW2 &=~0x80;                  
        PWMCR |= 0x04;
    }
}

void pwm5(unsigned int  DUTY)
{         
    if(DUTY==0)
    {
        PWMCR &=~0x08;
        PWM5=0; 
    }
    else if (DUTY==100)
    {
        PWMCR &=~0x08;
        PWM5=1; 
    }
    else
    {         
        P_SW2 |= 0x80;
        PWM5T1 = 0x0001;
        PWM5T2 = CYCLE * DUTY / 100;
        P_SW2 &=~0x80;                  
        PWMCR |= 0x08;
    }
}