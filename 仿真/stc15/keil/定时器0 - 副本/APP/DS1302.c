
/**********************************************************************************

DS1302各个寄存器及命令字

  寄存器    |      命令字       |              |          各位内容                |
   名称     | 写操作  |  读操作 |   取值范围   |    7    |  6  5  4  | 3  2  1  0 |
 秒寄存器   |  80H    |   81H   |    00~59     |    CH   |  10SEC    |    SEC     |
						|					|					|							 |				 |					 |						|
 分寄存器   |  82H    |   83H   |    00~59     |    0    |  10MIN    |    MIN     |
 						|					|					|							 |				 |					 |						|
 时寄存器   |  84H    |   85H   | 01~12/00~23  |  12/24  |  10HOUR   |    HOUR    |
 						|					|					|							 |				 |					 |						|
 日寄存器   |  86H    |   87H   |01~28.29.30.31|    0    |  10DATE   |    DATE    |
 						|					|					|							 |				 |					 |						|
 月寄存器   |  88H    |   89H   |    01~12     |    0    |  0  0 10M |    MONTH   |
 						|					|					|							 |				 |					 |						|
 周寄存器   |  8AH    |   8BH   |    01~07     |    0    |  0  0  0  | 0    DAY   |
 						|					|					|							 |				 |					 |						|
 年寄存器   |  8CH    |   8DH   |    00~99     |      10  YEAR       |    YEAR    |


**********************************************************************************/

#include "DS1302.h"


/*===============================================================================*/

/**********DS1302实时时钟读取的地址**********/
uchar code READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; 
//                              秒    分    时    日    月    周    年

/**********DS1302实时时钟写入的地址**********/
uchar code WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
//                              秒    分    时    日    月    周    年


/******储存读出的时间，存储顺序是 秒 分 时 日 月 周 年,存储格式是用BCD码******/
uchar TIME[7] = {0x30, 0x11, 0x18, 0x19, 0x15, 0x05, 0x23};
//---DS1302时钟初始化2023年5月19日星期四16点18分00秒。---//

/*===============================================================================*/




/**
  *@name   函数名:Ds1302Write
  *@brief  向DS1302写入命令（地址+数据）
  *@param  addr 需要写入的地址         
  *@param  dat  需要写入的数据
  *@retval 返回值（无）
  */
void Ds1302Write(uchar addr, uchar dat)
{
	uchar n;
	RST = 0;
	_nop_();

	SCLK = 0;        		  //先将SCLK置低电平。
	_nop_();
	RST = 1;          	  //然后将RST(CE)置高电平。
	_nop_();

	for (n=0; n<8; n++)		//开始传送八位地址命令
	{
		DSIO = addr & 0x01;	//数据从低位开始传送
		addr >>= 1;
		SCLK = 1;						//数据在上升沿时，DS1302读取数据
		_nop_();
		SCLK = 0;
		_nop_();
	}
	for (n=0; n<8; n++)		//写入8位数据
	{
		DSIO = dat & 0x01;
		dat >>= 1;
		SCLK = 1;						//数据在上升沿时，DS1302读取数据
		_nop_();
		SCLK = 0;
		_nop_();	
	}	
		 
	RST = 0;							//传送数据结束
	_nop_();
}





/**
  *@name   函数名 : Ds1302Read
	*@brief  读取一个地址的数据
	*@param  addr 需要读取的地址
	*@retval 返回值 dat 读取到的数据
	*/
uchar Ds1302Read(uchar addr)
{
	uchar n,dat,dat1;
	RST = 0;
	_nop_();

	SCLK = 0;  						//先将SCLK置低电平。
	_nop_();
	RST = 1;							//然后将RST(CE)置高电平。
	_nop_();

	for(n=0; n<8; n++)		//开始传送八位地址命令
	{
		DSIO = addr & 0x01;	//数据从低位开始传送
		addr >>= 1;
		SCLK = 1;						//数据在上升沿时，DS1302读取数据
		_nop_();
		SCLK = 0;						//DS1302下降沿时，放置数据
		_nop_();
	}
	_nop_();
	for(n=0; n<8; n++)		//读取8位数据
	{
		dat1 = DSIO;				//从最低位开始接收
		dat = (dat>>1) | (dat1<<7);
		SCLK = 1;
		_nop_();
		SCLK = 0;						//DS1302下降沿时，放置数据
		_nop_();
	}

	RST = 0;
	_nop_();							//以下为DS1302复位的稳定时间,必须的。
	SCLK = 1;
	_nop_();
	DSIO = 0;
	_nop_();
	DSIO = 1;
	_nop_();
	return dat;	
}



/**
	*@name   函数名: Ds1302Init
	*@brief  DS1302初始化。
	*@retval 返回值（无）
	*/
void Ds1302Init()
{
	uchar n;
	Ds1302Write(0x8E,0X00);		 //禁止写保护，就是关闭写保护功能
	for (n=0; n<7; n++)				 //写入7个字节的时钟信号：分秒时日月周年
		Ds1302Write(WRITE_RTC_ADDR[n],TIME[n]);	
	Ds1302Write(0x8E,0x80);		 //打开写保护功能
}



/**
	*@name   函数名: Ds1302ReadTime
	*@brief  读取时钟信息。
	*@retval 返回值（无）
	*/
void Ds1302ReadTime()
{
	uchar n;
	for (n=0; n<7; n++)					//读取7个字节的时钟信号：秒 分 时 日 月 周 年 
		TIME[n] = Ds1302Read(READ_RTC_ADDR[n]);
}



/*============================================================================*/
/**
	*@name   函数名: Ds1302_sec()
	*@brief  读取时钟的秒
	*@retval 返回值 sec 秒
	*/
uchar DS1302_sec()
{
	uchar sec_10 ,sec_1,sec;  	 //分别存储 十位 个位 秒
	sec_10 = TIME[0]/16;       	 //取出十位
	sec_1 = TIME[0] & 0x0f;   	 //取出个位
	
	sec = sec_10*10+sec_1;     	 //整合
	return sec;
}  



/**
	*@name   函数名: Ds1302_min()
	*@brief  读取时钟的分
	*@retval 返回值 min 分
	*/
uchar DS1302_min()
{
	uchar min_10 ,min_1,min;   //分别存储 十位 个位 分
	min_10 = TIME[1]/16;       //取出十位
	min_1 = TIME[1] & 0x0f;    //取出个位
	
	min = min_10*10+min_1;     //整合
	return min;
}  



/**
	*@name   函数名: Ds1302_hour()
	*@brief  读取时钟的时
	*@retval 返回值 hour 时.
	*/
uchar DS1302_hour()
{
	uchar hour_10 ,hour_1,hour;   //分别存储 十位 个位 时
	hour_10 = TIME[2]/16;       	//取出十位
	hour_1 = TIME[2] & 0x0f;    	//取出个位
	
	hour = hour_10*10+hour_1;     //整合
	return hour;
}  



/**
	*@name   函数名: Ds1302_date()
	*@brief  读取时钟的日
	*@retval 返回值 date 日。
	*/
uchar DS1302_date()
{
	uchar date_10 ,date_1,date;   //分别存储 十位 个位 日
	date_10 = TIME[3]/16;       	//取出十位
	date_1 = TIME[3] & 0x0f;    	//取出个位
	
	date = date_10*10+date_1;     //整合
	return date;
}  



/**
	*@name   函数名: Ds1302_month()
	*@brief  读取时钟的月
	*@retval 返回值 month 月。
	*/
uchar DS1302_month()
{
	uchar month_10 ,month_1,month;//分别存储 十位 个位 月
	month_10 = TIME[4]/16;       	//取出十位
	month_1 = TIME[4] & 0x0f;    	//取出个位
	
	month = month_10*10+month_1;  //整合
	return month;
}  



/**
	*@name   函数名: Ds1302_week()
	*@brief  读取时钟的周
	*@retval 返回值 week 周。
	*/
uchar *week_str[7] = {"Mon","Tue","Wed","Thu","Fir","Sat","Sun"};
uchar DS1302_week()
{
	uchar week_num;                   //
	week_num = TIME[5] & 0x07;
	
	return week_num;
}



/**
	*@name   函数名: Ds1302_year()
	*@brief  读取时钟的年
	*@retval 返回值 year 年
	*/
uint DS1302_year()
{
	uchar year_10 ,year_1;  	 //分别存储 十位 个位 
	uint year;
	year_10 = TIME[6]/16;       	 //取出十位
	year_1  = TIME[6] & 0x0f;   	   //取出个位
	
	year =2000+year_10*10+year_1; //整合
	return year;
}  

/*============================================================================*/



