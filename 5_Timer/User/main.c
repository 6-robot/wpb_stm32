#include "Wp_Sys.h"

int counter_0 = 0;

void timer_handler(u32 timerchannel)
{
	if (timerchannel == TIMER_CHANNEL0)
	{
		counter_0++;
	}
}

int main(void)
{
	Timer_SetHandler(timer_handler);
	Timer_Enable(TIMER_CHANNEL0, 1000000);
	
	WPB_Init();
	
	while(1)
	{
		OLED_String(0, 0, "counter_0 = ");
		OLED_Int(12, 0, counter_0, 3);
		DelayMs(10);
	}
}
