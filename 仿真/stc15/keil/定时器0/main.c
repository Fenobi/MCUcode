#include "public.h"
#include "pwm.h"
#include "SRF04.h"

sbit L=P0^0;
sbit M=P0^1;
sbit R=P0^2;

unsigned char speed1=50;
unsigned char speed2=50;

uchar mode;
uchar start=0;
uchar back=0;
uchar mode1=1;

lmr_struct lmr;

uint dist;

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

//void LCD12864()
//{
// //智(0) 能(1) 配(2) 送(3) 小(4) 车(5) 年(6) 月(7) 日(8) 配(9) 送(10) 模(11) 式(12)
//    //1
//    oled_showchinese(0,0,0);//显示汉字,x y为坐标，no为编号	
//    oled_showchinese(16,0,1);
//    oled_showchinese(32,0,2);
//    oled_showchinese(48,0,3);	
//    oled_showchinese(64,0,4);	
//    oled_showchinese(80,0,5);
//    
//    //2
//    oled_shownum(0,2,year,4,16);//x,y:坐标,num数值,len位数,size2是字体，默认填16就行
//    oled_showchinese(32,2,6);
// 
//    oled_shownum(32+16,2,0,1,16);//x,y:坐标,num数值,len位数,size2是字体，默认填16就行
//    
//    oled_shownum(32+16+8,2,month,1,16);//x,y:坐标,num数值,len位数,size2是字体，默认填16就行
//    oled_showchinese(32+16+8+8,2,7);
//    
//    oled_shownum(32+16+8+8+16,2,day,2,16);//x,y:坐标,num数值,len位数,size2是字体，默认填16就行
//    oled_showchinese(32+16+8+8+16+16,2,8);
//    
//    //3
//    oled_shownum(0,4,hour,2,16);//x,y:坐标,num数值,len位数,size2是字体，默认填16就行
//    oled_showstring(16,4,":",16);//显示字符串
//    
//    oled_shownum(16+8,4,min,2,16);//x,y:坐标,num数值,len位数,size2是字体，默认填16就行
//    oled_showstring(16+16+8,4,":",16);//显示字符串
//    
//    oled_shownum(16+16+16,4,sec,2,16);//x,y:坐标,num数值,len位数,size2是字体，默认填16就行
//    
//    //4
//    oled_showchinese(0,6,9);//显示汉字,x y为坐标，no为编号	
//    oled_showchinese(16,6,10);
//    oled_showchinese(32,6,11);
//    oled_showchinese(48,6,12);	
//    oled_showstring(60,6,":",16);//显示字符串
//    oled_shownum(60+8,6,mode,2,16);//x,y:坐标,num数值,len位数,size2是字体，默认填16就行

//    LCD12864_delay_ms(100);
//}

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

//void read_time()
//{
//    sec= DS1302_sec();                           //读秒
//    min= DS1302_min();                           //读分
//    hour= DS1302_hour();													//读时
//    day= DS1302_date();													//读日
//    month= DS1302_month();                         //读月
//    year= DS1302_year();                           //读年
//}

void Timer1_Isr(void) interrupt 3
{
    lmr_ctrl(&lmr);
    if(P10==0)
        mode=1;
    if(P11==0)
        mode=2;
    if(P12==0)
        start=1;
    if(P13==0)
    {
        start=0;
        back=1;
    }
    if(dist<10)
    {
        start=0;
        P40=0;
    }
    else
    {
        P40=1;
    }
    //    lmr
    //    010->011->001  //左偏  右调011-> 010
    //    010->110->100  //右偏  左调
    //    000 脱轨
    if(start)
    {
        P41=0;
       // if(mode==1)
        {
            speed1=50;
            speed2=50;
            pwm2(speed1);
            pwm3(speed2);
            if(lmr.l==1)
            {
                pwm2(speed1+30);
                pwm3(speed1);
            }
            else if(lmr.r==1)
            {
                pwm2(speed1);
                pwm3(speed1+30);
            }
        }
    }
    else
    {
        speed1=0;
        speed2=0;
        P41=1;
    }

//    lmr_ctrl(&lmr);
//    if(L==0 && M==1 && R==1)
//    {
//        pwm2(5*speed1/4);
//        pwm4(0);
//        
//        pwm3(2*speed1/3);
//        pwm5(0);
//    }
//    else if(L==0 && M==0 && R==1)
//    {
//        pwm2(5*speed1/4);
//        pwm4(0);
//        
//        pwm3(0);
//        pwm5(speed1/5);
//    }
//    else if(L==1 && M==1 && R==0)
//    {
//        pwm2(5*speed1/4);
//        pwm4(0);
//        
//        pwm3(2*speed1/3);
//        pwm5(0);
//    }
//    else if(L==1 && M==0 && R==0)
//    {
//        pwm2(5*speed1/4);
//        pwm4(0);
//        
//        pwm3(0);
//        pwm5(speed1/5);
//    }
//    else
//    {
//        pwm2(speed1);
//        pwm4(0);
//        
//        pwm3(speed1);
//        pwm5(0);
//    }
}

void main()
{
    P1M0 = 0x00; P1M1 = 0x00; 
    P6M0 = 0x00; P6M1 = 0x00; 
 
	ET0 = 1;
	EA = 1;
	Timer0_Init();
    Timer1_Init();
    SRF04_Init();

      lmr_init(&lmr);
//    oled_init();//OLED初始化
//    Ds1302Init(); 
    pwminit();
    P37=0;
    P21=0;
    buzi();
    pwm2(0);
    pwm3(0);
    while (1)
    { 
        dist=Get_Distance();
        
    }
}

