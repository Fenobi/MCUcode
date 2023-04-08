#include "DS18B20.h"
#include "delay.h"

/**********DS18B20����*************
*���·�Χ��-55��+125����-10��+85�ȣ�����Ϊ0.5��
*�ֱ��ʣ�9��12λ���ֱ��0.5��0.25��0.125��0.0625��
*
************************/

char DS18B20_Reset()//DS18B20��λ
{
    char flag;
    DS18B20_DQ=0;
    delay_1us(250);//��ʱ480-960us
    DS18B20_DQ=1;
    delay_1us(25);//��ʱ15-60us
    flag=DS18B20_DQ;
    delay_1us(200);//��ʱ400us
    return flag;
}


void DS18B20_WriteData(unsigned char dat)//��DS18B20д����
{
    unsigned char i;
    for(i=0;i<8;i++)
    {
        DS18B20_DQ=0;
        delay_1us(4);//��ʱ4us
        DS18B20_DQ=dat&0x01;//ȡ���λ
        delay_1us(25);//��ʱ60us
        DS18B20_DQ=1;//�ͷ�����
        dat=dat>>1;
    }
}

unsigned char DS18B20_ReadData()//��DS18B20������
{
    unsigned char i,dat;
    for(i=0;i<8;i++)
    {
        dat>>=1;
        DS18B20_DQ=0;
        delay_1us(4);//��ʱ4us
        DS18B20_DQ=1;
        delay_1us(6);//��ʱ6us
        if(DS18B20_DQ==1)
        {
            dat=dat|0x80;
        }
        delay_1us(50);//��ʱ60us       
        DS18B20_DQ=1;//�ͷ�����
    }
    return dat;
}


float DS18B20_Tem()//DS18B20�����¶�ֵ����
{
    unsigned int DataH;
    unsigned char DataL;
    float Temp;

    DS18B20_Reset();//DS18B20��λ
    DS18B20_WriteData(0xcc);//��DS18B20д����(����ROM�¶ȼ��)
    DS18B20_WriteData(0x44);//��DS18B20д����(�����¶�ת��)
    
    DS18B20_Reset();//DS18B20��λ
    DS18B20_WriteData(0xcc);//��DS18B20д����(����ROM�¶ȼ��)
    DS18B20_WriteData(0xBE);//��DS18B20д����(���ݴ�������)
    DataL=DS18B20_ReadData();//��DS18B20������(���Ͱ�λ)
    DataH=DS18B20_ReadData();//��DS18B20������(���߰�λ)
    DataH=(DataH<<8) | DataL;//���
    if((DataH & 0xF800) == 0xF800)//�¶�Ϊ���¶�,��ȡ��Ȼ���1
    {
        DataH = ~DataH+1;
    }
    Temp=DataH * 0.0625;
    return Temp;
}
