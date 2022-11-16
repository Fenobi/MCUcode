#include "LCD1602.H"

int main()
{
	LCD_Init();
	LCD_ShowChar(1,1,'a');
	LCD_ShowString(2,1,"Kenobi");
	while(1)
	{
		
	}
}