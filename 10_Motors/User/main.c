#include "Wp_Sys.h"

int main(void)
{
	WPB_Init();
	
	while(1)
	{
		Motor_SetSpeed(1, 20.0);
		Motors_Action();
		DelayMs(3000);
		
		Motor_SetSpeed(2, 20.0);
		Motors_Action();
		DelayMs(3000);
		
		Motor_SetSpeed(1, 0.0);
		Motor_SetSpeed(2, 0.0);
		Motors_Action();
		DelayMs(3000);
	}
}
