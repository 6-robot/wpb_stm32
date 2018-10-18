#include "Wp_Sys.h"

float R4wd = 0.165;
float Rw = 0.029;
float Pi = 3.1415926;

void FourWD(float Vx, float Wz)
{
	float w1,w2,w3,w4,wt;
	w1 = -((Vx/Rw)/(2*Pi))*60;
	w2 = -1*w1;
	w3 = w2;
	w4 = w1;
	
	wt = ((Wz*R4wd/Rw)/(2*Pi))*60*1.2222;
	w1 += wt;
	w2 += wt;
	w3 += wt;
	w4 += wt;
	
	Motor_SetSpeed(1, w1);
	Motor_SetSpeed(2, w2);
	Motor_SetSpeed(3, w3);
	Motor_SetSpeed(4, w4);
	Motors_Action();
	
	OLED_Float(0,0,w1,5,1);
	OLED_Float(0,1,w2,5,1);
	OLED_Float(0,2,w3,5,1);
	OLED_Float(0,3,w4,5,1);
}

void timer_handler(u32 timerchannel)
{
	if (timerchannel == TIMER_CHANNEL0)
	{
		FourWD(0, 0);
	}
}

int main(void)
{
	Timer_SetHandler(timer_handler);
	Timer_Enable(TIMER_CHANNEL0, 1000000 * 10);
	WPB_Init();
	
	FourWD(0.1, 0);
	//FourWD(0, (2*Pi)/10);
	
	while(1)
	{
		
	}
}
