#include "Wp_Sys.h"

float Romni = 0.175;
float Rw = 0.03;
float Pi = 3.1415926;

void Omni(float Vx, float Vy, float Wz)
{
	float w1,w2,w3,ws,wt;
	w1 = -(0.866*(Vx/Rw)/(2*Pi))*60;
	w2 = -1*w1;
	w3 = 0;
	
	ws = (Vy*60)/(2*Pi*Rw);
	w1 += ws*0.5;
	w2 += ws*0.5;
	w3 += ws*-1;
	
	wt = ((Wz*Romni/Rw)/(2*Pi))*60;
	w1 += wt;
	w2 += wt;
	w3 += wt;
	
	Motor_SetSpeed(1, w1);
	Motor_SetSpeed(2, w2);
	Motor_SetSpeed(3, w3);
	Motors_Action();
	
	OLED_Float(0,0,w1,5,1);
	OLED_Float(0,1,w2,5,1);
	OLED_Float(0,2,w3,5,1);
}

void timer_handler(u32 timerchannel)
{
	if (timerchannel == TIMER_CHANNEL0)
	{
		Omni(0, 0, 0);
	}
}

int main(void)
{
	Timer_SetHandler(timer_handler);
	Timer_Enable(TIMER_CHANNEL0, 1000000 * 10);
	WPB_Init();
	
	Omni(0.1, 0, 0);
	//Omni(0, 0.1, 0);
	//Omni(0, 0, (2*Pi)/10);
	
	while(1)
	{
		
	}
}
