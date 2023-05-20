/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC15Fxx 系列 输出任意周期和任意占空比的PWM实例-----------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966-------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.GXWMCU.com --------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序        */
/* 如果要在文章中应用此代码,请在文章中注明使用了STC的资料及程序        */
/*---------------------------------------------------------------------*/

//本示例在Keil开发环境下请选择Intel的8058芯片型号进行编译
//若无特别说明,工作频率一般为11.0592MHz


#include "reg51.h"

#define CYCLE   0x1000L     //定义PWM周期(最大值为32767)
#define DUTY    50L         //定义占空比为10%

#define PWMC        (*(unsigned int  volatile xdata *)0xfff0)
#define PWMCH       (*(unsigned char volatile xdata *)0xfff0)
#define PWMCL       (*(unsigned char volatile xdata *)0xfff1)
#define PWMCKS      (*(unsigned char volatile xdata *)0xfff2)
#define PWM2T1      (*(unsigned int  volatile xdata *)0xff00)
#define PWM2T1H     (*(unsigned char volatile xdata *)0xff00)
#define PWM2T1L     (*(unsigned char volatile xdata *)0xff01)
#define PWM2T2      (*(unsigned int  volatile xdata *)0xff02)
#define PWM2T2H     (*(unsigned char volatile xdata *)0xff02)
#define PWM2T2L     (*(unsigned char volatile xdata *)0xff03)
#define PWM2CR      (*(unsigned char volatile xdata *)0xff04)
#define PWM3T1      (*(unsigned int  volatile xdata *)0xff10)
#define PWM3T1H     (*(unsigned char volatile xdata *)0xff10)
#define PWM3T1L     (*(unsigned char volatile xdata *)0xff11)
#define PWM3T2      (*(unsigned int  volatile xdata *)0xff12)
#define PWM3T2H     (*(unsigned char volatile xdata *)0xff12)
#define PWM3T2L     (*(unsigned char volatile xdata *)0xff13)
#define PWM3CR      (*(unsigned char volatile xdata *)0xff14)
#define PWM4T1      (*(unsigned int  volatile xdata *)0xff20)
#define PWM4T1H     (*(unsigned char volatile xdata *)0xff20)
#define PWM4T1L     (*(unsigned char volatile xdata *)0xff21)
#define PWM4T2      (*(unsigned int  volatile xdata *)0xff22)
#define PWM4T2H     (*(unsigned char volatile xdata *)0xff22)
#define PWM4T2L     (*(unsigned char volatile xdata *)0xff23)
#define PWM4CR      (*(unsigned char volatile xdata *)0xff24)
#define PWM5T1      (*(unsigned int  volatile xdata *)0xff30)
#define PWM5T1H     (*(unsigned char volatile xdata *)0xff30)
#define PWM5T1L     (*(unsigned char volatile xdata *)0xff31)
#define PWM5T2      (*(unsigned int  volatile xdata *)0xff32)
#define PWM5T2H     (*(unsigned char volatile xdata *)0xff32)
#define PWM5T2L     (*(unsigned char volatile xdata *)0xff33)
#define PWM5CR      (*(unsigned char volatile xdata *)0xff34)
#define PWM6T1      (*(unsigned int  volatile xdata *)0xff40)
#define PWM6T1H     (*(unsigned char volatile xdata *)0xff40)
#define PWM6T1L     (*(unsigned char volatile xdata *)0xff41)
#define PWM6T2      (*(unsigned int  volatile xdata *)0xff42)
#define PWM6T2H     (*(unsigned char volatile xdata *)0xff42)
#define PWM6T2L     (*(unsigned char volatile xdata *)0xff43)
#define PWM6CR      (*(unsigned char volatile xdata *)0xff44)
#define PWM7T1      (*(unsigned int  volatile xdata *)0xff50)
#define PWM7T1H     (*(unsigned char volatile xdata *)0xff50)
#define PWM7T1L     (*(unsigned char volatile xdata *)0xff51)
#define PWM7T2      (*(unsigned int  volatile xdata *)0xff52)
#define PWM7T2H     (*(unsigned char volatile xdata *)0xff52)
#define PWM7T2L     (*(unsigned char volatile xdata *)0xff53)
#define PWM7CR      (*(unsigned char volatile xdata *)0xff54)

sfr PIN_SW2 =   0xba;

sfr P0M1    =   0x93;
sfr P0M0    =   0x94;
sfr P1M1    =   0x91;
sfr P1M0    =   0x92;
sfr P2M1    =   0x95;
sfr P2M0    =   0x96;
sfr P3M1    =   0xb1;
sfr P3M0    =   0xb2;
sfr P4M1    =   0xb3;
sfr P4M0    =   0xb4;
sfr P5M1    =   0xC9;
sfr P5M0    =   0xCA;
sfr P6M1    =   0xCB;
sfr P6M0    =   0xCC;
sfr P7M1    =   0xE1;
sfr P7M0    =   0xE2;

sfr PWMCFG  =   0xf1;
sfr PWMCR   =   0xf5;
sfr PWMIF   =   0xf6;
sfr PWMFDCR =   0xf7;

void main()
{
    P0M0 = 0x00;
    P0M1 = 0x00;
    P1M0 = 0x00;
    P1M1 = 0x00;
    P2M0 = 0x00;
    P2M1 = 0x00;
    P3M0 = 0x00;
    P3M1 = 0x00;
    P4M0 = 0x00;
    P4M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;
    P6M0 = 0x00;
    P6M1 = 0x00;
    P7M0 = 0x00;
    P7M1 = 0x00;

    PIN_SW2 |= 0x80;                //使能访问XSFR
    PWMCFG = 0x00;                  //配置PWM的输出初始电平为低电平
    PWMCKS = 0x00;                  //选择PWM的时钟为Fosc/(0+1)
    PWMC = CYCLE;                   //设置PWM周期
    PWM2T1 = 0x0000;                //设置PWM2第1次反转的PWM计数
    PWM2T2 = CYCLE * DUTY / 100;    //设置PWM2第2次反转的PWM计数
                                    //占空比为(PWM2T2-PWM2T1)/PWMC
    PWM2CR = 0x00;                  //选择PWM2输出到P3.7,不使能PWM2中断
    PWMCR = 0x01;                   //使能PWM信号输出
    PWMCR |= 0x80;                  //使能PWM模块
    PIN_SW2 &= ~0x80;

    while (1)
    {
        
    }
}

