/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_NVIC.c
** 最后修订日期:  		2012-10-10
** 最后版本:			1.0
** 描述:				系统中断等级初始化;
**
**-----------------------------------------------------------------------------------------------------------
** 创建人:				吴康
** 创建日期:			2012-02-09
** 版本:				1.0
** 描述:				系统中断等级初始化;
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
#include "Wp_NVIC.h"


/*************************************************************************************************************
** 函数名称:			Wp_NVIC_Configuration
**
** 函数描述:			中断初始化函数;
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
void Wp_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
//  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0xB000);
    
	// Configure one bit for preemption priority 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	// 外部中断
/*	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	if(g_UP_ExtiFlag & EXTI_Line0)
	{
		NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
		NVIC_Init(&NVIC_InitStructure);
	}
	if(g_UP_ExtiFlag & EXTI_Line1)
	{
		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
		NVIC_Init(&NVIC_InitStructure);
	}
	if(g_UP_ExtiFlag & EXTI_Line2)
	{
		NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
		NVIC_Init(&NVIC_InitStructure);
	}
	if(g_UP_ExtiFlag & EXTI_Line3)
	{
		NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
		NVIC_Init(&NVIC_InitStructure);
	}
	if(g_UP_ExtiFlag & EXTI_Line4)
	{
		NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
		NVIC_Init(&NVIC_InitStructure);
	}
	if(g_UP_ExtiFlag & (EXTI_Line6|EXTI_Line7|EXTI_Line8|EXTI_Line9))
	{
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
		NVIC_Init(&NVIC_InitStructure);
	}
	if(g_UP_ExtiFlag & (EXTI_Line10|EXTI_Line11|EXTI_Line12|EXTI_Line13|EXTI_Line14|EXTI_Line15))
	{
		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
		NVIC_Init(&NVIC_InitStructure);
	}
*/
	// Timer2中断
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	// Timer3中断
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	// ADC的DMA中断
/*	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
*/
	// UART1，UART1中断，优先级必须调到最高
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	// UART2，UART2中断
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	// UART3，UART3中断
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
    
    // UART1的DMA中断
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;   
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   // 次高优先级，UART1 DMA发送
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;   
    NVIC_InitStructure.NVIC_IRQChannelCmd= ENABLE;   
    NVIC_Init(&NVIC_InitStructure);
    
    /* Enable DMA channel5 IRQ Channel */
/*	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   // 最高优先级，UART1 DMA接收
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
*/  
}


/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
