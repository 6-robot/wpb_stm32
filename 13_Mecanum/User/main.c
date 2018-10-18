#include "Wp_Sys.h"

float a = 0.150;
float b = 0.095;
float Rw = 0.03;
float Pi = 3.1415926;

void Mecanum(float Vx, float Vy, float Wz)
{
	float w1,w2,w3,w4,wx,wy,wt;
	wx = ((Vx/Rw)/(2*Pi))*60;
	w1 = -wx;
	w2 = wx;
	w3 = wx;
	w4 = -wx;
	
	wy = ((Vy/Rw)/(2*Pi))*60;
	w1 += wy;
	w2 += wy;
	w3 -= wy;
	w4 -= wy;
	
	wt = ((Wz*(a+b)/Rw)/(2*Pi))*60;
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
		Mecanum(0, 0, 0);
	}
}

int main(void)
{
	Timer_SetHandler(timer_handler);
	Timer_Enable(TIMER_CHANNEL0, 1000000 * 10);
	WPB_Init();
	
	Mecanum(0.1, 0, 0);
	//Mecanum(0, 0.1, 0);
	//Mecanum(0, 0, (2*Pi)/10);
	
	while(1)
	{
		
	}
}
