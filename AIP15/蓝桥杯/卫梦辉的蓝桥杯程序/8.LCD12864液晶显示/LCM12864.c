#include "LCM12864.h"
#include "delay.h"//��ʱ����ͷ�ļ�

sbit LCD12864_E =P1^2;//E�ܽ�.......һ��Ҫ��ʹ�õĹܽǳ�ʼ��
sbit LCD12864_WR  =P2^1;//WR�ܽ�
sbit LCD12864_RS  =P2^0;//RS�ܽ�
sbit LCD12864_REST  =P2^6;//REST�ܽ�(��λ��Ĭ�ϽӸ�) 

#define LCD12864_Data  P0//DB0--DB7���ݹܽ�

void LCD_PIN()//��I/O�ڳ�ʼ��
{
    P2M1 &= 0x00;	P2M0 &= 0x00;//����P2Ϊ׼˫���
    P0M1 &= 0x00;	P0M0 &= 0x00;//����P1Ϊ׼˫���
}

//*********************************************************

  //��12864��д������
void LCD12864_Write_Data(unsigned char dat)//��12864��д������
{
    LCD12864_E = 0;
    LCD12864_WR = 0;//ѡ��дģʽ 
    LCD12864_RS = 1;//ѡ������ģʽ

    //��ʱ
    delay_10us(1);
    //������׼��
    LCD12864_Data = dat;
    delay_10us(1);
    LCD12864_E = 1;//��ʾ��ʼд������,������д������
    delay_10us(20); //��ʱ�ȴ�����ȫ���������
}

//��12864��д������
void LCD12864_Write_Com(unsigned char com)//��12864��д������
{
    //������������Ƭѡ�ź�
    LCD12864_E = 0;//Ƭѡ�ź�һ������Ϊ0��ʾƬѡ
    LCD12864_WR = 0;//ѡ��дģʽ 
    LCD12864_RS = 0;//ѡ������ģʽ
    //��ʱ
    delay_10us(1);
    //������׼��
    LCD12864_Data = com;
    delay_10us(1);
    LCD12864_E = 1;//��ʾ��ʼд������,������д������
    delay_10us(20);
}

        
         //��LCD12864���г�ʼ��
void LCD12864_Init()//��LCD12864���г�ʼ��
{
    LCD_PIN();//��I/O�ڳ�ʼ��
    //���ȶ�LCD���и�λ
    LCD12864_REST = 0;
    Delay_ms(30);
    LCD12864_REST = 1;
    Delay_ms(20);

    /* ��ʼ��ʼ���Ĳ��� */
    LCD12864_Write_Com(0x30);
    LCD12864_Write_Com(0x08);
    LCD12864_Write_Com(0x01);
    LCD12864_Write_Com(0x06);
    LCD12864_Write_Com(0x0c);
}

           /*  
        1.�ܹ���Ϊ����������Ļ,���е�0->31�к͵�32->63�е��е�ַ��ͬ

        (�� 0->31)��һ����Ļ���׵�ַ(0x80,0x80) -> ... -> (0x80,0x87)
                                   ....
                                  (0xa0,0x80) -> ... -> (0xa0,0x87)
        (�� 32->63)�ڶ�����Ļ���׵�ַ(0x80,0x88) -> ... -> (0x80,0x90)
                                    ...
                                 (0xa0,0x88) -> ... -> (0xa0,0x90)

        2.ÿ����ַ���ǿ��� һ��16��С��,�����������ݷֱ����ǰ8��ͺ�8����,
            ��д���01010101 01010101��������Ļ�ĵ� , 1��ʾ 0����ʾ

        3.��д���е�ַ,��д���е�ַ,����д�е�ַ���Զ�����
        */

//������������ LCD12864_Clear_Screen(0xFF)ȫ��
//LCD12864_Clear_Screen(0xFF)ȫ��
void LCD12864_Clear_Screen(unsigned char value)
{
    unsigned char i,j;

    LCD12864_Write_Com(0x34);
    LCD12864_Write_Com(0x36);


    for(i=0;i<64;i++)
    {
        if(i<32)
        {
            LCD12864_Write_Com(0x80+i);
            LCD12864_Write_Com(0x80);
        }
        else 
        {
            LCD12864_Write_Com(0x80+(i-32));
            LCD12864_Write_Com(0x88);
        }

        for(j=0;j<16;j++)
        LCD12864_Write_Data(value);
    }
}
        
//��ʾ�������ַ� �� �����ַ������,��Ϊ�Դ����ֿ�,ֻ��ע��д���ֵ�ʱ��Ҫ����д!
// ע��������������,һ��Ҫע��!!!
/*  
    ʵ������:
    0x80 -> 0x87
    0x90 -> 0x97
    0x88 -> 0x8f
    0x98 -> 0x9f
//������������Լ��涨��,�ٻ���������ʵ������Ϳ�����
    ָ������(1,1) -> (1,8)
            (4,1) -> (4,8)
    ��ָ����Ҫ��ʾ���ַ�
*/
unsigned char addresses[] = {0x80,0x90,0x88,0x98};
void LCD12864_Display_Char(unsigned char x,unsigned char y,unsigned char dat)
{
    LCD12864_Write_Com(0x30);
    LCD12864_Write_Com(0x06);

    //д���ַ
    LCD12864_Write_Com(addresses[x-1]+(y-1));

    //д������
    LCD12864_Write_Data(dat);
}

//*******************************************��ʾ����
void LCD12864_Display_Chars(unsigned char x,unsigned char y,unsigned char *dat)
{
    LCD12864_Write_Com(0x30);
    LCD12864_Write_Com(0x06);
    //д���ַ
    LCD12864_Write_Com(addresses[x-1]+(y-1));
    //д������
    while(*dat != '\0')
    {
        LCD12864_Write_Data(*dat);
        dat++;
    }
}
//*******************************************��ʾ��������ֵ      
void LCD12864_ZS_display(unsigned char x,unsigned char y,unsigned int num)//��ʾ����ֵ����
{
    unsigned char str1[10];
	  sprintf(str1,"%d",num);//������ת�����ַ���,���������С�
    LCD12864_Display_Chars(x,y,str1);//������������ʾ
}

//*******************************************��ʾָ��λ��С������ֵ      
void LCD12864_XS_display(unsigned char x,unsigned char y,float num,unsigned char wei)//��ʾָ��λ��С������ֵ 
{
  unsigned char str1[10];
	switch(wei)
	{
		case 0: sprintf(str1,"%0.0f",num);break;
		case 1: sprintf(str1,"%0.1f",num);break;
		case 2: sprintf(str1,"%0.2f",num);break;
		case 3: sprintf(str1,"%0.3f",num);break;
		case 4: sprintf(str1,"%0.4f",num);break;
		case 5: sprintf(str1,"%0.5f",num);break;
		case 6: sprintf(str1,"%0.6f",num);break;
	}
  LCD12864_Display_Chars(x,y,str1);//������������ʾ
}

//*******************************************�������
//��:LCD12864_display(2,3,6) ָ���LCD����2�еĵ�3~6����ʾ���ַ�
void LCD12864_Clearn(unsigned char hang,unsigned char x1,unsigned char x2)//��ʾ����ֵ����
{
	unsigned char i;
	for(i=x1;i<=x2;i++)
	{
			LCD12864_Display_Chars(hang,i,"  ");//������������ʾ
	}
}


void LCD12864_Test()//LCD12864��ʾ���Գ���
{
    unsigned char *datas ="LCD Һ����ʾ";
    unsigned char str1[20];
    unsigned int a=1987;
    float b=1999.12;
    
    //Һ����ʼ��
    LCD12864_Init();
    LCD12864_Clear_Screen(0x00); //����

    while(1)
    {
        sprintf(str1,"����:%4d",a);//������ת�����ַ���,���������С�
        LCD12864_Display_Chars(1,1,str1);//������������ʾ
        sprintf(str1,"����:%0.2f",b);//������ת�����ַ���,���������С�
        LCD12864_Display_Chars(2,1,str1);//������������ʾ
        LCD12864_Display_Char(3,2,'A');
        LCD12864_ZS_display(3,4,1235);//��ʾ����ֵ����
			  LCD12864_XS_display(4,1,36.2354,3);//��ʾ����ֵ����
    }

}

        
 