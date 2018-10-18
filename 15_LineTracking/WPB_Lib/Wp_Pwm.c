/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_Pwm.c
** 最后修订日期:  		2012-10-10
** 最后版本:			1.0
** 描述:				PWM配置文件;
**
**-----------------------------------------------------------------------------------------------------------
** 创建人:				吴康
** 创建日期:			2012-02-09
** 版本:				1.0
** 描述:				PWM配置文件;
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
#include "Wp_Pwm.h"


u32 g_UP_PWMFrequency[WP_PWM_NUM] = {0};	// PWM频率
u16 g_UP_PWMDutyTime[WP_PWM_NUM] = {0};		// PWM占空比

u8 g_UP_bPWM_L[WP_PWM_NUM] = {0};			// PWM通道当前是否是低电平

u16 g_UP_PWMCCRVal_H[WP_PWM_NUM] = {0};		// PWM高电平时间，高电平时间初始化的时候进行设置
u16 g_UP_PWMCCRVal_L[WP_PWM_NUM] = {0};		// PWM低电平时间

u8 g_UP_bPWMMode[WP_PWM_NUM];				// 端口模式，PWM或IO-OUT，高电平为PWM模式，低电平为IO-OUT模式
u8 g_UP_PWMIOVal[WP_PWM_NUM];				// IO模式端口电平，输入电平值来判断输出高电平还是低电平


/*************************************************************************************************************
** 函数名称:			Wp_PwmInitParameters
**
** 函数描述:			PWM参数初始化设置;
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
static void Wp_PwmInitParameters(void)
{
	u8 i = 0;
    
	for(i = 0; i < WP_PWM_NUM; i++)
	{
		g_UP_PWMFrequency[i] = 1000;            // 频率设置，2KHz
        
		g_UP_PWMCCRVal_H[i] = 10;               // PWM高电平的时间
		g_UP_PWMCCRVal_L[i]	= 1990;             // PWM低电平的时间
        
		g_UP_bPWM_L[i] = 0;                     // 初始化设定为低电平输出标志，PWM端口输出低电平
        
		g_UP_PWMDutyTime[i] = 2048;             // 占空比设置
	}
}


/*************************************************************************************************************
** 函数名称:			Wp_PwmConfigure
**
** 函数描述:			PWM初始化函数;
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
void Wp_PwmConfigure(void)	
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;                  // Timer4的4个输出比较做4路PWM
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	Wp_PwmInitParameters();                                         // 参数初始化

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);           // 使能端口时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);            // 使能定时器时钟
	
	WP_PWM0_L;                                                      // GPIO设置，初始化PWM端口输出低电平
	WP_PWM1_L;
	WP_PWM2_L;
	WP_PWM3_L;
    
    // PB6，PB7，PB8，PB9设置为推挽服用输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			        // 推免复用输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		        // 50M时钟速度
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
    
	// Timer4基本设置
	TIM_DeInit(TIM4);
	TIM_TimeBaseStructure.TIM_Prescaler = 36-1;						// 36分频，2MHz
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		// 向上计数
	TIM_TimeBaseStructure.TIM_Period = 65535;						// 计数值65535
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;         // 不分频
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;              // 仅Timer1和Timer8有此项，故屏蔽之
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    
	// 比较输出通道设置
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle; 			// 比较翻转模式
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 	// 正向通道有效
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;// 反向通道无效
    
	TIM_OCInitStructure.TIM_Pulse = g_UP_PWMCCRVal_H[0]; 			// 比较（低电平翻转）时间
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 		// 输出极性
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;     // 互补端的极性  
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);						// 通道1
    
	TIM_OCInitStructure.TIM_Pulse = g_UP_PWMCCRVal_H[1];
	TIM_OC2Init(TIM4, &TIM_OCInitStructure); 						// 通道2
	TIM_OCInitStructure.TIM_Pulse = g_UP_PWMCCRVal_H[2];
	TIM_OC3Init(TIM4, &TIM_OCInitStructure); 						// 通道3
	TIM_OCInitStructure.TIM_Pulse = g_UP_PWMCCRVal_H[3];
	TIM_OC4Init(TIM4, &TIM_OCInitStructure); 						// 通道4
	
	TIM_CtrlPWMOutputs(TIM4, ENABLE);                               // TIM4使能PWM输出
	
//	TIM_ITConfig(TIM4, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);  // 比较中断使能（默认不使能）
	
	TIM_Cmd(TIM4, ENABLE);                                          // TIM4计数使能
}


/*************************************************************************************************************
** 函数名称:			Wp_PwmEnable
**
** 函数描述:			使能PWM模式输出;
** 						使能PWM中断;
**					    
** 输入变量:			u8 Channel, FunctionalState NewState;
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
void Wp_PwmEnable(u8 Channel, FunctionalState NewState)
{
	if (Channel > WP_PWM_NUM)
		return;
    
	g_UP_bPWMMode[Channel] = (NewState == DISABLE)?0:1;     // 使能PWM中断
    
	if (g_UP_bPWMMode[Channel])		                        // 如果设置为PWM模式，使能相应中断
		TIM_ITConfig(TIM4, 0x02 << Channel, ENABLE);
	else
		TIM_ITConfig(TIM4, 0x02 << Channel, DISABLE);
}


/*************************************************************************************************************
** 函数名称:			Wp_PwmTimerPro
**
** 函数描述:			中断服务函数;
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
void Wp_Pwm_TimerPro(void)
{
	// 比较通道1中断
	if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)
	{
	    TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);
        
		TIM4->CCR1 += g_UP_bPWM_L[0]?g_UP_PWMCCRVal_L[0]:g_UP_PWMCCRVal_H[0];
		g_UP_bPWM_L[0] = !g_UP_bPWM_L[0];
	}
    
	// 比较通道2中断
	else if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)
	{
	    TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);
        
	    TIM4->CCR2 += g_UP_bPWM_L[1]?g_UP_PWMCCRVal_L[1]:g_UP_PWMCCRVal_H[1];
		g_UP_bPWM_L[1] = !g_UP_bPWM_L[1];
	}
    
	// 比较通道3中断
	else if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)
	{
	    TIM_ClearITPendingBit(TIM4, TIM_IT_CC3);
        
	    TIM4->CCR3 += g_UP_bPWM_L[2]?g_UP_PWMCCRVal_L[2]:g_UP_PWMCCRVal_H[2];
		g_UP_bPWM_L[2] = !g_UP_bPWM_L[2];
	}
    
	// 比较通道4中断
	else if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)
	{
	    TIM_ClearITPendingBit(TIM4, TIM_IT_CC4);
        
	    TIM4->CCR4 += g_UP_bPWM_L[3]?g_UP_PWMCCRVal_L[3]:g_UP_PWMCCRVal_H[3];
		g_UP_bPWM_L[3] = !g_UP_bPWM_L[3];
	}
    else
    {
        
    }
}


/*************************************************************************************************************
** 函数名称:			Wp_Pwm_SetCCR
**
** 函数描述:			设置占空比对应的计时器计数值;
** 						
**					    
** 输入变量:			u8 Channel;
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
static void Wp_Pwm_SetCCR(u8 Channel)	
{
	if (Channel > WP_PWM_NUM)
		return;
    
	g_UP_PWMCCRVal_H[Channel] = (2000000/g_UP_PWMFrequency[Channel]*g_UP_PWMDutyTime[Channel])>>12; 	    // 高电平时间
	g_UP_PWMCCRVal_L[Channel] = (2000000/g_UP_PWMFrequency[Channel]*(4095-g_UP_PWMDutyTime[Channel]))>>12;	// 低电平时间
}


/*************************************************************************************************************
** 函数名称:			Wp_PwmSetDutyTime
**
** 函数描述:			设置占空时间0~4095;
** 						
**					    
** 输入变量:			u8 Channel, u16 DutyTime;
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
void Wp_PwmSetDutyTime(u8 Channel, u16 DutyTime)	
{
	if (Channel > WP_PWM_NUM || DutyTime > 4095)
		return;
    
	g_UP_PWMDutyTime[Channel] = DutyTime;
	Wp_Pwm_SetCCR(Channel);
}


/*************************************************************************************************************
** 函数名称:			Wp_PwmSetFrequency
**
** 函数描述:			设置频率;
** 						
**					    
** 输入变量:			u8 Channel, u32 Frequency;
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
void Wp_PwmSetFrequency(u8 Channel, u32 Frequency)
{
	if (Channel > WP_PWM_NUM)
		return;
    
	g_UP_PWMFrequency[Channel] = Frequency;
	Wp_Pwm_SetCCR(Channel);
}


/*************************************************************************************************************
** 函数名称:			Wp_PwmSetIO
**
** 函数描述:			设置IO输出;
** 						
**					    
** 输入变量:			u8 Channel, u8 Value;
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
void Wp_PwmSetIO(u8 Channel, u8 Value)
{
	if (Channel > WP_PWM_NUM || Value > 1)
		return;
    
	g_UP_PWMIOVal[Channel] = Value;
    
	if (g_UP_bPWMMode[Channel] == 1)                    // 如果是PWM模式，则不使能定时器比较中断
		TIM_ITConfig(TIM4, 0x02 << Channel, DISABLE);
    
	g_UP_bPWMMode[Channel] = 0;                         // 0为PWM工作在IO-OUT模式
    
	switch(Channel)								        // 将相应的端口设置成需要的电平
	{
		case 0: 
            Value ? WP_PWM0_H : WP_PWM0_L;
        
            break;
		case 1: 
            Value ? WP_PWM1_H : WP_PWM1_L;
        
            break;
		case 2: 
            Value ? WP_PWM2_H : WP_PWM2_L;
        
            break;
		case 3: 
            Value ? WP_PWM3_H : WP_PWM3_L;
        
            break;
		default: 
            break;
	}
}


/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
