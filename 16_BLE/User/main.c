#include "Wp_Sys.h"

int recv = 0;
int count = 0;

void ble_handler(u8 data)
{	
	recv = data;
	count ++;
	
	BLE_SendChar(count);
}

int main(void)
{
	BLE_SetHandler(ble_handler);
	
	WPB_Init();
	
	BLE_SetName("WPB_10");
	while(1)
	{
		OLED_String(0, 0, "BLE");
		OLED_String(0, 1, "recv=");
		OLED_Int(6, 1, recv, 3);
		OLED_String(0, 2, "count=");
		OLED_Int(7, 2, count, 3);
		
		DelayMs(50);
	}
}