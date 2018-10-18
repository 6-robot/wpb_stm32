/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_EXTI.c
** 最后修订日期:  		2012-10-10
** 最后版本:			1.0
** 描述:				外终端相关;
**
**-----------------------------------------------------------------------------------------------------------
** 创建人:				吴康
** 创建日期:			2012-02-09
** 版本:				1.0
** 描述:				外终端相关;
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
#include "Wp_EXTI.h" 


/*************************************************************************************************************
** 函数名称:			UP_Exti_Init
**
** 函数描述:			外部中断初始化;
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
void UP_Exti_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	// PB5作为MPU6050中断输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			// 上拉输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// 连接按键IO口到中断线
	if (g_UP_ExtiFlag & EXTI_DMP)
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);
}


/*************************************************************************************************************
** 函数名称:			UP_Exti_EnableIT
**
** 函数描述:			使能外部中断;
** 						
**					    
** 输入变量:			u32 Channel, EXTITrigger_TypeDef TriggerMode;
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
void UP_Exti_EnableIT(u32 Channel, EXTITrigger_TypeDef TriggerMode)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	g_UP_ExtiFlag |= Channel;
    
	// 配置中断线
	EXTI_InitStructure.EXTI_Line = Channel;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = TriggerMode;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}


/*************************************************************************************************************
** 函数名称:			UP_Exti_SetHadler
**
** 函数描述:			传递外部中断入口函数;
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
void UP_Exti_SetHadler(void (*ApplicationAddress)(u32))
{
	if (ApplicationAddress != 0)
		g_UP_ExtiITAddress = (u32)ApplicationAddress;
}


/*************************************************************************************************************
** 函数名称:			UP_Exti_DisableIT
**
** 函数描述:			禁能外部中断;
** 						
**					    
** 输入变量:			u32 Channel;
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
void UP_Exti_DisableIT(u32 Channel)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	g_UP_ExtiFlag &= ~Channel;
    
	// 配置中断线
	EXTI_InitStructure.EXTI_Line = Channel;
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
	EXTI_Init(&EXTI_InitStructure);
}


/*************************************************************************************************************
** 函数名称:			ExtiHadler
**
** 函数描述:			定义外部中断入口函数;
** 						
**					    
** 输入变量:			u32 extichannel;
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
void ExtiHadler(u32 extichannel)
{
	if (extichannel == EXTI_DMP) 				// 判断是哪一路中断
	{
		
	}
}


/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
