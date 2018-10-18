/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_Sys.c
** 最后修订日期:  		2012-10-10
** 最后版本:			1.0
** 描述:				系统初始化文件;
**
**-----------------------------------------------------------------------------------------------------------
** 创建人:				吴康
** 创建日期:			2012-02-09
** 版本:				1.0
** 描述:				系统初始化文件;
**
**-----------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
** 版本:
** 描述:
**
**-----------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
** 版本:
** 描述:
**
*************************************************************************************************************/
#include "Wp_Sys.h"


/*************************************************************************************************************
** 函数名称:			Wp_Sev_TimerPro
**
** 函数描述:			50ms伺服中断函数;
** 						
**					    
** 输入变量:			void;
** 返回值:				void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				
** 创建日期:			2011-11-1
**-------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**-------------------------------------------------------------------------------------------------------------
***************************************************************************************************************/
void Wp_Sev_TimerPro(void)
{	
	static u8 i = 0;                    // LED1闪烁
    static u16 j = 0;                   // LED2闪烁
    static u8 k = 0;                    // 刷新按键使用
	static u8 h = 0;                    // 读取姿态信息使用
    

	if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
	}
	else if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
        
		if (++i >= 10)										        // 板载LED频闪
		{
			i = 0;
            
            LED2_TOGGLE;
		}
        if (++j >= 5)                                               // 接口面板LED频闪
        {
            j = 0;
            
            LED1_TOGGLE;
        }
        
        if (++k >= 1)                                               // 检测按键是否按下
        {
            k = 0;
            
            /*  刷新按键状态，用户切换屏幕使用      */
            Wp_KeyRefreshState(&key_up);                            // 刷新按键状态
            if (Wp_KeyAccessTimes(&key_up, KEY_ACCESS_READ) != 0)
            {
                Wp_KeyAccessTimes(&key_up, KEY_ACCESS_REFRESH);
                
                keyvalue++;                                         // 切换屏幕状态
                if (keyvalue >= 5)
                {
                    keyvalue = 1;
                }
            }
            /*  刷新按键状态，用户切换屏幕使用      */
            Wp_KeyRefreshState(&key_down);                          // 刷新按键状态
            if (Wp_KeyAccessTimes(&key_down, KEY_ACCESS_READ) != 0)
            {
                Wp_KeyAccessTimes(&key_down, KEY_ACCESS_REFRESH);
                
                keyvalue--;                                         // 切换屏幕状态
                if (keyvalue <= 0)
                {
                    keyvalue = 4;
                }
            }
            /*  刷新按键状态，用户切换屏幕使用      */
            Wp_KeyRefreshState(&key_back);                          // 刷新按键状态
            if (Wp_KeyAccessTimes(&key_back, KEY_ACCESS_READ) != 0)
            {
                Wp_KeyAccessTimes(&key_back, KEY_ACCESS_REFRESH);
                
                keyvalue = 1;                                       // 切换屏幕状态
            }
            /*  刷新按键状态，用户切换屏幕使用      */
            Wp_KeyRefreshState(&key_ok);                            // 刷新按键状态
            if (Wp_KeyAccessTimes(&key_ok, KEY_ACCESS_READ) != 0)
            {
                Wp_KeyAccessTimes(&key_ok, KEY_ACCESS_REFRESH);
                
                keyvalue = 1;                                       // 切换屏幕状态
            }
        }

        /*  50ms伺服周期返回上位机数据    */
		if (++h >= 1)
        {	
            h = 0;
            
            gpioinputvalue = Wp_GetInputValue();                    // 读输入IO口的值
            gpiooutputvalue = Wp_GetOutputValue();                  // 读输出IO口的值
            Wp_GetAdcVoltageValue();                                // 计算各通道电压
            powervalue = Wp_FilterPower();					        // 计算电池电压并滤波
						Sys_Voltage = powervalue;
            powervalueint = powervalue * 1000;
            Wp_GetMpu6050Dmp();								        // 获取姿态信息        
		}
	}
}


/*************************************************************************************************************
** 函数名称:			RCC_Configuration
**
** 函数描述:			初始化系统时钟;
** 						
**					    
** 输入变量:			void;
** 返回值:				void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				
** 创建日期:			2011-11-1
**-------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**-------------------------------------------------------------------------------------------------------------
***************************************************************************************************************/
static void RCC_Configuration(void)
{
	RCC_ClocksTypeDef RCC_ClockFreq;
	
	/**************************************************
	获取RCC的信息,调试用请参考RCC_ClocksTypeDef结构体的内容,当时钟配置完成后,
	里面变量的值就直接反映了器件各个部分的运行频率
	***************************************************/
	RCC_GetClocksFreq(&RCC_ClockFreq);
	
	/*	这个配置可使外部晶振停振的时候,产生一个NMI中断,不需要用的可屏蔽掉   */
//	RCC_ClockSecuritySystemCmd(ENABLE);
	
	/*	启动系统定时器, SYSTICK分频得到1ms的系统时钟中断 */
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
** 函数名称:			Wp_SystemConfigure
**
** 函数描述:			初始化系统函数;
** 						
**					    
** 输入变量:			void;
** 返回值:				void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				
** 创建日期:			2011-11-1
**-------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**-------------------------------------------------------------------------------------------------------------
***************************************************************************************************************/
void Wp_SystemConfigure(void)
{   
	SystemInit();																	// STM32系统初始化
	RCC_Configuration();													// 初始化系统时钟
    
	Wp_NVIC_Configuration();											// 初始化中断配置
	
	Wp_GpioConfigure(); 													// GPIO配置初始化
	Wp_KeyInit();                       					// 按键引脚初始化
    
	Wp_Usart1Configure(User_Uart_Baud);		    						// Uart1初始化，与上位机通讯接口
	Wp_SetUART1Hadler(ReceiveUart1Hadler);		    // UART1中断入口函数
	Wp_Usart2Configure(9600);
	Wp_SetUART2Hadler(ReceiveUart2Hadler);		    // UART2中断入口函数
	Wp_Usart3Configure(115200);	      						// Uart3初始化，与电机模块通讯接口
    
	Wp_AdcConfigure();					          				// ADC初始化
    
	Wp_OledInit();						            				// OLED初始化
	Wp_ClearOled();					              				// 清屏
    
	Wp_DisP16x16HanZiArray(3, 1, Name16x16, 0);   // 显示开机界面
	Wp_DisP16x16HanZiArray(4, 1, Name16x16, 1);
	
	Wp_DisP16x16HanZiArray(1, 2, Name16x16, 2);
	Wp_DisP16x16HanZiArray(2, 2, Name16x16, 3);
	Wp_DisP16x16HanZiArray(3, 2, Name16x16, 4);
	Wp_DisP16x16HanZiArray(4, 2, Name16x16, 5);
	Wp_DisP16x16HanZiArray(5, 2, Name16x16, 6);
	Wp_DisP16x16HanZiArray(6, 2, Name16x16, 7);    
	
	Wp_MPU6050DMP_Init();				            			// MPU6050初始化    
	Wp_BleKeyInit();                              // BLE模式引脚初始化
	BLEMODE_L;
	
	Wp_DelayMs(500);                              // 点亮500ms
	Wp_ClearOled();					                			// 清屏
    
	Wp_Timer2Configure();				            			// Timer2初始化，系统伺服周期定时10ms
	Wp_UserTimerConfigure();			            		// Timer3初始化，供用户使用，比较通道0~3作为4个定时器供用户使用 
    
  UART3RXEN;                                    // 上电接收使能
}

void WPB_Init(void)
{
	Wp_SystemConfigure();
}


/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
