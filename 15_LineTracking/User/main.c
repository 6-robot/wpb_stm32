#include "Wp_Sys.h"

int Lux[2];
int i=0;
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
}

int main(void)
{
	WPB_Init(); 
	while(1)
	{
		for(i=0;i<2;i++)
		{
			Lux[i]	= Sensor_Lux(i+1);
			OLED_Int(0,i,Lux[i],5);
		}
		
		if(Lux[0]<1500)
		{
			FourWD(0.1, 2*Pi/20);
		}
		else if(Lux[1]<1500)
		{
			FourWD(0.1, -2*Pi/20);
		}
		else
		{
			FourWD(0.1, 0);
		}
		
		DelayMs(10);
	}
}
