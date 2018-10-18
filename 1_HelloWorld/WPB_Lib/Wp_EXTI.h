/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_EXTI.h
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
#ifndef WP_EXTI_H
#define WP_EXTI_H


#include "stm32f10x.h"
#include "Wp_Globle.h"


/************************************************************************************************************
**                             宏定义相关
*************************************************************************************************************/
// 外部中断通道宏定义
#define EXTI_DMP	EXTI_Line5


/************************************************************************************************************
**                             函数声明
*************************************************************************************************************/
extern void UP_Exti_Init(void);												// 外部中断初始化
extern void UP_Exti_EnableIT(u32 Channel, EXTITrigger_TypeDef TriggerMode);	// 使能外部中断通道并配置其中断模式
extern void UP_Exti_DisableIT(u32 Channel); 								// 禁能外部中断
extern void UP_Exti_SetHadler(void (*ApplicationAddress)(u32));				// 传递外部中断入口函数
extern void ExtiHadler(u32 extichannel);									// 外部中断入口函数


#endif
/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
