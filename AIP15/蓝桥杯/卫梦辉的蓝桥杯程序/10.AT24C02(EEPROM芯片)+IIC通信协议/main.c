#include <STC15F2K60S2.h>
#include <intrins.h>
#include "smg.h"//����ܺ���ͷ�ļ�
#include "iic.h"
#include "EEPROM.h"


void main()
{
	unsigned char temp1,temp2; 
	Write_EEPROM(0x00,001);//���ַ0x00д��255��
	Write_EEPROM(0x01,159);//���ַ0x01д��234��

	temp1 = Read_EEPROM(0x00);//������ַ0x00������
	temp2 = Read_EEPROM(0x01);//������ַ0x01������

	while(1)
	{
		Display_4_WEI(1,temp1);	
		Display_4_WEI(5,temp2);	
	}
}
