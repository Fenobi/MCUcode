#include "LED_light.h"

void delay_nms(u16 n)
{
	while(n--)
	{
		unsigned char a,b,c;
		for(c=1;c>0;c--)
			for(b=142;b>0;b--)
				for(a=2;a>0;a--);	
	}
}

u8 key_scan(u8 mode)
{
	static u8 key=1;
	if(mode)
		key=1;
	if(key==1 && (KEY1==0 || KEY2==0 || KEY3==0 || KEY4==0))
	{
		delay_nms(10);//Ïû¶¶
		key=0;
		if(KEY1==0)
			return KEY1_PRESS;
		else if(KEY2==0)
			return KEY2_PRESS;
		else if(KEY3==0)
			return KEY3_PRESS;
		else if(KEY4==0)
			return KEY4_PRESS;
	}
	else if(KEY1==1 && KEY2==1 && KEY3==1 && KEY4==1)
	{
		key=1;
	}
	return KEY_UNPRESS;
}