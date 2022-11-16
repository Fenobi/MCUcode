#include "LCD1602.H"

int main()
{
	LCD_Init();
	while(1)
	{
		LCD_ShowChar(1,1,'a');
		LCD_ShowString(2,1,"Kenobi");
	}
}