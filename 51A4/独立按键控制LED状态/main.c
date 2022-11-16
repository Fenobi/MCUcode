#include <REGX51.H>

void delayX10us(unsigned int xms) 
{
	while(xms)
	{
		unsigned char a,b;
		for(b=1;b>0;b--)
			for(a=2;a>0;a--);
		xms--;
	}
}


int main()
{
	while(1)
	{
		if(P3_1==0)
		{
			delayX10us(2);
			while(P3_1==0);
			delayX10us(2);
			
			P2_0=~P2_0;
		}
	}	
	return 0;
}