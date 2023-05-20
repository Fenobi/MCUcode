#include <REGX52.H>

void Delay1ms(void)
{
	unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}

void DelayNms(unsigned int n)
{
    while(n--)
    {
        Delay1ms();
    }
}

void smg_display(u8 pos)
{
	u8 i=0;
    
	for(i=pos;i<8;i++)
	{
	   	switch(7-i)
		{
			case 0: LSC=1;LSB=1;LSA=1;break;
			case 1: LSC=1;LSB=1;LSA=0;break;
			case 2: LSC=1;LSB=0;LSA=1;break;
			case 3: LSC=1;LSB=0;LSA=0;break;
			case 4: LSC=0;LSB=1;LSA=1;break;
			case 5: LSC=0;LSB=1;LSA=0;break;
			case 6: LSC=0;LSB=0;LSA=1;break;
			case 7: LSC=0;LSB=0;LSA=0;break;
		}
		SMG_A_DP_PORT=dat[i-pos_temp];//���Ͷ�ѡ����
		delay_10us(100);//��ʱһ��ʱ�䣬�ȴ���ʾ�ȶ�
		SMG_A_DP_PORT=0x00;//����
	}
}

void main()
{
    while(1)
    {
        char i=0;
        for(i=0;i<8;++i)
        {
            P1=0x01<<i;
            DelayNms(500);
//            P1=0;
//            DelayNms(500);
        }
    }
    
}