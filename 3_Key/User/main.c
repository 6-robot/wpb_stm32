#include "Wp_Sys.h"

int main(void)
{
	WPB_Init();    
	while(1)
	{
		if(Key_Up())
		{
			OLED_Clear();
			OLED_String(0, 0, "Key_Up");
		}
		if(Key_Down())
		{
			OLED_Clear();
			OLED_String(0, 0, "Key_Down");
		}
		if(Key_Back())
		{
			OLED_Clear();
			OLED_String(0, 0, "Key_Back");
		}
		if(Key_OK())
		{
			OLED_Clear();
			OLED_String(0, 0, "Key_OK");
		}
	}
}
