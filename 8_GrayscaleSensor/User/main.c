#include "Wp_Sys.h"

float adc_1_voltage = 0.0f;
int lux_1 = 0;

int main(void)
{
	WPB_Init();
  
	while(1)
	{
		OLED_String(0,0,"ADC_1 = ");
		adc_1_voltage	= ADC_GetVoltage(1);
		OLED_Float(8,0,adc_1_voltage,1,2);
		
		OLED_String(0,1,"Lux_1 = ");
		lux_1	= Sensor_Lux(1);
		OLED_Int(8,1,lux_1,4);
		DelayMs(500);
	}
}
