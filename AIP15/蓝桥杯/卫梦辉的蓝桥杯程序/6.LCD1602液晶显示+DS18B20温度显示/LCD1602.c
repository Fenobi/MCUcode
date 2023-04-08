#include "lcd1602.h"
#include <stdio.h>

/*******************************************************************************
* 函 数 名         : Lcd1602_Delay1ms
* 函数功能		   : 延时函数，延时1ms
* 输    入         : c
* 输    出         : 无
* 说    名         : 该函数是在12MHZ晶振下，12分频单片机的延时。
*******************************************************************************/
void Lcd1602_Delay1ms(uint c)   //误差 0us
{
  uchar a,b;
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	}   	
}

/*******************************************************************************
* 函 数 名         : LcdWriteCom
* 函数功能		   : 向LCD写入一个字节的命令
* 输    入         : com
* 输    出         : 无
*******************************************************************************/
void LcdWriteCom(uchar com)	  //写入命令
{
	LCD1602_E = 0;     //使能
	LCD1602_RS = 0;	   //选择发送命令
	LCD1602_RW = 0;	   //选择写入
	
	LCD1602_DATAPINS = com;     //放入命令
	Lcd1602_Delay1ms(1);		//等待数据稳定

	LCD1602_E = 1;	          //写入时序
	Lcd1602_Delay1ms(5);	  //保持时间
	LCD1602_E = 0;
}
/*******************************************************************************
* 函 数 名         : LcdWriteData
* 函数功能		   : 向LCD写入一个字节的数据
* 输    入         : dat
* 输    出         : 无
*******************************************************************************/		      
void LcdWriteData(uchar dat)			//写入数据
{
	LCD1602_E = 0;	//使能清零
	LCD1602_RS = 1;	//选择输入数据
	LCD1602_RW = 0;	//选择写入

	LCD1602_DATAPINS = dat; //写入数据
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;   //写入时序
	Lcd1602_Delay1ms(5);   //保持时间
	LCD1602_E = 0;
}

/*******************************************************************************
* 函 数 名       : LcdInit()
* 函数功能		 : 初始化LCD屏
* 输    入       : 无
* 输    出       : 无
*******************************************************************************/		   
void LcdInit()						  //LCD初始化子程序
{
 	LcdWriteCom(0x38);  //开显示
	LcdWriteCom(0x0c);  //开显示不显示光标
	LcdWriteCom(0x06);  //写一个指针加1
	LcdWriteCom(0x01);  //清屏
	LcdWriteCom(0x80);  //设置数据指针起点
}
/**************************************
功能描述：LCD1602按指定位置显示一个字符
入口参数：uint8 X, uint8 Y, uint8 DData
返回值：无
***************************************/
void DisplayOneChar(uchar X, uchar Y, uchar DData)
{
	Y &= 0x1;
	X &= 0xF; //限制X不能大于15，Y不能大于1
	if (Y) X |= 0x40; //当要显示第二行时地址码+0x40;
	X |= 0x80; //算出指令码
	LcdWriteCom(X); //发命令字
	LcdWriteData(DData); //发数据
}

/**************************************
功能描述：LCD1602按指定位置显示一串字符
入口参数：uint8 X, uint8 Y, uint8 DData  X代表第X+1列，Y代表第Y+1行
返回值：无
***************************************/
void DisplayListChar(uchar X, uchar Y, uchar *DData)
{
	uchar ListLength;

  ListLength = 0;
	Y &= 0x1;
	X &= 0xF; //限制X不能大于15，Y不能大于1
	while (DData[ListLength]>0x19) //若到达字串尾则退出
		{
			if (X <= 0xF)        //X坐标应小于0xF
				{
					DisplayOneChar(X, Y, DData[ListLength]); //显示单个字符
					ListLength++;
					X++;
				}
		}
}


uchar txt[20];
void Display_XS(uchar X, uchar Y,float XS,uchar XS_wei)//显示指定小数。
{
	switch(XS_wei)
	{
		case 0: sprintf(txt,"%0.0f",XS); break;
		case 1: sprintf(txt,"%0.1f",XS); break;
		case 2: sprintf(txt,"%0.2f",XS); break;
		case 3: sprintf(txt,"%0.3f",XS); break;
	}
	DisplayListChar(X, Y,txt);//显示小数变量数值****4	
}

uint lcd_1602=9845;
float XS=23.48;
uchar code Disp1[]={"0123456789"};

void LCD1602_test(void)//LCD1602测试程序
{
	LcdInit(); //LCD1602初始化
	
	while(1)
	{
		DisplayListChar(0, 0, "WMH");     //从第一行第0列开始显示内容****1
		DisplayListChar(6, 0, Disp1);  //显示字符数组内容****2
		
		lcd_1602=41;	
		sprintf(txt,"num:%d",lcd_1602);
		DisplayListChar(0,1,txt);//显示整数变量数值****3
		
		sprintf(txt,"xs:%0.2f",XS);
		DisplayListChar(8,1,txt);//显示小数变量数值****4
	}
}



////		LcdWriteCom(0x01);//清屏



