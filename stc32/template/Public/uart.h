#ifndef __URAT__H
#define __URAT__H

#include "public.h"
#include "stdio.h"

void UART1_config();
void UART1_PutChar(char dat);
char UART1_GetChar();
void UART1_PutStr(char *p);

void UART4_config(u16 tmr);
void UART4_PutChar(char ch);
void UART4_PutStr(char *str);
char UART4_GetChar(void );

#endif
