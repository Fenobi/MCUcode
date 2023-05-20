#include "public.h"
#include "IIC_LCD12864.h"
#include "pwm.h"
#include "DS1302.h"

sbit L=P0^0;
sbit M=P0^1;
sbit R=P0^2;

int year;
int month;
int day;
int sec;
int min;
int hour;	

uchar mode;
uchar start=0;

lmr_struct lmr;

void lmr_init(lmr_struct *lmr)
{
    lmr->l = 0;
    lmr->l_old = 0;
    lmr->m = 0;
    lmr->m_old = 0;
    lmr->r = 0;
    lmr->r_old = 0;
}

void lmr_ctrl(lmr_struct *lmr)
{
    lmr->l_old = lmr->l;
    lmr->l = L;
    lmr->m_old = lmr->m;
    lmr->m = M;
    lmr->r_old = lmr->r;
    lmr->r = R;
    
}

void LCD12864()
{
 //智(0) 能(1) 配(2) 送(3) 小(4) 车(5) 年(6) 月(7) 日(8) 配(9) 送(10) 模(11) 式(12)
    //1
    oled_showchinese(0,0,0);//显示汉字,x y为坐标，no为编号	
    oled_showchinese(16,0,1);
    oled_showchinese(32,0,2);
    oled_showchinese(48,0,3);	
    oled_showchinese(64,0,4);	
    oled_showchinese(80,0,5);
    
    //2
    oled_shownum(0,2,year,4,16);//x,y:坐标,num数值,len位数,size2是字体，默认填16就行
    oled_showchinese(32,2,6);
 
    oled_shownum(32+16,2,0,1,16);//x,y:坐标,num数值,len位数,size2是字体，默认填16就行
    
    oled_shownum(32+16+8,2,month,1,16);//x,y:坐标,num数值,len位数,size2是字体，默认填16就行
    oled_showchinese(32+16+8+8,2,7);
    
    oled_shownum(32+16+8+8+16,2,day,2,16);//x,y:坐标,num数值,len位数,size2是字体，默认填16就行
    oled_showchinese(32+16+8+8+16+16,2,8);
    
    //3
    oled_shownum(0,4,hour,2,16);//x,y:坐标,num数值,len位数,size2是字体，默认填16就行
    oled_showstring(16,4,":",16);//显示字符串
    
    oled_shownum(16+8,4,min,2,16);//x,y:坐标,num数值,len位数,size2是字体，默认填16就行
    oled_showstring(16+16+8,4,":",16);//显示字符串
    
    oled_shownum(16+16+16,4,sec,2,16);//x,y:坐标,num数值,len位数,size2是字体，默认填16就行
    
    //4
    oled_showchinese(0,6,9);//显示汉字,x y为坐标，no为编号	
    oled_showchinese(16,6,10);
    oled_showchinese(32,6,11);
    oled_showchinese(48,6,12);	
    oled_showstring(60,6,":",16);//显示字符串
    oled_shownum(60+8,6,mode,2,16);//x,y:坐标,num数值,len位数,size2是字体，默认填16就行

    LCD12864_delay_ms(100);
}

void buzi()
{
    uchar n=3;
    while(n--)
    {
        P60=1;
        DelayNms(500);
        P60=0;
        DelayNms(500);
    }
    P60=1;
}

void read_time()
{
    sec= DS1302_sec();                           //读秒
    min= DS1302_min();                           //读分
    hour= DS1302_hour();													//读时
    day= DS1302_date();													//读日
    month= DS1302_month();                         //读月
    year= DS1302_year();                           //读年
}


void Timer1_Isr(void) interrupt 3
{
    ;
}

void tm0_isr() interrupt 1
{  
      
}

void main()
{
       P1M0 = 0x00; P1M1 = 0x07; 

    P6M0 = 0x00; P6M1 = 0x00; 

//	ET0 = 1;
//	EA = 1;
//	Timer0_Init();
////  Timer1_Init();
//   

// //   lmr_init(&lmr);
    oled_init();//OLED初始化
    Ds1302Init(); 
    while (1)
    { 
        if(P10==0)
            mode=1;
        if(P11==0)
            mode=2;
        if(P12==0)
            start=1; 
        Ds1302ReadTime();
        read_time();
        LCD12864();
    }
}

