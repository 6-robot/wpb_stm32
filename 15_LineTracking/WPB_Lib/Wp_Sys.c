/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------�ļ���Ϣ-------------------------------------------------------
** �ļ�����:			Wp_Sys.c
** ����޶�����:  		2012-10-10
** ���汾:			1.0
** ����:				ϵͳ��ʼ���ļ�;
**
**-----------------------------------------------------------------------------------------------------------
** ������:				�⿵
** ��������:			2012-02-09
** �汾:				1.0
** ����:				ϵͳ��ʼ���ļ�;
**
**-----------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
** �汾:
** ����:
**
**-----------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
** �汾:
** ����:
**
*************************************************************************************************************/
#include "Wp_Sys.h"


/*************************************************************************************************************
** ��������:			Wp_Sev_TimerPro
**
** ��������:			50ms�ŷ��жϺ���;
** 						
**					    
** �������:			void;
** ����ֵ:				void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				
** ��������:			2011-11-1
**-------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**-------------------------------------------------------------------------------------------------------------
***************************************************************************************************************/
void Wp_Sev_TimerPro(void)
{	
	static u8 i = 0;                    // LED1��˸
    static u16 j = 0;                   // LED2��˸
    static u8 k = 0;                    // ˢ�°���ʹ��
	static u8 h = 0;                    // ��ȡ��̬��Ϣʹ��
    

	if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
	}
	else if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
        
		if (++i >= 10)										        // ����LEDƵ��
		{
			i = 0;
            
            LED2_TOGGLE;
		}
        if (++j >= 5)                                               // �ӿ����LEDƵ��
        {
            j = 0;
            
            LED1_TOGGLE;
        }
        
        if (++k >= 1)                                               // ��ⰴ���Ƿ���
        {
            k = 0;
            
            /*  ˢ�°���״̬���û��л���Ļʹ��      */
            Wp_KeyRefreshState(&key_up);                            // ˢ�°���״̬
            if (Wp_KeyAccessTimes(&key_up, KEY_ACCESS_READ) != 0)
            {
                Wp_KeyAccessTimes(&key_up, KEY_ACCESS_REFRESH);
                
                keyvalue++;                                         // �л���Ļ״̬
                if (keyvalue >= 5)
                {
                    keyvalue = 1;
                }
            }
            /*  ˢ�°���״̬���û��л���Ļʹ��      */
            Wp_KeyRefreshState(&key_down);                          // ˢ�°���״̬
            if (Wp_KeyAccessTimes(&key_down, KEY_ACCESS_READ) != 0)
            {
                Wp_KeyAccessTimes(&key_down, KEY_ACCESS_REFRESH);
                
                keyvalue--;                                         // �л���Ļ״̬
                if (keyvalue <= 0)
                {
                    keyvalue = 4;
                }
            }
            /*  ˢ�°���״̬���û��л���Ļʹ��      */
            Wp_KeyRefreshState(&key_back);                          // ˢ�°���״̬
            if (Wp_KeyAccessTimes(&key_back, KEY_ACCESS_READ) != 0)
            {
                Wp_KeyAccessTimes(&key_back, KEY_ACCESS_REFRESH);
                
                keyvalue = 1;                                       // �л���Ļ״̬
            }
            /*  ˢ�°���״̬���û��л���Ļʹ��      */
            Wp_KeyRefreshState(&key_ok);                            // ˢ�°���״̬
            if (Wp_KeyAccessTimes(&key_ok, KEY_ACCESS_READ) != 0)
            {
                Wp_KeyAccessTimes(&key_ok, KEY_ACCESS_REFRESH);
                
                keyvalue = 1;                                       // �л���Ļ״̬
            }
        }

        /*  50ms�ŷ����ڷ�����λ������    */
		if (++h >= 1)
        {	
            h = 0;
            
            gpioinputvalue = Wp_GetInputValue();                    // ������IO�ڵ�ֵ
            gpiooutputvalue = Wp_GetOutputValue();                  // �����IO�ڵ�ֵ
            Wp_GetAdcVoltageValue();                                // �����ͨ����ѹ
            powervalue = Wp_FilterPower();					        // �����ص�ѹ���˲�
						Sys_Voltage = powervalue;
            powervalueint = powervalue * 1000;
            Wp_GetMpu6050Dmp();								        // ��ȡ��̬��Ϣ        
		}
	}
}


/*************************************************************************************************************
** ��������:			RCC_Configuration
**
** ��������:			��ʼ��ϵͳʱ��;
** 						
**					    
** �������:			void;
** ����ֵ:				void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				
** ��������:			2011-11-1
**-------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**-------------------------------------------------------------------------------------------------------------
***************************************************************************************************************/
static void RCC_Configuration(void)
{
	RCC_ClocksTypeDef RCC_ClockFreq;
	
	/**************************************************
	��ȡRCC����Ϣ,��������ο�RCC_ClocksTypeDef�ṹ�������,��ʱ��������ɺ�,
	���������ֵ��ֱ�ӷ�ӳ�������������ֵ�����Ƶ��
	***************************************************/
	RCC_GetClocksFreq(&RCC_ClockFreq);
	
	/*	������ÿ�ʹ�ⲿ����ͣ���ʱ��,����һ��NMI�ж�,����Ҫ�õĿ����ε�   */
//	RCC_ClockSecuritySystemCmd(ENABLE);
	
	/*	����ϵͳ��ʱ��, SYSTICK��Ƶ�õ�1ms��ϵͳʱ���ж� */
	if (SysTick_Config(SystemCoreClock / 1000))
  	{
  	  	/* Capture error */
    	while (1);
  	}
}

static u32 User_Uart_Baud = 19200;
void UART_SetBaudRate(u32 BaudRate)
{
	User_Uart_Baud = BaudRate;
}

/*************************************************************************************************************
** ��������:			Wp_SystemConfigure
**
** ��������:			��ʼ��ϵͳ����;
** 						
**					    
** �������:			void;
** ����ֵ:				void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				
** ��������:			2011-11-1
**-------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**-------------------------------------------------------------------------------------------------------------
***************************************************************************************************************/
void Wp_SystemConfigure(void)
{   
	SystemInit();																	// STM32ϵͳ��ʼ��
	RCC_Configuration();													// ��ʼ��ϵͳʱ��
    
	Wp_NVIC_Configuration();											// ��ʼ���ж�����
	
	Wp_GpioConfigure(); 													// GPIO���ó�ʼ��
	Wp_KeyInit();                       					// �������ų�ʼ��
    
	Wp_Usart1Configure(User_Uart_Baud);		    						// Uart1��ʼ��������λ��ͨѶ�ӿ�
	Wp_SetUART1Hadler(ReceiveUart1Hadler);		    // UART1�ж���ں���
	Wp_Usart2Configure(9600);
	Wp_SetUART2Hadler(ReceiveUart2Hadler);		    // UART2�ж���ں���
	Wp_Usart3Configure(115200);	      						// Uart3��ʼ��������ģ��ͨѶ�ӿ�
    
	Wp_AdcConfigure();					          				// ADC��ʼ��
    
	Wp_OledInit();						            				// OLED��ʼ��
	Wp_ClearOled();					              				// ����
    
	Wp_DisP16x16HanZiArray(3, 1, Name16x16, 0);   // ��ʾ��������
	Wp_DisP16x16HanZiArray(4, 1, Name16x16, 1);
	
	Wp_DisP16x16HanZiArray(1, 2, Name16x16, 2);
	Wp_DisP16x16HanZiArray(2, 2, Name16x16, 3);
	Wp_DisP16x16HanZiArray(3, 2, Name16x16, 4);
	Wp_DisP16x16HanZiArray(4, 2, Name16x16, 5);
	Wp_DisP16x16HanZiArray(5, 2, Name16x16, 6);
	Wp_DisP16x16HanZiArray(6, 2, Name16x16, 7);    
	
	Wp_MPU6050DMP_Init();				            			// MPU6050��ʼ��    
	Wp_BleKeyInit();                              // BLEģʽ���ų�ʼ��
	BLEMODE_L;
	
	Wp_DelayMs(500);                              // ����500ms
	Wp_ClearOled();					                			// ����
    
	Wp_Timer2Configure();				            			// Timer2��ʼ����ϵͳ�ŷ����ڶ�ʱ10ms
	Wp_UserTimerConfigure();			            		// Timer3��ʼ�������û�ʹ�ã��Ƚ�ͨ��0~3��Ϊ4����ʱ�����û�ʹ�� 
    
  UART3RXEN;                                    // �ϵ����ʹ��
}

void WPB_Init(void)
{
	Wp_SystemConfigure();
}


/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
