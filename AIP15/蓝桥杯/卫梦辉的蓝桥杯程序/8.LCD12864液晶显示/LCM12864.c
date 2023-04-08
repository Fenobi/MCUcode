#include "LCM12864.h"
#include "delay.h"//延时函数头文件

sbit LCD12864_E =P1^2;//E管脚.......一定要把使用的管角初始化
sbit LCD12864_WR  =P2^1;//WR管脚
sbit LCD12864_RS  =P2^0;//RS管脚
sbit LCD12864_REST  =P2^6;//REST管脚(复位，默认接高) 

#define LCD12864_Data  P0//DB0--DB7数据管脚

void LCD_PIN()//对I/O口初始化
{
    P2M1 &= 0x00;	P2M0 &= 0x00;//设置P2为准双向口
    P0M1 &= 0x00;	P0M0 &= 0x00;//设置P1为准双向口
}

//*********************************************************

  //向12864中写入数据
void LCD12864_Write_Data(unsigned char dat)//向12864中写入数据
{
    LCD12864_E = 0;
    LCD12864_WR = 0;//选择写模式 
    LCD12864_RS = 1;//选择数据模式

    //延时
    delay_10us(1);
    //将数据准备
    LCD12864_Data = dat;
    delay_10us(1);
    LCD12864_E = 1;//表示开始写入数据,上升沿写入数据
    delay_10us(20); //延时等待数据全部发送完成
}

//向12864中写入命令
void LCD12864_Write_Com(unsigned char com)//向12864中写入命令
{
    //首先我们设置片选信号
    LCD12864_E = 0;//片选信号一般设置为0表示片选
    LCD12864_WR = 0;//选择写模式 
    LCD12864_RS = 0;//选择命令模式
    //延时
    delay_10us(1);
    //将数据准备
    LCD12864_Data = com;
    delay_10us(1);
    LCD12864_E = 1;//表示开始写入数据,上升沿写入数据
    delay_10us(20);
}

        
         //对LCD12864进行初始化
void LCD12864_Init()//对LCD12864进行初始化
{
    LCD_PIN();//对I/O口初始化
    //首先对LCD进行复位
    LCD12864_REST = 0;
    Delay_ms(30);
    LCD12864_REST = 1;
    Delay_ms(20);

    /* 开始初始化的步骤 */
    LCD12864_Write_Com(0x30);
    LCD12864_Write_Com(0x08);
    LCD12864_Write_Com(0x01);
    LCD12864_Write_Com(0x06);
    LCD12864_Write_Com(0x0c);
}

           /*  
        1.总共分为上下两个屏幕,其中第0->31行和第32->63行的行地址相同

        (上 0->31)第一个屏幕的首地址(0x80,0x80) -> ... -> (0x80,0x87)
                                   ....
                                  (0xa0,0x80) -> ... -> (0xa0,0x87)
        (下 32->63)第二个屏幕的首地址(0x80,0x88) -> ... -> (0x80,0x90)
                                    ...
                                 (0xa0,0x88) -> ... -> (0xa0,0x90)

        2.每个地址就是控制 一行16个小点,发送两次数据分别控制前8点和后8个点,
            例写入的01010101 01010101来控制屏幕的点 , 1显示 0不显示

        3.先写入行地址,后写入列地址,连续写列地址会自动增加
        */

//进行清屏操作 LCD12864_Clear_Screen(0xFF)全亮
//LCD12864_Clear_Screen(0xFF)全灭
void LCD12864_Clear_Screen(unsigned char value)
{
    unsigned char i,j;

    LCD12864_Write_Com(0x34);
    LCD12864_Write_Com(0x36);


    for(i=0;i<64;i++)
    {
        if(i<32)
        {
            LCD12864_Write_Com(0x80+i);
            LCD12864_Write_Com(0x80);
        }
        else 
        {
            LCD12864_Write_Com(0x80+(i-32));
            LCD12864_Write_Com(0x88);
        }

        for(j=0;j<16;j++)
        LCD12864_Write_Data(value);
    }
}
        
//显示非中文字符 和 中文字符都差不多,因为自带汉字库,只是注意写汉字的时候要连续写!
// 注意这里的坐标变了,一定要注意!!!
/*  
    实际坐标:
    0x80 -> 0x87
    0x90 -> 0x97
    0x88 -> 0x8f
    0x98 -> 0x9f
//这个坐标我们自己规定的,再换算成上面的实际坐标就可以了
    指出坐标(1,1) -> (1,8)
            (4,1) -> (4,8)
    再指出需要显示的字符
*/
unsigned char addresses[] = {0x80,0x90,0x88,0x98};
void LCD12864_Display_Char(unsigned char x,unsigned char y,unsigned char dat)
{
    LCD12864_Write_Com(0x30);
    LCD12864_Write_Com(0x06);

    //写入地址
    LCD12864_Write_Com(addresses[x-1]+(y-1));

    //写入数据
    LCD12864_Write_Data(dat);
}

//*******************************************显示汉字
void LCD12864_Display_Chars(unsigned char x,unsigned char y,unsigned char *dat)
{
    LCD12864_Write_Com(0x30);
    LCD12864_Write_Com(0x06);
    //写入地址
    LCD12864_Write_Com(addresses[x-1]+(y-1));
    //写入数据
    while(*dat != '\0')
    {
        LCD12864_Write_Data(*dat);
        dat++;
    }
}
//*******************************************显示整数变量值      
void LCD12864_ZS_display(unsigned char x,unsigned char y,unsigned int num)//显示变量值函数
{
    unsigned char str1[10];
	  sprintf(str1,"%d",num);//将变量转换成字符串,放在数组中。
    LCD12864_Display_Chars(x,y,str1);//将数组内容显示
}

//*******************************************显示指定位数小数变量值      
void LCD12864_XS_display(unsigned char x,unsigned char y,float num,unsigned char wei)//显示指定位数小数变量值 
{
  unsigned char str1[10];
	switch(wei)
	{
		case 0: sprintf(str1,"%0.0f",num);break;
		case 1: sprintf(str1,"%0.1f",num);break;
		case 2: sprintf(str1,"%0.2f",num);break;
		case 3: sprintf(str1,"%0.3f",num);break;
		case 4: sprintf(str1,"%0.4f",num);break;
		case 5: sprintf(str1,"%0.5f",num);break;
		case 6: sprintf(str1,"%0.6f",num);break;
	}
  LCD12864_Display_Chars(x,y,str1);//将数组内容显示
}

//*******************************************清除函数
//例:LCD12864_display(2,3,6) 指清除LCD屏第2行的第3~6格显示的字符
void LCD12864_Clearn(unsigned char hang,unsigned char x1,unsigned char x2)//显示变量值函数
{
	unsigned char i;
	for(i=x1;i<=x2;i++)
	{
			LCD12864_Display_Chars(hang,i,"  ");//将数组内容显示
	}
}


void LCD12864_Test()//LCD12864显示测试程序
{
    unsigned char *datas ="LCD 液晶显示";
    unsigned char str1[20];
    unsigned int a=1987;
    float b=1999.12;
    
    //液晶初始化
    LCD12864_Init();
    LCD12864_Clear_Screen(0x00); //清屏

    while(1)
    {
        sprintf(str1,"变量:%4d",a);//将变量转换成字符串,放在数组中。
        LCD12864_Display_Chars(1,1,str1);//将数组内容显示
        sprintf(str1,"变量:%0.2f",b);//将变量转换成字符串,放在数组中。
        LCD12864_Display_Chars(2,1,str1);//将数组内容显示
        LCD12864_Display_Char(3,2,'A');
        LCD12864_ZS_display(3,4,1235);//显示变量值函数
			  LCD12864_XS_display(4,1,36.2354,3);//显示变量值函数
    }

}

        
 