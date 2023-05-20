
/**********************************************************************************

DS1302�����Ĵ�����������

  �Ĵ���    |      ������       |              |          ��λ����                |
   ����     | д����  |  ������ |   ȡֵ��Χ   |    7    |  6  5  4  | 3  2  1  0 |
 ��Ĵ���   |  80H    |   81H   |    00~59     |    CH   |  10SEC    |    SEC     |
						|					|					|							 |				 |					 |						|
 �ּĴ���   |  82H    |   83H   |    00~59     |    0    |  10MIN    |    MIN     |
 						|					|					|							 |				 |					 |						|
 ʱ�Ĵ���   |  84H    |   85H   | 01~12/00~23  |  12/24  |  10HOUR   |    HOUR    |
 						|					|					|							 |				 |					 |						|
 �ռĴ���   |  86H    |   87H   |01~28.29.30.31|    0    |  10DATE   |    DATE    |
 						|					|					|							 |				 |					 |						|
 �¼Ĵ���   |  88H    |   89H   |    01~12     |    0    |  0  0 10M |    MONTH   |
 						|					|					|							 |				 |					 |						|
 �ܼĴ���   |  8AH    |   8BH   |    01~07     |    0    |  0  0  0  | 0    DAY   |
 						|					|					|							 |				 |					 |						|
 ��Ĵ���   |  8CH    |   8DH   |    00~99     |      10  YEAR       |    YEAR    |


**********************************************************************************/

#include "DS1302.h"


/*===============================================================================*/

/**********DS1302ʵʱʱ�Ӷ�ȡ�ĵ�ַ**********/
uchar code READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; 
//                              ��    ��    ʱ    ��    ��    ��    ��

/**********DS1302ʵʱʱ��д��ĵ�ַ**********/
uchar code WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
//                              ��    ��    ʱ    ��    ��    ��    ��


/******���������ʱ�䣬�洢˳���� �� �� ʱ �� �� �� ��,�洢��ʽ����BCD��******/
uchar TIME[7] = {0x30, 0x11, 0x18, 0x19, 0x15, 0x05, 0x23};
//---DS1302ʱ�ӳ�ʼ��2023��5��19��������16��18��00�롣---//

/*===============================================================================*/




/**
  *@name   ������:Ds1302Write
  *@brief  ��DS1302д�������ַ+���ݣ�
  *@param  addr ��Ҫд��ĵ�ַ         
  *@param  dat  ��Ҫд�������
  *@retval ����ֵ���ޣ�
  */
void Ds1302Write(uchar addr, uchar dat)
{
	uchar n;
	RST = 0;
	_nop_();

	SCLK = 0;        		  //�Ƚ�SCLK�õ͵�ƽ��
	_nop_();
	RST = 1;          	  //Ȼ��RST(CE)�øߵ�ƽ��
	_nop_();

	for (n=0; n<8; n++)		//��ʼ���Ͱ�λ��ַ����
	{
		DSIO = addr & 0x01;	//���ݴӵ�λ��ʼ����
		addr >>= 1;
		SCLK = 1;						//������������ʱ��DS1302��ȡ����
		_nop_();
		SCLK = 0;
		_nop_();
	}
	for (n=0; n<8; n++)		//д��8λ����
	{
		DSIO = dat & 0x01;
		dat >>= 1;
		SCLK = 1;						//������������ʱ��DS1302��ȡ����
		_nop_();
		SCLK = 0;
		_nop_();	
	}	
		 
	RST = 0;							//�������ݽ���
	_nop_();
}





/**
  *@name   ������ : Ds1302Read
	*@brief  ��ȡһ����ַ������
	*@param  addr ��Ҫ��ȡ�ĵ�ַ
	*@retval ����ֵ dat ��ȡ��������
	*/
uchar Ds1302Read(uchar addr)
{
	uchar n,dat,dat1;
	RST = 0;
	_nop_();

	SCLK = 0;  						//�Ƚ�SCLK�õ͵�ƽ��
	_nop_();
	RST = 1;							//Ȼ��RST(CE)�øߵ�ƽ��
	_nop_();

	for(n=0; n<8; n++)		//��ʼ���Ͱ�λ��ַ����
	{
		DSIO = addr & 0x01;	//���ݴӵ�λ��ʼ����
		addr >>= 1;
		SCLK = 1;						//������������ʱ��DS1302��ȡ����
		_nop_();
		SCLK = 0;						//DS1302�½���ʱ����������
		_nop_();
	}
	_nop_();
	for(n=0; n<8; n++)		//��ȡ8λ����
	{
		dat1 = DSIO;				//�����λ��ʼ����
		dat = (dat>>1) | (dat1<<7);
		SCLK = 1;
		_nop_();
		SCLK = 0;						//DS1302�½���ʱ����������
		_nop_();
	}

	RST = 0;
	_nop_();							//����ΪDS1302��λ���ȶ�ʱ��,����ġ�
	SCLK = 1;
	_nop_();
	DSIO = 0;
	_nop_();
	DSIO = 1;
	_nop_();
	return dat;	
}



/**
	*@name   ������: Ds1302Init
	*@brief  DS1302��ʼ����
	*@retval ����ֵ���ޣ�
	*/
void Ds1302Init()
{
	uchar n;
	Ds1302Write(0x8E,0X00);		 //��ֹд���������ǹر�д��������
	for (n=0; n<7; n++)				 //д��7���ֽڵ�ʱ���źţ�����ʱ��������
		Ds1302Write(WRITE_RTC_ADDR[n],TIME[n]);	
	Ds1302Write(0x8E,0x80);		 //��д��������
}



/**
	*@name   ������: Ds1302ReadTime
	*@brief  ��ȡʱ����Ϣ��
	*@retval ����ֵ���ޣ�
	*/
void Ds1302ReadTime()
{
	uchar n;
	for (n=0; n<7; n++)					//��ȡ7���ֽڵ�ʱ���źţ��� �� ʱ �� �� �� �� 
		TIME[n] = Ds1302Read(READ_RTC_ADDR[n]);
}



/*============================================================================*/
/**
	*@name   ������: Ds1302_sec()
	*@brief  ��ȡʱ�ӵ���
	*@retval ����ֵ sec ��
	*/
uchar DS1302_sec()
{
	uchar sec_10 ,sec_1,sec;  	 //�ֱ�洢 ʮλ ��λ ��
	sec_10 = TIME[0]/16;       	 //ȡ��ʮλ
	sec_1 = TIME[0] & 0x0f;   	 //ȡ����λ
	
	sec = sec_10*10+sec_1;     	 //����
	return sec;
}  



/**
	*@name   ������: Ds1302_min()
	*@brief  ��ȡʱ�ӵķ�
	*@retval ����ֵ min ��
	*/
uchar DS1302_min()
{
	uchar min_10 ,min_1,min;   //�ֱ�洢 ʮλ ��λ ��
	min_10 = TIME[1]/16;       //ȡ��ʮλ
	min_1 = TIME[1] & 0x0f;    //ȡ����λ
	
	min = min_10*10+min_1;     //����
	return min;
}  



/**
	*@name   ������: Ds1302_hour()
	*@brief  ��ȡʱ�ӵ�ʱ
	*@retval ����ֵ hour ʱ.
	*/
uchar DS1302_hour()
{
	uchar hour_10 ,hour_1,hour;   //�ֱ�洢 ʮλ ��λ ʱ
	hour_10 = TIME[2]/16;       	//ȡ��ʮλ
	hour_1 = TIME[2] & 0x0f;    	//ȡ����λ
	
	hour = hour_10*10+hour_1;     //����
	return hour;
}  



/**
	*@name   ������: Ds1302_date()
	*@brief  ��ȡʱ�ӵ���
	*@retval ����ֵ date �ա�
	*/
uchar DS1302_date()
{
	uchar date_10 ,date_1,date;   //�ֱ�洢 ʮλ ��λ ��
	date_10 = TIME[3]/16;       	//ȡ��ʮλ
	date_1 = TIME[3] & 0x0f;    	//ȡ����λ
	
	date = date_10*10+date_1;     //����
	return date;
}  



/**
	*@name   ������: Ds1302_month()
	*@brief  ��ȡʱ�ӵ���
	*@retval ����ֵ month �¡�
	*/
uchar DS1302_month()
{
	uchar month_10 ,month_1,month;//�ֱ�洢 ʮλ ��λ ��
	month_10 = TIME[4]/16;       	//ȡ��ʮλ
	month_1 = TIME[4] & 0x0f;    	//ȡ����λ
	
	month = month_10*10+month_1;  //����
	return month;
}  



/**
	*@name   ������: Ds1302_week()
	*@brief  ��ȡʱ�ӵ���
	*@retval ����ֵ week �ܡ�
	*/
uchar *week_str[7] = {"Mon","Tue","Wed","Thu","Fir","Sat","Sun"};
uchar DS1302_week()
{
	uchar week_num;                   //
	week_num = TIME[5] & 0x07;
	
	return week_num;
}



/**
	*@name   ������: Ds1302_year()
	*@brief  ��ȡʱ�ӵ���
	*@retval ����ֵ year ��
	*/
uint DS1302_year()
{
	uchar year_10 ,year_1;  	 //�ֱ�洢 ʮλ ��λ 
	uint year;
	year_10 = TIME[6]/16;       	 //ȡ��ʮλ
	year_1  = TIME[6] & 0x0f;   	   //ȡ����λ
	
	year =2000+year_10*10+year_1; //����
	return year;
}  

/*============================================================================*/



