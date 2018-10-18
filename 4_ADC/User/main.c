#include "Wp_Sys.h"

int adc_1_value = 0;
float adc_1_voltage = 0.0f;

int main(void)
{
	WPB_Init();
	while(1)
	{
		adc_1_value = ADC_GetValue(1);
		OLED_Int(0,0,adc_1_value,5);
		adc_1_voltage	= ADC_GetVoltage(1);
		OLED_Float(0,1,adc_1_voltage,1,2);
		DelayMs(500);
	}
}
