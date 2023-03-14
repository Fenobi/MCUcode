#include "ds18b20.h"
#include "smg.h"

void main()
{
	int temp_value=0;
	u8 temp_buf[5];
	u8 i=0;
	
	ds18b20_init();
	
	
	while(1)
	{	
		++i;
		if(i%50==0)
			temp_value=ds18b20_read_temperture()*10;
		
		if(temp_value<0)
		{
			temp_value=-temp_value;
			temp_buf[0]=0x40;
		}
		else
			temp_buf[0]=0x00;
		
		temp_buf[1]=gsmg_code[temp_value/1000];
		temp_buf[2]=gsmg_code[temp_value%1000/100];
		temp_buf[3]=gsmg_code[temp_value%1000%100/10]|0x80;
		temp_buf[4]=gsmg_code[temp_value%1000%100%10];
		smg_display(temp_buf,4);
	}
}
