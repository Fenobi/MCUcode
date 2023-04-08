#include <STC15F2K60S2.h>
#include <stdio.h>//包含printf();函数头文件
#include <string.h>//包含strcmp(,);函数头文件
#include "delay.h"//延时函数头文件
#include "usart.h"//串口通信函数头文件


//strcmp(str1,str2);//比较两个字符串是否相同，相同则返回0


//串口接收协议说明：把接收的字符串与规定的命令1和命令2字符串做比较，如果相同则进行对应操作

unsigned char order1[8]="ST\r\n";		//命令1：查询数据指令:”ST\r\n"
unsigned char order2[8]="PARA\r\n";	//命令2：查询参数指令:"PARA\r\n"
char i,Rdata1=1,Rdata2=1;

void main()
{
	Init_Uart();//串口初始化	
	printf("--WMH--");
	while(1)
	{
		
		if(Rdata_flag==1)//判断字符串是否接收完成
		{
			Rdata_flag=0;//清除字符串接收标志
			
			Rdata1=strcmp(order1,R_data);  //命令1比较的返回值 
			Rdata2=strcmp(order2,R_data);  //命令1比较的返回值 
			
			if(Rdata1==0)//判断是否接收命令1
			{
				printf("ST ST ST\r\n");
			}
			else if(Rdata2==0)//判断是否接收命令2
			{
				printf("PARA PARA PARA\r\n");
			}
			else//接收命令错误
			{
				printf("ERROR...\r\n");
			}
			
			for(i=0;i<8;i++)//清空接收数组，为下次接收数据做准备
			{
				R_data[i]='\0';
			}		
		}

	}
}
