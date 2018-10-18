/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_Sys.h
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
#ifndef WP_SYS_H
#define WP_SYS_H


#include "stm32f10x.h"
#include <stdio.h>						// printf函数用
#include "stdlib.h"
#include <string.h>
#include "math.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "inv_mpu.h"
#include "Wp_GPIO.h"
#include "Wp_Globle.h"
#include "Wp_Key.h"
#include "Wp_Ble.h"
#include "Wp_UART.h"
#include "Wp_IIC.h"
#include "Wp_IIC.h"
#include "Wp_ADC.h"
#include "Wp_Motor.h"
#include "Wp_OLED.h"
#include "Wp_NVIC.h"
#include "Wp_HallSensor.h"
#include "Wp_MPU6050.h"
#include "Wp_TIMER.h"
#include "Wp_EXTI.h"
#include "CfgTypes.h"
#include "Queue.h"
#include "Wp_Pwm.h"
#include "Wp_25F16.h"
#include "Wp_Flash.h"
#include "Wp_Dma.h"


/************************************************************************************************************
**                             宏定义相关
*************************************************************************************************************/
// 位带操作,实现51类似的GPIO控制功能
// 具体实现思想,参考<<CM3权威指南>>第五章(87页~92页)
// IO口操作宏定义
/*
#define BITBAND(addr, bitnum)       ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)              *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)       MEM_ADDR(BITBAND(addr, bitnum)) 


// IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) 		// 0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) 		// 0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) 		// 0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) 		// 0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) 		// 0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) 		// 0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) 		// 0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) 		// 0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) 		// 0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) 		// 0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) 		// 0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) 		// 0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) 		// 0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) 		// 0x40011E08 


// IO口操作,只对单一的IO口
// 确保n的值小于16
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  	// 输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  	// 输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  	// 输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  	// 输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  	// 输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  	// 输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  	// 输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  	// 输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n) 	// 输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  	// 输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  	// 输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  	// 输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  	// 输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  	// 输入
*/

/************************************************************************************************************
**                             函数外部声明
*************************************************************************************************************/
extern void Wp_SystemConfigure(void);
extern void WPB_Init(void);
extern const unsigned char Name16x16[];
extern void UART_SetBaudRate(u32 BaudRate);


#endif
/********************************************************************************************************
**                              End Of File
********************************************************************************************************/
