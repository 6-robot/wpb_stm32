#include "Wp_Sys.h"

u8 recv = 0;
int count = 0;

void uart_handler(u8 data)
{	
	recv = data;
	count ++;
	UART_SendChar(6);
}

int main(void)
{
	UART_SetBaudRate(19200);
	UART_SetHandler(uart_handler);
	
	WPB_Init();
	
	while(1)
	{
		OLED_String(0, 0, "UART");
		OLED_Int(0,1,recv,3);
		OLED_Int(0,2,count,3);
		
		DelayMs(50);
	}
}
