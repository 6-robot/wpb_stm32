/********************************************Copyright******************************************************
**                                                                                                                           
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_UART.h
** 最后修订日期:  		2011-11-1
** 最后版本:			1.0
** 描述:				串口驱动文件;
**
**-----------------------------------------------------------------------------------------------------------
** 创建人:				吴康
** 创建日期:			2011-11-1
** 版本:				1.0
** 描述:				串口驱动函数;
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
#ifndef WP_UART_H
#define WP_UART_H


#include "stm32f10x.h"
#include "Wp_Globle.h"
#include "Queue.h"
#include "Wp_Motor.h"


/************************************************************************************************************
**                             宏定义相关
*************************************************************************************************************/
// UART1Cts
#define UART1Cts_H			GPIO_SetBits(GPIOA, GPIO_Pin_8)
#define UART1Cts_L			GPIO_ResetBits(GPIOA, GPIO_Pin_8)
#define Uart1Cts			GPIOA->ODR ^= GPIO_Pin_8


/************************************************************************************************************
**                             函数声明
*************************************************************************************************************/
extern void Wp_Usart1Configure(u32 baud);
extern void Wp_Usart2Configure(u32 baud);

extern void Wp_Usart1_SendChar(unsigned char c);
extern void Wp_Usart1_SendStr(char *str);
extern void UART_SendChar(unsigned char Value);
extern void UART_SendString(char String[]);

extern void Wp_Usart2_SendChar(unsigned char c);
extern void Wp_Usart2_SendStr(char *str);

extern void Wp_Usart1_SendInt(int16_t num);
extern void Wp_Usart2_SendInt(int16_t num);

extern void ReceiveUart1Hadler(u8 val);
extern void ReceiveUart2Hadler(u8 val);

extern void Wp_SetUART1Hadler(void (*ApplicationAddress)(u8));
extern void UART_SetHandler(void (*HandlerName)(u8));
extern void Wp_SetUART2Hadler(void (*ApplicationAddress)(u8));
extern void BLE_SetHandler(void (*HandlerName)(u8));


#endif
/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
