#include "lcd1602.h"
#include <stdio.h>
#include <STC15F2K60S2.H>

sbit LCD1602_RS=P1^0;
sbit LCD1602_RW=P1^1;
sbit LCD1602_E=P1^2;

#define LCD1602_DATAPINS P0  //数据

/*******************************************************************************
* 函 数 名         : Lcd1602_Delay1ms
* 函数功能		   : 延时函数，延时1ms
* 输    入         : c
* 输    出         : 无
* 说    名         : 该函数是在12MHZ晶振下，12分频单片机的延时。
*******************************************************************************/

void Lcd1602_Delay1ms(uint ms)   //误差 0us
{
	unsigned char i, j;
	while(ms--)
	{
		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} while (--i);
	}
}
void Lcd1602_Delay50us()		//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	_nop_();
	i = 147;
	while (--i);
}
/*******************************************************************************
* 函 数 名         : LcdWriteCom
* 函数功能		   : 向LCD写入一个字节的命令
* 输    入         : com
* 输    出         : 无
*******************************************************************************/
//#ifndef 	LCD1602_4PINS	 //当没有定义这个LCD1602_4PINS时
//void LcdWriteCom(uchar com)	  //写入命令
//{
//	LCD1602_E = 0;     //使能
//	LCD1602_RS = 0;	   //选择发送命令
//	LCD1602_RW = 0;	   //选择写入
//	
//	LCD1602_DATAPINS = com;     //放入命令
//	Lcd1602_Delay1ms(1);		//等待数据稳定

//	LCD1602_E = 1;	          //写入时序
//	Lcd1602_Delay1ms(5);	  //保持时间
//	LCD1602_E = 0;
//}
//#else 
void LcdWriteCom(uchar com)	  //写入命令
{
	LCD1602_E = 0;	 //使能清零
	LCD1602_RS = 0;	 //选择写入命令
	LCD1602_RW = 0;	 //选择写入

	LCD1602_DATAPINS = com;	//由于4位的接线是接到P0口的高四位，所以传送高四位不用改
//	Lcd1602_Delay1ms(1);
	Lcd1602_Delay50us();


	LCD1602_E = 1;	 //写入时序
//	Lcd1602_Delay1ms(5);
	Lcd1602_Delay50us();
	LCD1602_E = 0;

	LCD1602_DATAPINS = com << 4; //发送低四位
//	Lcd1602_Delay1ms(1);
	Lcd1602_Delay50us();

	LCD1602_E = 1;	 //写入时序
//	Lcd1602_Delay1ms(5);
	Lcd1602_Delay50us();
	LCD1602_E = 0;
}
//#endif
/*******************************************************************************
* 函 数 名         : LcdWriteData
* 函数功能		   : 向LCD写入一个字节的数据
* 输    入         : dat
* 输    出         : 无
*******************************************************************************/		   
//#ifndef 	LCD1602_4PINS		   
//void LcdWriteData(uchar dat)			//写入数据
//{
//	LCD1602_E = 0;	//使能清零
//	LCD1602_RS = 1;	//选择输入数据
//	LCD1602_RW = 0;	//选择写入

//	LCD1602_DATAPINS = dat; //写入数据
//	Lcd1602_Delay1ms(1);

//	LCD1602_E = 1;   //写入时序
//	Lcd1602_Delay1ms(5);   //保持时间
//	LCD1602_E = 0;
//}
//#else
void LcdWriteData(uchar dat)			//写入数据
{
	LCD1602_E = 0;	  //使能清零
	LCD1602_RS = 1;	  //选择写入数据
	LCD1602_RW = 0;	  //选择写入

	LCD1602_DATAPINS = dat;	//由于4位的接线是接到P0口的高四位，所以传送高四位不用改
//	Lcd1602_Delay1ms(1);
	Lcd1602_Delay50us();

	LCD1602_E = 1;	  //写入时序
//	Lcd1602_Delay1ms(5);
	Lcd1602_Delay50us();
	LCD1602_E = 0;

	LCD1602_DATAPINS = dat << 4; //写入低四位
//	Lcd1602_Delay1ms(1);
	Lcd1602_Delay50us();

	LCD1602_E = 1;	  //写入时序
//	Lcd1602_Delay1ms(5);
	Lcd1602_Delay50us();
	LCD1602_E = 0;
}
//#endif
/*******************************************************************************
* 函 数 名       : LcdInit()
* 函数功能		 : 初始化LCD屏
* 输    入       : 无
* 输    出       : 无
*******************************************************************************/		   
//#ifndef		LCD1602_4PINS
//void LcdInit()						  //LCD初始化子程序
//{
// 	LcdWriteCom(0x38);  //开显示
//	LcdWriteCom(0x0c);  //开显示不显示光标
//	LcdWriteCom(0x06);  //写一个指针加1
//	LcdWriteCom(0x01);  //清屏
//	LcdWriteCom(0x80);  //设置数据指针起点
//}
//#else
void LcdInit()						  //LCD初始化子程序
{
	LcdWriteCom(0x32);	 //将8位总线转为4位总线
	LcdWriteCom(0x28);	 //在四位线下的初始化
	LcdWriteCom(0x0c);  //开显示不显示光标
	LcdWriteCom(0x06);  //写一个指针加1
	LcdWriteCom(0x01);  //清屏
	LcdWriteCom(0x80);  //设置数据指针起点
}
//#endif

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


/**********************************************************
注意：lcd1602 显示屏显示范围一共 0~1共2行  0~15共16列
例：	Display_Num(5, 0, -552);//第5列第0行开始显示-552
************************************************************/
void Display_Num(uchar X, uchar Y, int num)//显整数函数 范围-32768~32767
{
	uchar num_txt[20];
	sprintf(num_txt,"%4d",num);
	DisplayListChar(X, Y, num_txt);
}

/**********************************************************
注意：lcd1602 显示屏显示范围一共 0~1共2行  0~15共16列
例：	Display_NumPoint(0, 1, -24.2);//第0列第1行开始显示-24.2
************************************************************/
void Display_NumPoint(uchar X, uchar Y, float decimal)//显小数函数 范围
{
	uchar decimal_txt[20];
	sprintf(decimal_txt,"%0.1f",decimal);//%0.xf  x是几，代表要显示小数点后几位，根据需求更改
	DisplayListChar(X, Y, decimal_txt);
}

void LCD1602_test(void)//LCD1602测试程序
{
	uchar lcd_1602_txt[20];
	int lcd_1602=543;
	
	LcdInit(); //LCD1602初始化
	while(1)
	{
		DisplayListChar(0, 0, " ABC");//从第0行第0列开始显示内容
		Display_Num(7, 0, -552);//显整数函数 范围-32768~32767
		Display_NumPoint(0, 1, -25.8);//显小数函数
		
		sprintf(lcd_1602_txt,"WMH:%d",lcd_1602);
		DisplayListChar(7,1,lcd_1602_txt);//显示字符串
		
		
		Lcd1602_Delay1ms(500);//500ms刷新一次显示
	}
}




