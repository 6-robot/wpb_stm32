#include "Wp_Sys.h"


float R4wd = 0.165;
float Rw = 0.03;
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

float Romni = 0.175;
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
}


float a = 0.150;
float b = 0.095;
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
}

int count = 0;
u8 last_recv = 0;
bool bFrameStart = false;
u8 recv_buffer[6];
float move_x = 0;
float move_y = 0;
float turn = 0;

void ble_handler(u8 data)
{
	if(bFrameStart == false)
	{
		if(last_recv == 0x55 && data == 0xaa)
		{
			bFrameStart = true;
			recv_buffer[0] = 0x55;
			recv_buffer[1] = 0xaa;
			count = 2;
		}
	}
	else
	{
		recv_buffer[count] = data;
		count ++;
		if(count >= 6)
		{
			move_x = (recv_buffer[3]-100) * 0.005;
			move_y = (recv_buffer[4]-100) * 0.005;
			turn = (recv_buffer[5]-100) * 0.01;
			
			OLED_Float(9, 1, move_x, 2, 2);
			OLED_Float(9, 2, move_y, 2, 2);
			OLED_Float(9, 3, turn, 2, 2);
			
			FourWD(move_x, turn);
			//Omni(move_x, move_y, turn);
			//Mecanum(move_x, move_y, turn);
			
			bFrameStart = false;
		}
	}
		
	last_recv = data;
}

int main(void)
{
	BLE_SetHandler(ble_handler);
	
	WPB_Init();
	
	BLE_SetName("WPB_10");
	OLED_String(0, 0, "Remote");
	OLED_String(0, 1, "move_x =");
	OLED_String(0, 2, "move_y =");
	OLED_String(0, 3, "turn   =");
	while(1)
	{
		
		DelayMs(50);
	}
}
