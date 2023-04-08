#include <STC15F2K60S2.h>
#include <intrins.h>
#include "smg.h"//数码管函数头文件
#include "iic.h"
#include "EEPROM.h"


void main()
{
	unsigned char temp1,temp2; 
	Write_EEPROM(0x00,001);//向地址0x00写入255；
	Write_EEPROM(0x01,159);//向地址0x01写入234；

	temp1 = Read_EEPROM(0x00);//读出地址0x00的数据
	temp2 = Read_EEPROM(0x01);//读出地址0x01的数据

	while(1)
	{
		Display_4_WEI(1,temp1);	
		Display_4_WEI(5,temp2);	
	}
}
