#ifndef __URAT__H
#define __URAT__H

#include "public.h"
#include "stdio.h"

void UartInit();
void UART1_PutChar(char dat);
char UART1_GetChar();
void UART1_PutStr(char *p);

#endif
