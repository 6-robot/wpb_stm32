#include "Wp_Sys.h"

int input_1 = 0;
int output_1 = 0;

int main(void)
{
	WPB_Init();						                // ϵͳ��ʼ��

	while(1)
	{
		// ��ȡ1������˿ڵ�ƽ����ʾ����Ļ��һ��
		OLED_String(0, 0, "input_1 = ");
		input_1 = Port_GetInputValue(1);
		OLED_Int(10, 0, input_1,1);
		
		// ����1�����������͵�ƽ����Ӧ��LEDϨ��
		Port_SetOutputValue(1, 0);
		
		// ��ȡ1�����IO��ƽ����ʾ����Ļ�ڶ��С����ִ�Լ1000���루1�룩Ȼ���л�����һ״̬
		OLED_String(0, 1, "output_1 = ");
		output_1 = Port_GetOutputValue(1);
		OLED_Int(11, 1, output_1,1);
		DelayMs(1000);
		
		// ����1�����������ߵ�ƽ����Ӧ��LED����
		Port_SetOutputValue(1, 1);
		
		// ��ȡ1�����IO��ƽ����ʾ����Ļ�ڶ��С����ִ�Լ1000���루1�룩Ȼ���л�����һ״̬
		OLED_String(0, 1, "output_1 = ");
		output_1 = Port_GetOutputValue(1);
		OLED_Int(12, 1, output_1,1);
		
		DelayMs(1000);
	}
}

