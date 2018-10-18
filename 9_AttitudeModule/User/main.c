#include "Wp_Sys.h"

float pitch = 0.0;
float roll = 0.0;
float yaw = 0.0;

int main(void)
{
	WPB_Init();
	
	
	while(1)
	{
		pitch = Gyro_GetPitch();				            //¸©Ñö½Ç
		OLED_String(0, 1, "P:");
		OLED_Float(2, 1, pitch, 4, 2);
		
		roll = Gyro_GetRoll();				            //·­¹ö½Ç
		OLED_String(0, 2, "R:");
		OLED_Float(2, 2, roll, 4, 2);
		
		yaw = Gyro_GetYaw();					            //º½Ïò½Ç
		OLED_String(0, 3, "Y:+");
		OLED_Float(2, 3, yaw, 4, 2);
		
		DelayMs(50);
	}
}
