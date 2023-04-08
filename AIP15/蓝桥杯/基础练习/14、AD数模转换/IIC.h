#ifndef IIC_H
#define IIC_H

#include <STC15F2K60S2.h>
#include <intrins.h>
sbit SCL = P2^0;
sbit SDA = P2^1;

void iic_Start();
void iic_Stop();
void Send_ACK(bit ackbit);
bit waitAck();
void Write_byte(unsigned char da);
unsigned char Read_byte();


#endif