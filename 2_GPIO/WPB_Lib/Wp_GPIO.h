/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_GPIO.h
** 最后修订日期:  		2012-10-10
** 最后版本:			1.0
** 描述:				GPIO初始化文件;
**
**-----------------------------------------------------------------------------------------------------------
** 创建人:				吴康
** 创建日期:			2012-02-09
** 版本:				1.0
** 描述:				GPIO初始化文件;
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
#ifndef WP_GPIO_H
#define WP_GPIO_H


#include "stm32f10x.h"


/************************************************************************************************************
**                             宏定义相关
*************************************************************************************************************/
// LED1为接口面板用户指示灯
#define LED1_ON				GPIO_ResetBits(GPIOC, GPIO_Pin_11)  // 点亮LED1
#define LED1_OFF			GPIO_SetBits(GPIOC, GPIO_Pin_11)    // 熄灭LED1
#define LED1_TOGGLE         GPIOC->ODR ^= GPIO_Pin_11           // LED1闪烁

// LED2为控制面板指示灯
#define LED2_ON				GPIO_ResetBits(GPIOB, GPIO_Pin_12)  // 点亮LED2
#define LED2_OFF			GPIO_SetBits(GPIOB, GPIO_Pin_12)    // 熄灭LED2
#define LED2_TOGGLE         GPIOC->ODR ^= GPIO_Pin_12           // LED2闪烁

#define PWM_1_L			    GPIO_ResetBits(GPIOB, GPIO_Pin_6)
#define PWM_1_H			    GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define PWM_2_L			    GPIO_ResetBits(GPIOB, GPIO_Pin_7)
#define PWM_2_H			    GPIO_SetBits(GPIOB, GPIO_Pin_7)
#define PWM_3_L			    GPIO_ResetBits(GPIOB, GPIO_Pin_8)
#define PWM_3_H			    GPIO_SetBits(GPIOB, GPIO_Pin_8)
#define PWM_4_L			    GPIO_ResetBits(GPIOB, GPIO_Pin_9)
#define PWM_4_H			    GPIO_SetBits(GPIOB, GPIO_Pin_9)

#define OUTPUT_1_L			GPIO_ResetBits(GPIOE, GPIO_Pin_0)
#define OUTPUT_1_H			GPIO_SetBits(GPIOE, GPIO_Pin_0)
#define OUTPUT_2_L			GPIO_ResetBits(GPIOE, GPIO_Pin_1)
#define OUTPUT_2_H			GPIO_SetBits(GPIOE, GPIO_Pin_1)
#define OUTPUT_3_L			GPIO_ResetBits(GPIOE, GPIO_Pin_2)
#define OUTPUT_3_H			GPIO_SetBits(GPIOE, GPIO_Pin_2)
#define OUTPUT_4_L			GPIO_ResetBits(GPIOE, GPIO_Pin_3)
#define OUTPUT_4_H			GPIO_SetBits(GPIOE, GPIO_Pin_3)


/************************************************************************************************************
**                             函数外部声明
*************************************************************************************************************/
extern void Wp_FlowLights(u8 dismode);

extern u8 Wp_GetInputValue(void);
extern u8 Wp_GetPortInputValue(u8 port);
extern u8 Port_GetInputValue(u8 Port);

extern u8 Wp_GetOutputValue(void);
extern u8 Wp_GetPortOutputValue(u8 port);
extern u8 Port_GetOutputValue(u8 Port);

extern void Wp_SetOutputValue(u8 value);
extern void Wp_SetPortOutputValue(u8 port, u8 value);
extern void Port_SetOutputValue(u8 Port, u8 Value);

extern void Wp_GpioConfigure(void);


#endif
/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
