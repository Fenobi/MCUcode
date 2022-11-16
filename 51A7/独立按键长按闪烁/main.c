#include "LED_light.h"

void main()
{
	u8 key=0;
	while(1)
	{
		key=key_scan(1);
		if(key==KEY1_PRESS)
		{
			LED1=~LED1;
		}
		if(key==KEY2_PRESS)
		{
			LED2=~LED2;
		}
		if(key==KEY3_PRESS)
		{
			LED3=~LED3;
		}
		if(key==KEY4_PRESS)
		{
			LED4=~LED4;
		}
	} 	
}