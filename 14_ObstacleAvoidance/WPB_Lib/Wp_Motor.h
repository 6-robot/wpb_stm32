/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_Motor.h
** 最后修订日期:  		2012-10-10
** 最后版本:			1.0
** 描述:				电机驱动文件;
**
**-----------------------------------------------------------------------------------------------------------
** 创建人:				吴康
** 创建日期:			2012-02-09
** 版本:				1.0
** 描述:				电机驱动文件;
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
#ifndef WP_MOTOR_H
#define WP_MOTOR_H


#include "stm32f10x.h"

#include "Wp_Globle.h"
#include "Wp_UART.h"
#include "Queue.h"

#include <string.h>


#define		UPROBOT_GLOBALS

#ifndef   UPROBOT_GLOBALS
     #define UPROBOT_EXT
#else 
     #define UPROBOT_EXT  extern
#endif 
     
     
/************************************************************************************************************
**                            	宏定义
*************************************************************************************************************/
#define UPMOTOR_COMMAND_INFO_MAX_LENGTH			0x20			// 最长参数定义
#define UPMOTOR_DATA_INFO_MAX_LENGTH			0x20            // 根据启智模块设计，最多4个驱动轮，顾最多需要16字节缓存
     
     
// Usart3发送接收使能端口宏定义
//#define UART3TXEN   GPIO_SetBits(GPIOD, GPIO_Pin_7)           // 置高电平
//#define UART3RXEN   GPIO_ResetBits(GPIOD, GPIO_Pin_7)	        // 置低电平

//#define UART3TXEN   GPIOD->BSRR = GPIO_Pin_7                  // 置高电平，使能发送
//#define UART3RXEN   GPIOD->BRR = GPIO_Pin_7                   // 置低电平，使能接收

#define UART3TXEN      (GPIOD->ODR |= GPIO_Pin_7)				// 置高电平
#define UART3RXEN      (GPIOD->ODR &= ~GPIO_Pin_7)			    // 置低电平


/*************************************************************************************************************************
**                                                     结构体定义
*************************************************************************************************************************/
typedef struct SUpMotorDataInfo                                 // 发送给驱动模块的协议帧
{
	u8 local_id;												// 本机ID
	u8 device_id;												// 设备ID
	u8 method_code;												// 方法代号，控制字
    
	u8 parameter_length;										// 参数长度
    
	u8* p_para;													// 参数数组指针，用于发送
	u8 parameter[UPMOTOR_DATA_INFO_MAX_LENGTH];					// 参数数组，用于接收
}UPMOTOR_DATA_INFO_STRUCT;										// UpRobot主机接收从机发送结构体


typedef struct SUpMotorCommandInfo                              // 解析驱动模块发送协议帧
{
	u8 local_id;												// 本机ID
	u8 device_id;												// 设备ID
	u8 method_code;												// 方法代号
	
	u8 parameter_length;										// 参数长度
    
	u8* p_para;													// 参数数组指针，用于发送
	u8 parameter[UPMOTOR_COMMAND_INFO_MAX_LENGTH];				// 参数数组，用于接收
}UPMOTOR_COMMAND_INFO_STRUCT;									// UpRobot主机发送从机接收结构体


typedef struct WpMotorDataInfo                                  // 发送关节模块的速度和位置结构体
{
	long sendspeed;								                // 发送给各个模块的速度缓存，也就是解析上位机的速度缓存
	long receivespeed;							                // 接收各个模块的速度缓存，也就是要发给上位机的速度缓存
    long receiveposition;                                       // 接收各个模块的位置缓存，也就是要发给上位机的位置缓存
}WP_MOTOR_DATA_INFO_STRUCT;


/*************************************************************************************************************************
**                                                     结构体定义
*************************************************************************************************************************/
UPROBOT_EXT UPMOTOR_COMMAND_INFO_STRUCT str_motor_cmd;
UPROBOT_EXT UPMOTOR_DATA_INFO_STRUCT str_motor_reply;
UPROBOT_EXT WP_MOTOR_DATA_INFO_STRUCT motor_data[4];


/************************************************************************************************************
**                            	外部函数声明
*************************************************************************************************************/
UPROBOT_EXT void Wp_Usart3_SendChar(unsigned char c);
UPROBOT_EXT void Wp_Usart3_SendStr(char *str);
UPROBOT_EXT void Wp_Usart3Configure(u32 baud);
UPROBOT_EXT void ReceiveUart3Hadler(u8 val);
UPROBOT_EXT void Wp_SetUART3Hadler(void (*ApplicationAddress)(u8));

UPROBOT_EXT void Wp_SetMotorSpeed(u8 motorid, long speed);
UPROBOT_EXT void Motor_SetSpeed(u8 MotorID, float MotorSpeed);
UPROBOT_EXT void Wp_ActiomMotorMode(void);
UPROBOT_EXT void Motors_Action(void);

UPROBOT_EXT void UpMotorSlaveTxPacket(UPMOTOR_DATA_INFO_STRUCT* p_uprobot_send);
UPROBOT_EXT uint8_t UpMotorSlaveRxPacket(BUFFER_QUEUE* p_usart_data, UPMOTOR_COMMAND_INFO_STRUCT* p_uprobot_receive);


#endif
/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
