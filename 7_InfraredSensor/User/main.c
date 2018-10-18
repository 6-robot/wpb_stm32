#include "Wp_Sys.h"

float adc_1_voltage = 0.0f;
int distance_1 = 0;

int main(void)
{
	WPB_Init();
  
	while(1)
	{
		OLED_String(0,0,"ADC_1 = ");
		adc_1_voltage	= ADC_GetVoltage(1);
		OLED_Float(8,0,adc_1_voltage,1,2);
		
		OLED_String(0,1,"Dist_1 = ");
		distance_1	= Sensor_Distance(1);
		OLED_Int(9,1,distance_1,3);
		DelayMs(500);
	}
}
