#include "Wp_Sys.h"

int input_1 = 0;
int output_1 = 0;

int main(void)
{
	WPB_Init();						                // 系统初始化

	while(1)
	{
		// 获取1号输入端口电平，显示在屏幕第一行
		OLED_String(0, 0, "input_1 = ");
		input_1 = Port_GetInputValue(1);
		OLED_Int(10, 0, input_1,1);
		
		// 设置1号输出口输出低电平，对应的LED熄灭
		Port_SetOutputValue(1, 0);
		
		// 获取1号输出IO电平，显示在屏幕第二行。保持大约1000毫秒（1秒）然后切换到下一状态
		OLED_String(0, 1, "output_1 = ");
		output_1 = Port_GetOutputValue(1);
		OLED_Int(11, 1, output_1,1);
		DelayMs(1000);
		
		// 设置1号输出口输出高电平，对应的LED点亮
		Port_SetOutputValue(1, 1);
		
		// 获取1号输出IO电平，显示在屏幕第二行。保持大约1000毫秒（1秒）然后切换到下一状态
		OLED_String(0, 1, "output_1 = ");
		output_1 = Port_GetOutputValue(1);
		OLED_Int(12, 1, output_1,1);
		
		DelayMs(1000);
	}
}

