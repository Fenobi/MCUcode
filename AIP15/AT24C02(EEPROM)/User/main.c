#include <intrins.h>
#include "smg.h"
#include "iic.h"
#include "EEPROM.h"
#include "key.h"

#define EEPROM_ADDRESS1  0
#define EEPROM_ADDRESS2  1

void main()
{
	u8 key_temp=0;
	u8 save_value=0;
	
	u8 save_buf[3];
	//u8 temp1,temp2;
	//Write_EEPROM(EEPROM_ADDRESS1,000);//向地址0x00写入000；
	//Write_EEPROM(EEPROM_ADDRESS2,159);//向地址0x01写入159；

	//temp1 = Read_EEPROM(0x00);//读出地址0x00的数据
	//temp2 = Read_EEPROM(0x01);//读出地址0x01的数据
	
	
	while(1)
	{
		key_temp=key_scan(0);
		if(key_temp==KEY1_PRESS)
		{
			Write_EEPROM(EEPROM_ADDRESS1,save_value);
		}
		else if(key_temp==KEY2_PRESS)
		{
			save_value=Read_EEPROM(EEPROM_ADDRESS1);
		}
		else if(key_temp==KEY3_PRESS)
		{
			++save_value;
			
			if(save_value==255)
			{
				save_value=255;
			}
		}
		else if(key_temp==KEY4_PRESS)
		{
			save_value=0;
		}
		save_buf[0]=save_value/100;
		save_buf[1]=save_value%100/10;
		save_buf[2]=save_value%100%10;
		
		
		Display_1_WEI(6,save_buf[0]);
		Display_1_WEI(7,save_buf[1]);
		Display_1_WEI(8,save_buf[2]);
		//Display_4_WEI(6,save_value);
		//Display_4_WEI(6,save_value);
		//Display_4_WEI(1,temp1);
		//Display_4_WEI(5,temp2);
	}
}
