#include "12864_st7920c.h"

//========================================================
sbit RES=P0^4; //RST��λ,����

sbit CS =P0^2; //RS ����/ָ��
sbit SID=P0^1; //RW ����
sbit SCK=P0^0; //E  ʱ��

unsigned char code bmp1[];
//========================================================

unsigned char code tab1[]={
"��ӭѡ�����ǲ�Ʒ"
"�޹�˾Һ����ʾģ"     
"����\xfd˹��ŵ�Ƽ���"      
"�����ST7920����"     
};      

unsigned char code tab2[]={
"128X64ȫ������ʾ"      //��һ�к�������
"����ʾ8Xz4������"      //�ڶ��к�������
"�ڴ���׼�����ֿ�"      //�����к�������
"��8192����������"      //�����к�������
};      


//========================================================

void LCD12864_Init()//LCD12864��ʼ������
{
    	DelayMs(10);			//Delay50mS
    	RES=0;
    	DelayMs(10);
    	RES=1;
    	DelayMs(10);
    	write_com(0x30);		//FUNCTION SET 001,DL,N,DH,IS2,IS1
    	DelayMs(10);
    	write_com(0x30);		//FUNCTION SET 001,DL,N,DH,IS2,IS1
    	DelayMs(10);
    	write_com(0x30);		//FUNCTION SET 001,DL,N,DH,IS2,IS1
    	DelayMs(10);
    	write_com(0x03);		//ENTRY MODE SET
    	DelayMs(10);
    	write_com(0x01);		//RETURN HOME
    	DelayMs(10);
    	write_com(0x06);		//////////////////////////
    	DelayMs(10);/////////////////////////////////
    	write_com(0x0c);		//DISPLAY ON ,00001DCB ,D=1:Display on; 0:off
    	DelayMs(10);
	
	
}
//========================================================
unsigned char ReceiveByte(void)
{
	 unsigned char i,temp1,temp2;
	 temp1=temp2=0;
	 for(i=0;i<8;i++)
	 {
		 temp1=temp1<<1;
		 SCK = 0;
		 SCK = 1;                
		 SCK = 0;
		 if(SID) temp1++;
	 }
	 for(i=0;i<8;i++)
	 {
		 temp2=temp2<<1;
		 SCK = 0;
		 SCK = 1;
		 SCK = 0;
		 if(SID) temp2++;
	 }
	 return ((0xf0&temp1)+(0x0f&temp2));
}
 
//========================================================

void SendByte(unsigned char Dbyte)
{
		unsigned char i;
		for(i=0;i<8;i++)
		{
			 SCK = 0;
			 Dbyte=Dbyte<<1;
			 SID = CY;
			 SCK = 1;
			 SCK = 0;
		}
}
//========================================================
void LcmClearBMP( void )
{
		unsigned char i,j;
		write_com(0x34);
		write_com(0x36);
		for(i=0;i<32;i++) //<32
		{
			write_com(0x80|i);
			write_com(0x80);
			for(j=0;j<32;j++) //<32
			write_data(0);
		}
}
//========================================================
void PutBMP(unsigned char *puts)
{
	 unsigned int x=0;
	 unsigned char i,j;
	 write_com(0x34);
	 write_com(0x36);
	 for(i=0;i<32;i++)  //<32
	 {
		 write_com(0x80|i);
		 write_com(0x80); 
		 for(j=0;j<32;j++)    //<32
		 {                     
						 write_data(puts[x]);
						 x++;
		 }
	 }

}
//========================================================
void LcmClearTXT( void )
{
	unsigned char i;
	write_com(0x30);
	write_com(0x80);
	for(i=0;i<64;i++)
	write_data(0x20);
}

//========================================================
void font1()
{
	int i,j;
  write_com(0x80);  		//
	delay(1);
	for(i=0X30;i<0X50;i++)
	{
	   write_data(i);
		delay(1);
	}
	write_com(0x90);
	delay(1);
	for(j=0x50;j<0x70;j++)
	{
	  write_data(j);
		delay(1);
	}
}
//========================================================
void font2(int h,int l)
{
	int i,j;
    write_com(0x80);  		//
	delay(1);
	for(i=0;i<16;i++)
	{
	    write_data(h);
		delay(1);
	    write_data(l++);
		delay(1);
	}
//	++h;
	write_com(0x90);
	delay(1);
	for(j=0;j<16;j++)
	{
	    write_data(h);
		delay(1);
	    write_data(l++);
		delay(1);
	}
}
//========================================================

//========================================================
void wr_gdram_H()	
{
 	int i,j,k;
 	//i=0X80;				//
 	k=0Xff;
	write_com(0x34);		//Set GDRAM
	delay(10);
	write_com(0x36);		//Set GDRAM
	delay(10);

	for(j=0;j<64;j++)	
	{
		for(i=0X80;i<0X90;i++)		//
		{
			write_com(0X80+j);		//Set vertical address (Y) for GDRAM
			delay(1);
			write_com(i);			//
			delay(1);
			write_data(k);			//Write D15~D8 to GDRAM (first byte)
			write_data(k);			//Write D7~D0 to GDRAM (second byte)
		}
		k=~k;
	}	
	write_com(0x34);
	delay(1);
	write_com(0x30);
	delay(1);
}
//========================================================

/******************************************************************************************
*�������ƣ� lat_disp
*���������� ��ʾ����
******************************************************************************************/
void wr_gdram(int k, int h)//��ʾ���㺯��
{
    int i,j;
//	write_com(0x34);		//Set GDRAM
//	delay(1);//1
//	write_com(0x36);		//Set GDRAM
//	delay(1);//1
	for(j=0;j<64;j++)	//<64
   {
	write_com(0X80|j);		//Set vertical address (Y) for GDRAM
//	delay(10);
	write_com(0x80);			//
//	delay(10);
 	for(i=0;i<16;i++)		//
   {
	write_data(k);
//	delay(10);			//Write D15~D8 to GDRAM (first byte)
	write_data(h);
//	delay(10);			//Write D7~D0 to GDRAM (second byte)
   }
   }	
  	write_com(0x34);
 	delay(1);//1

	write_com(0x36);
	delay(1);//1
}


/******************************************************************************************
*�������ƣ� lat_disp
*���������� ��ʾ����
******************************************************************************************/
void lat_disp(unsigned char data1,unsigned char data2)
{
 unsigned char i,j;
	for(j=0;j<16;j++)
	{
		for(i=0;i<16;i++)
		{
			write_com(0x34);
			write_com(0x80+j*2);
			write_com(0x80+i);
			write_com(0x30);
			write_data(data1);
			write_data(data1);
		}
		for(i=0;i<16;i++)
		{
			write_com(0x34);
			write_com(0x80+j*2+1);
			write_com(0x80+i);
			write_com(0x30);
			write_data(data2);
			write_data(data2);
		}
	}
	write_com(0x36);
	DelayMs(1700);
	write_com(0x34);   //ͼ��ģʽ��
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
void wr_gdram_W()	
{
 	int i,j,k;
 	//i=0X80;				//
 	k=0X55;
	write_com(0x34);		//Set GDRAM
	delay(1);
	write_com(0x36);		//Set GDRAM
	delay(1);

	for(j=0;j<64;j++)	
   {
	for(i=0X80;i<0X90;i++)		//
   {
	write_com(0X80+j);		//Set vertical address (Y) for GDRAM
	delay(1);
	write_com(i);			//
	delay(1);
	write_data(k);			//Write D15~D8 to GDRAM (first byte)
	write_data(k);			//Write D7~D0 to GDRAM (second byte)
   }
   	k=~k;
   }	
 write_com(0x36);
 DelayMs(1600);
 write_com(0x34);   //ͼ��ģʽ��

}



void cn_disp(unsigned char code *cn)//��ʾ���ֺ���
{
	unsigned char i,j;
	write_com(0x30);
	write_com(0x80);
	for(j=0;j<4;j++)
	{
		for(i=0;i<16;i++)
		write_data(cn[j*16+i]);
	}
	DelayNus(200);//200
}

 /***************************************************************************
 * ��  �� : LCD12864Һ��������ʾ�ӳ��� 
 * ��  �� : uint8 y ��,uint8 x ��,uint8 i ���ݴ�С,uint8 *z ��ʾ����
 * ����ֵ : ��
 **************************************************************************/
/*
��һ�� 80H
�ڶ��� 90H
������ 88H
������ 98H
*/ 
void HZ_disp( unsigned char hang,unsigned char lie, unsigned char code cn[])//��ʾ���ֺ���
{
	unsigned char i=2;

	write_com(0x30);
	switch (hang)
	{
		case 1:write_com(0x80+lie);break;
		case 2:write_com(0x90+lie);break;
		case 3:write_com(0x88+lie);break;
		case 4:write_com(0x98+lie);break;
	}

	for(;i>0;i++)
	{
		write_data(cn[i]);
	}
	DelayNus(200);//200
}

//========================================================
void write_com(unsigned char Cbyte)
{
	CS = 1;
	chk_busy();
	SendByte(0xf8);          //11111,RW(0),RS(0),0
	SendByte(0xf0&Cbyte);
	SendByte(0xf0&Cbyte<<4);
         CS = 0;
}
//========================================================
void write_data(unsigned char Dbyte )
{
	CS = 1;
	chk_busy();
	SendByte(0xfa);          //11111,RW(0),RS(1),0
	SendByte(0xf0&Dbyte);
	SendByte(0xf0&Dbyte<<4);
	CS = 0;
}
//========================================================
void chk_busy()
{
	do    
		SendByte(0xfc);     //11111,RW(1),RS(0),0
	while(0x80&ReceiveByte());
}

//========================================================
void delay(int t)
{
	register int i,j;
	for(i=0;i<t;i++)
	for(j=0;j<125;j++);
}


/******************************************************************************************
*�������ƣ� img_disp
*���������� ��ʾͼ��
******************************************************************************************/
void gra_disp(unsigned char code *img)
{
	unsigned char i,j;
	for(j=0;j<32;j++)
	{
		for(i=0;i<8;i++)
		{
			write_com(0x34);
			write_com(0x80+j);
			write_com(0x80+i);
			write_com(0x30);
			write_data(img[j*16+i*2]);
			write_data(img[j*16+i*2+1]);
		}
	}
  for(j=32;j<64;j++)
	{
		for(i=0;i<8;i++)
		{
			write_com(0x34);
			write_com(0x80+j-32);
			write_com(0x88+i);
			write_com(0x30);
			write_data(img[j*16+i*2]);
			write_data(img[j*16+i*2+1]);
		}
	}
	write_com(0x36);   //ͼ��ģʽ��
	DelayMs(1200);
	write_com(0x34);   //ͼ��ģʽ��
}
///////////////////////////////////////////////////////////////////////////////////////
void lcd_text()
{
	LCD12864_Init();
	delay(20);
	while(1)
	{
   cn_disp(tab1);            //��ӭҳ��
   DelayMs(1000);
   cn_disp(tab2);//��ʾ���ֺ���
   DelayMs(200);
//   LcmClearTXT();
//	DelayMs(1000);
//		HZ_disp( 1,1, "��\XFD");//��ʾ���ֺ���
//		DelayMs(200);

//   lat_disp(0xff,0xff);      //��ʾȫ��
//   lat_disp(0xaa,0x55);      //��ʾ����
//   lat_disp(0x55,0xaa);      //����ʾ����     
//   lat_disp(0xaa,0xaa);      //��ʾ����
//   lat_disp(0x55,0x55);      //����ʾ����
//   lat_disp(0xff,0x00);      //��ʾ����
//   lat_disp(0x00,0xff);      //����ʾ����
//   
//   LcmClearTXT();
//   gra_disp(bmp1);
//   DelayMs(500);
//   LcmClearBMP();
//   LcmClearTXT();

	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////
 unsigned char code bmp1[]={   //����ȡģ�����ֽڵ���
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X07,0XFF,0XE0,0X0F,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X03,0XFF,0XE0,0X0F,0XFF,0X80,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X7F,0X00,0X00,0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X3F,0X00,0X00,0XF0,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X1F,0X00,0X00,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X1F,0X80,0X01,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X0F,0X80,0X01,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X07,0XC0,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X07,0XC0,0X03,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X03,0XE0,0X07,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X03,0XE0,0X07,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X01,0XF0,0X0F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X01,0XF0,0X0E,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0XF8,0X1E,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0XF8,0X1C,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X7C,0X3C,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X3C,0X39,0XF7,0XFF,0X80,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X3E,0X79,0XFF,0XFF,0XF8,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X1E,0X70,0X3C,0X00,0X7C,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X1F,0XF0,0X3C,0X00,0X1E,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X0F,0XE0,0X3C,0X00,0X1F,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X0F,0XE0,0X3C,0X00,0X1F,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X07,0XE0,0X3C,0X00,0X1E,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X07,0XC0,0X3C,0X00,0X3E,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X03,0X80,0X3C,0X00,0X78,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X03,0X80,0X3E,0X1F,0XE0,0X00,0XE0,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X02,0X00,0X07,0X00,0X3F,0XFF,0XE0,0X03,0XE0,0X00,0X00,0X01,


};
//======================================================== 

