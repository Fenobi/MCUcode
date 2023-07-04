#include "ADC.h"

void ADC_Init()
{
    P1M0 = 0x00; P1M1 = 0x03; //P10、P11高阻态
    
    P_SW2 |= 0x80;
    ADCTIM = 0x3f;					//设置 ADC 内部时序，ADC采样时间设最大值
    P_SW2 &= 0x7f;
    ADCCFG = 0x2f;					//设置 ADC 时钟为系统时钟/2/16/16，转化结果右对齐
    ADC_CONTR = 0x80; 			    //使能 ADC 模块

}

u16 ADC_Read(u8 ADC_Channel_x)//x为0~1
{  
    ADC_RES = 0;
    ADC_RESL = 0;

	ADC_CONTR = (ADC_CONTR & 0xF0) | 0x40 | ADC_Channel_x;//启动 AD 转换
	_nop_();
    _nop_();
    _nop_();
    _nop_();

    while((ADC_CONTR & 0x20) == 0);          //等待ADC完成
    ADC_CONTR &= ~0x20;     		         //清除ADC结束标志
    return  (((u16)ADC_RES << 8) | ADC_RESL);//默认是12位
}

float ADC_Vol(u16 vol)
{
    return ADC_Vref * vol / 4096;
}