#include <REGX52.H>

typedef unsigned int u16;
typedef unsigned char u8;


#define KEY_MATRIX_PORT P1	
#define SMG_A_DP_PORT P0

u8 gamg_code[17] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f,
					0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};//共阴0-F


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

u8 key_matrix_ranks_scan(void)
{
	KEY_MATRIX_PORT=0xf7;
	if(KEY_MATRIX_PORT!=0xf7)
	{
		delay_nms(10);
	}
}


void main()
{
	
	while(1)
	{
		;
	}
}