//#include <REGX52.H>

//void Delay1ms(void)
//{
//	unsigned char i, j;

//	i = 2;
//	j = 239;
//	do
//	{
//		while (--j);
//	} while (--i);
//}

//void DelayNms(unsigned int n)
//{
//    while(n--)
//    {
//        Delay1ms();
//    }
//}

//void smg_display(u8 pos)
//{
//	u8 i=0;
//    
//	for(i=pos;i<8;i++)
//	{
//	   	switch(7-i)
//		{
//			case 0: LSC=1;LSB=1;LSA=1;break;
//			case 1: LSC=1;LSB=1;LSA=0;break;
//			case 2: LSC=1;LSB=0;LSA=1;break;
//			case 3: LSC=1;LSB=0;LSA=0;break;
//			case 4: LSC=0;LSB=1;LSA=1;break;
//			case 5: LSC=0;LSB=1;LSA=0;break;
//			case 6: LSC=0;LSB=0;LSA=1;break;
//			case 7: LSC=0;LSB=0;LSA=0;break;
//		}
//		SMG_A_DP_PORT=dat[i-pos_temp];//传送段选数据
//		delay_10us(100);//延时一段时间，等待显示稳定
//		SMG_A_DP_PORT=0x00;//消音
//	}
//}

//void main()
//{
//    while(1)
//    {
//        char i=0;
//        for(i=0;i<8;++i)
//        {
//            P1=0x01<<i;
//            DelayNms(500);
////            P1=0;
////            DelayNms(500);
//        }
//    }
//    
//}


#include <REGX52.H>

typedef unsigned char u8;
typedef unsigned int u16;

#define SMG P2

#define KEY_ANJI P1


//u8 a[]={0x03,0x9f,0x25,0x0d,0x99,0x49,0x41,0x1f,0x01,0x09,0x77,0x7c,0x39,0x5e,0x79,0x71};//共阳0—F显示的值
u8 a[17] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f,
0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};//共阴0-F

void delay_N10us(int b)          //_10us 为注释delay，可以去掉。//
{
   while(b--);		
}

u8 key_scan(void)
{
	u8 key=0;
	
	KEY_ANJI=0xf7;//第一列为低电平
	if(KEY_ANJI!=0xf7)
	{
        delay_N10us(1000); 
//        if(KEY_ANJI==0x77 || KEY_ANJI==0xb7 || KEY_ANJI==0xd7 || KEY_ANJI==0xe7)
//        {
//            if(KEY_ANJI==0x77)
//                key=1;
//            else if(KEY_ANJI==0xb7)
//                key=5;
//            else if(KEY_ANJI==0xd7)
//                key=9;
//            else if(KEY_ANJI==0xe7)
//                key=13;
//        }
        switch(KEY_ANJI)
        {
            case 0x77:
                key=1;break;
            case 0xb7:
                key=5;break;
            case 0xd7:
                key=9;break;
            case 0xe7:
                key=13;break;
        }		
        
        while(KEY_ANJI!=0xf7);//等待按键松开
	}

	KEY_ANJI=0xfb;//第二列为低电平
	if(KEY_ANJI==0xfb)
	{
		
        delay_N10us(1000);
            
        switch(KEY_ANJI)
		{
		case 0x7b:key=2;break;
		case 0xbb:key=6;break;
		case 0xdb:key=10;break;
		case 0xeb:key=14;break;
		}		
		while(KEY_ANJI!=0xfb);
	}
    
    KEY_ANJI=0xfd;//第三列为低电平
	if(KEY_ANJI==0xfd)
	{
		
        delay_N10us(1000);
            
        switch(KEY_ANJI)
		{
		case 0x7d:key=3;break;
		case 0xbd:key=7;break;
		case 0xdd:key=11;break;
		case 0xed:key=15;break;
		}
        
        while(KEY_ANJI!=0xfd);
	}	
		
    
	KEY_ANJI=0xfe;//第四列为低电平
	if(KEY_ANJI==0xfe)
	{
		
        delay_N10us(1000);
		
        switch(KEY_ANJI)
        {
		case 0x7e:key=4;break;
		case 0xbe:key=8;break;
		case 0xde:key=12;break;
		case 0xee:key=16;break;
		}		
		while(KEY_ANJI!=0xfe);
	}
	return key;
}

  void main()
{
  u8 key =0;
	
	while(1)
	{
        key=key_scan();
        if(key>0)
        {
            //P0=a[key];
            SMG=a[key];
        }		
	
	
	}
	
}
