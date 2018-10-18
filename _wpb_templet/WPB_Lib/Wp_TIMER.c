/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_TIMER.c
** 最后修订日期:  		2012-10-10
** 最后版本:			1.0
** 描述:				Timer初始化相关;
**
**-----------------------------------------------------------------------------------------------------------
** 创建人:				吴康
** 创建日期:			2012-02-09
** 版本:				1.0
** 描述:				Timer初始化相关;
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
#include "Wp_TIMER.h"


u32 g_UP_iTimerTime[4] = {0};			// 计时时间，us为单位

u16 g_UP_TimerCCRVal_L16[4] = {0};		// Timer比较通道比较值低16位
u16 g_UP_TimerCCRVal_H16[4] = {0};		// Timer比较通道比较值高16位

u16 g_UP_TempCCRVal_L16[4] = {0};		// Timer比较通道比较值低16位
u16 g_UP_TempCCRVal_H16[4] = {0};		// Timer比较通道比较值高16位


/*************************************************************************************************************
** 函数名称:			Wp_Timer_InitParameters
**
** 函数描述:		    初始化相关参数;
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
static void Wp_Timer_InitParameters(void)
{

}


/*************************************************************************************************************
** 函数名称:			Wp_UserTimerConfigure
**
** 函数描述:			Timer3初始化函数;
** 						Timer3作为用户定时器使用;
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
void Wp_UserTimerConfigure(void)
{
	// Timer3的4个输出比较做4路计时器
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	Wp_Timer_InitParameters();                                      // 参数初始化

	if (!g_UP_bTimerIT[0] && !g_UP_bTimerIT[1] && !g_UP_bTimerIT[2] && !g_UP_bTimerIT[3])
		return;
    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	        // 使能定时器时钟

	// Timer3基本设置
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;						// 72分频，1us
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		// 向上计数
	TIM_TimeBaseStructure.TIM_Period = 65535;						// 计数值65535
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;         // 不分频
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;              // 这个参数仅Timer1和Timer8存在，故屏蔽之
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	// 比较通道设置
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;       	// 输出比较非主动模式
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		// 极性为正，高电平有效
	
	TIM_OCInitStructure.TIM_Pulse = g_UP_iTimerTime[0]>65535?65535:g_UP_iTimerTime[0]; 	//比较时间
	if (g_UP_bTimerIT[0])                                           // 判断是否启用定时器
		TIM_OC1Init(TIM3, &TIM_OCInitStructure);					// 通道1
    
	TIM_OCInitStructure.TIM_Pulse = g_UP_iTimerTime[1]>65535?65535:g_UP_iTimerTime[1]; 	//比较时间
	if (g_UP_bTimerIT[1])                                           // 判断是否启用定时器
		TIM_OC2Init(TIM3, &TIM_OCInitStructure); 					// 通道2
    
	TIM_OCInitStructure.TIM_Pulse = g_UP_iTimerTime[2]>65535?65535:g_UP_iTimerTime[2]; 	//比较时间
	if (g_UP_bTimerIT[2])                                           // 判断是否启用定时器
		TIM_OC3Init(TIM3, &TIM_OCInitStructure); 					// 通道3
    
	TIM_OCInitStructure.TIM_Pulse = g_UP_iTimerTime[3]>65535?65535:g_UP_iTimerTime[3]; 	//比较时间
	if (g_UP_bTimerIT[3])                                           // 判断是否启用定时器
		TIM_OC4Init(TIM3, &TIM_OCInitStructure); 					// 通道4

	// 预先清除所有中断位
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4);

	// 比较中断使能
	if (g_UP_bTimerIT[0]) 
		TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);                     // 比较中断使能
	if (g_UP_bTimerIT[1]) 
		TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);                     // 比较中断使能
	if (g_UP_bTimerIT[2]) 
		TIM_ITConfig(TIM3, TIM_IT_CC3, ENABLE);                     // 比较中断使能
	if (g_UP_bTimerIT[3]) 
		TIM_ITConfig(TIM3, TIM_IT_CC4, ENABLE);                     // 比较中断使能

	TIM_Cmd(TIM3, ENABLE);	                                        // TIM3计数使能
}


/*************************************************************************************************************
** 函数名称:			TimerHadler
**
** 函数描述:		    定义Timer中断入口函数;
** 						
**					    
** 输入变量:			u32 timerchannel;
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
/*void TimerHadler(u32 timerchannel)
{
	if (timerchannel == TIMER_CHANNEL0)	 		    // 判断是那一路计时器中断
	{
		// 中断函数
	}
	else if (timerchannel == TIMER_CHANNEL1)
	{   
		// 中断函数
	}
	else if (timerchannel == TIMER_CHANNEL2)
	{
		// 中断函数
	}
	else if (timerchannel == TIMER_CHANNEL3)
	{
		// 中断函数
	}
}*/


/*************************************************************************************************************
** 函数名称:			Wp_User_TimerPro
**
** 函数描述:			用户定时器的中断服务函数;
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
void Wp_User_TimerPro(void)
{
	// 比较通道1中断
	if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
	{
	    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
		
		if (g_UP_TempCCRVal_H16[0] == 0 && g_UP_TempCCRVal_L16[0] == 0)
		{
			g_UP_TempCCRVal_L16[0] = g_UP_TimerCCRVal_L16[0];
			g_UP_TempCCRVal_H16[0] = g_UP_TimerCCRVal_H16[0];
            
			if (g_UP_TimerITAddress)
				(*((void(*)(u8))g_UP_TimerITAddress))(TIMER_CHANNEL0);
		}
		if (g_UP_TempCCRVal_H16[0] != 0)
		{
			TIM3->CCR1 += 65535;
			g_UP_TempCCRVal_H16[0]--;
		}
		else if (g_UP_TempCCRVal_L16[0] != 0)
		{
			TIM3->CCR1 += g_UP_TempCCRVal_L16[0];
			g_UP_TempCCRVal_L16[0] = 0;
		}
	}
	// 比较通道2中断
	else if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)
	{
	    TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);
		
		if (g_UP_TempCCRVal_H16[1] == 0 && g_UP_TempCCRVal_L16[1] == 0)
		{
			g_UP_TempCCRVal_L16[1] = g_UP_TimerCCRVal_L16[1];
			g_UP_TempCCRVal_H16[1] = g_UP_TimerCCRVal_H16[1];
			if (g_UP_TimerITAddress)
				(*((void(*)(u8))g_UP_TimerITAddress))(TIMER_CHANNEL1);
		}
		if (g_UP_TempCCRVal_H16[1] != 0)
		{
			TIM3->CCR2 += 65535;
			g_UP_TempCCRVal_H16[1]--;
		}
		else if (g_UP_TempCCRVal_L16[1] != 0)
		{
			TIM3->CCR2 += g_UP_TempCCRVal_L16[1];
			g_UP_TempCCRVal_L16[1] = 0;
		}
	}
	// 比较通道3中断
	else if (TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)
	{
	    TIM_ClearITPendingBit(TIM3, TIM_IT_CC3);
		if (g_UP_TempCCRVal_H16[2] == 0 && g_UP_TempCCRVal_L16[2] == 0)
		{
			g_UP_TempCCRVal_L16[2] = g_UP_TimerCCRVal_L16[2];
			g_UP_TempCCRVal_H16[2] = g_UP_TimerCCRVal_H16[2];
			if (g_UP_TimerITAddress)
				(*((void(*)(u8))g_UP_TimerITAddress))(TIMER_CHANNEL2);
		}
		if (g_UP_TempCCRVal_H16[2] != 0)
		{
			TIM3->CCR3 += 65535;
			g_UP_TempCCRVal_H16[2]--;
		}
		else if (g_UP_TempCCRVal_L16[2] != 0)
		{
			TIM3->CCR3 += g_UP_TempCCRVal_L16[2];
			g_UP_TempCCRVal_L16[2] = 0;
		}
	}
	// 比较通道4中断
	else if (TIM_GetITStatus(TIM3, TIM_IT_CC4) != RESET)
	{
	    TIM_ClearITPendingBit(TIM3, TIM_IT_CC4);
		if (g_UP_TempCCRVal_H16[3] == 0 && g_UP_TempCCRVal_L16[3] == 0)
		{
			g_UP_TempCCRVal_L16[3] = g_UP_TimerCCRVal_L16[3];
			g_UP_TempCCRVal_H16[3] = g_UP_TimerCCRVal_H16[3];
			if (g_UP_TimerITAddress)
				(*((void(*)(u8))g_UP_TimerITAddress))(TIMER_CHANNEL3);
		}
		if (g_UP_TempCCRVal_H16[3] != 0)
		{
			TIM3->CCR4 += 65535;
			g_UP_TempCCRVal_H16[3]--;
		}
		else if (g_UP_TempCCRVal_L16[3] != 0)
		{
			TIM3->CCR4 += g_UP_TempCCRVal_L16[3];
			g_UP_TempCCRVal_L16[3] = 0;
		}
	}
}


/*************************************************************************************************************
** 函数名称:			Wp_UserTimerEnableIT
**
** 函数描述:			使能计时器中断;
** 						
**					    
** 输入变量:			u32 TimerChannel, u32 Time_us;
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
void Wp_UserTimerEnableIT(u32 TimerChannel, u32 Time_us)
{
	if (TimerChannel > 3 || Time_us == 0)
		return;
    
	g_UP_bTimerIT[TimerChannel] = TRUE;															// 启动定时器标志置位
	g_UP_iTimerTime[TimerChannel] = Time_us;													// 初始化比较计数寄存器的值
	g_UP_TempCCRVal_L16[TimerChannel] = g_UP_TimerCCRVal_L16[TimerChannel] = Time_us;			// 初始化比较寄存器
	g_UP_TempCCRVal_H16[TimerChannel] = g_UP_TimerCCRVal_H16[TimerChannel] = Time_us >> 16;		// 初始化比较寄存器
}

void Timer_Enable(u32 TimerChannel, u32 IntervalUs)
{
	Wp_UserTimerEnableIT(TimerChannel, IntervalUs);
}


/*************************************************************************************************************
** 函数名称:			Wp_UserTimerDisableIT
**
** 函数描述:			禁能计时器中断;
** 						
**					    
** 输入变量:			u32 TimerChannel;
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
void Wp_UserTimerDisableIT(u32 TimerChannel)
{
	if (TimerChannel > 3)                       // 0~3通道比较使能中断
		return;
    
	g_UP_bTimerIT[TimerChannel] = FALSE;
    
	// 比较中断禁能
	if (!g_UP_bTimerIT[0]) 
		TIM_ITConfig(TIM3, TIM_IT_CC1, DISABLE);
	if (!g_UP_bTimerIT[1]) 
		TIM_ITConfig(TIM3, TIM_IT_CC2, DISABLE);
	if (!g_UP_bTimerIT[2]) 
		TIM_ITConfig(TIM3, TIM_IT_CC3, DISABLE);
	if (!g_UP_bTimerIT[3]) 
		TIM_ITConfig(TIM3, TIM_IT_CC4, DISABLE);	
}

void Timer_Disable(u32 TimerChannel)
{
	Wp_UserTimerDisableIT(TimerChannel);
}


/*************************************************************************************************************
** 函数名称:			Wp_UserTimerSetHadler
**
** 函数描述:			设置定时器中断入口函数;
** 						
**					    
** 输入变量:			void (*ApplicationAddress)(u32);
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
void Wp_UserTimerSetHadler(void (*ApplicationAddress)(u32))
{
	if (ApplicationAddress != 0)
		g_UP_TimerITAddress = (u32)ApplicationAddress;
}

void Timer_SetHandler(void (*HandlerName)(u32))
{
	Wp_UserTimerSetHadler(HandlerName);
}


/*************************************************************************************************************
** 函数名称:			Wp_Timer2Configure
**
** 函数描述:			Timer2初始化函数;
** 						10ms伺服周期;
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
void Wp_Timer2Configure(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	u16 CCR1_Val = 5000;                                            // 初始化比较通道1比较值
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);            // TIMER2 clock enable
	
	// Timer2基础设置
	TIM_TimeBaseStructure.TIM_Period = 50000;						// 计数值，10ms伺服周期
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;    					// 预分频,此值+1为分频的除数
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x00;  				// 时钟分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	// 向上计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	// 比较通道1设置
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;      		// 输出比较非主动模式
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		// 极性为正
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);				// 禁止OC1重装载,其实可以省掉这句,因为默认是4路都不重装的
	
	TIM_ARRPreloadConfig(TIM2, ENABLE);                             // 使能预装载
	
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC1 | TIM_IT_Update);        // 预先清除所有中断位
	
	TIM_ITConfig(TIM2, TIM_IT_CC1 | TIM_IT_Update, ENABLE);         // 1个通道和溢出都配置中断
	
	TIM_Cmd(TIM2, ENABLE);                                          // 允许TIMER2开始计数
}


/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
