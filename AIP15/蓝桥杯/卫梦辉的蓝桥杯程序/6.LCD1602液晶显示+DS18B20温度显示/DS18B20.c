#include "DS18B20.h"
#include "delay.h"

/**********DS18B20参数*************
*测温范围：-55—+125°在-10—+85度，精度为0.5度
*分辨率：9—12位，分变度0.5，0.25，0.125，0.0625。
*
************************/

char DS18B20_Reset()//DS18B20复位
{
    char flag;
    DS18B20_DQ=0;
    delay_1us(250);//延时480-960us
    DS18B20_DQ=1;
    delay_1us(25);//延时15-60us
    flag=DS18B20_DQ;
    delay_1us(200);//延时400us
    return flag;
}


void DS18B20_WriteData(unsigned char dat)//向DS18B20写数据
{
    unsigned char i;
    for(i=0;i<8;i++)
    {
        DS18B20_DQ=0;
        delay_1us(4);//延时4us
        DS18B20_DQ=dat&0x01;//取最低位
        delay_1us(25);//延时60us
        DS18B20_DQ=1;//释放总线
        dat=dat>>1;
    }
}

unsigned char DS18B20_ReadData()//向DS18B20读数据
{
    unsigned char i,dat;
    for(i=0;i<8;i++)
    {
        dat>>=1;
        DS18B20_DQ=0;
        delay_1us(4);//延时4us
        DS18B20_DQ=1;
        delay_1us(6);//延时6us
        if(DS18B20_DQ==1)
        {
            dat=dat|0x80;
        }
        delay_1us(50);//延时60us       
        DS18B20_DQ=1;//释放总线
    }
    return dat;
}


float DS18B20_Tem()//DS18B20返回温度值函数
{
    unsigned int DataH;
    unsigned char DataL;
    float Temp;

    DS18B20_Reset();//DS18B20复位
    DS18B20_WriteData(0xcc);//向DS18B20写数据(跳过ROM温度检测)
    DS18B20_WriteData(0x44);//向DS18B20写数据(启动温度转换)
    
    DS18B20_Reset();//DS18B20复位
    DS18B20_WriteData(0xcc);//向DS18B20写数据(跳过ROM温度检测)
    DS18B20_WriteData(0xBE);//向DS18B20写数据(读暂存器命令)
    DataL=DS18B20_ReadData();//向DS18B20读数据(读低八位)
    DataH=DS18B20_ReadData();//向DS18B20读数据(读高八位)
    DataH=(DataH<<8) | DataL;//组合
    if((DataH & 0xF800) == 0xF800)//温度为负温度,则取反然后加1
    {
        DataH = ~DataH+1;
    }
    Temp=DataH * 0.0625;
    return Temp;
}
