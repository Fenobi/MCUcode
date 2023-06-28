#include <STC32G.H>

typedef 	unsigned char	u8;
typedef 	unsigned int	u16;
typedef 	unsigned long	u32;

#define MAIN_Fosc        24000000UL

u8 ledIndex;
u8 code ledNum[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};


void  delay_ms(u8 ms)
{
     u16 i;
     do{
          i = MAIN_Fosc / 6000;
          while(--i);
     }while(--ms);
}

void main(void)
{
    u8 openIndex = 0;
    WTST = 0; 
    EAXFR = 1; 
    CKCON = 0; 

    P0M1 = 0x00;   P0M0 = 0x00;
    P1M0 = 0x00; P1M1 = 0x00; 

    while(1)
    {
        if(P11==0)
		{
			delay_ms(2);
			while(P11==0);
			delay_ms(2);
			
			P00=~P00;
		}
        

    }
}


