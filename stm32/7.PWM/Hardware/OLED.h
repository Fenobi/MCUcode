#ifndef __OLED_H
#define __OLED_H

void OLED_Init(void);//OLED初始化
void OLED_Clear(void);//OLED清平
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);//OLED显示一个字符
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);//OLED显示字符串
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);//OLED显示无符号数字
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);//OLED显示有符号数字
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);//OLED显示16进制数字
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);//OLED显示2进制数字

#endif
