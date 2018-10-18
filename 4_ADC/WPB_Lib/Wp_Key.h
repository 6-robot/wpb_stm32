/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_Key.h
** 最后修订日期:  		2012-10-10
** 最后版本:			1.0
** 描述:				操作按键函数;
**
**-----------------------------------------------------------------------------------------------------------
** 创建人:				吴康
** 创建日期:			2012-02-09
** 版本:				1.0
** 描述:				操作按键函数;
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
#ifndef WP_KEY_H
#define WP_KEY_H


#include "stm32f10x.h"
#include "Wp_GPIO.h"


/************************************************************************************************************
**                            	宏定义相关
*************************************************************************************************************/
// 初版
/*
#define CHECKKEYUP          GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_15)           // 读按键的值
#define CHECKKEYDOWN        GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_14)           // 读按键的值
#define CHECKKEYBACK        GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13)           // 读按键的值
#define CHECKKEYOK          GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12)           // 读按键的值

#define key_up()            (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_15))
#define key_down()          (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_14))
#define key_back()          (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13))
#define key_ok()            (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12))
*/

// 第二版，发给华中科大的版本
#define CHECKKEYUP          GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12)           // 读按键的值
#define CHECKKEYDOWN        GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13)           // 读按键的值
#define CHECKKEYBACK        GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_14)           // 读按键的值
#define CHECKKEYOK          GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_15)           // 读按键的值

#define Key_Up()            (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12))
#define Key_Down()          (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13))
#define Key_Back()          (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_14))
#define Key_OK()            (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_15))


#define USER_DATA_EN		(0)             // 使能用户数据，每一个按键有一个变量供用户使用
#define KEY_USE_SEM			(0)	            // 1：使用按键互斥信号量，0：不使用按键互斥信号量
#define KEY_WOBBLE_TIME		(5)             // 按键抖动时间，也就是消抖时间，单位ms
//#define KEY_FIXED_PERIOD	(10)            // 固定频率调用按键状态更新函数，括号内为调用周期，周期单位为ms
#define KEY_TIMES_MAX       (0xFF)          // 按键次数的最大值


typedef enum                                // 这个枚举类型在使用互斥信号量时，对按键状态访问的选择
{
	KEY_ACCESS_READ 	= 0x08,
	KEY_ACCESS_WRITE	= 0x80,
	KEY_ACCESS_CLEAR	= 0x40,
	KEY_ACCESS_DECREASE = 0x20,
	KEY_ACCESS_INCREASE = 0x10,
    KEY_ACCESS_REFRESH  = 0xc0              // 新增，刷新有按键按下标志，KEY_ACCESS_REFRESH = (KEY_ACCESS_WRITE | KEY_ACCESS_CLEAR)
}access_type;


typedef enum                                // 按键状态机
{
	KEY_DOWN 		    = 1,                // 按下
	KEY_UP	 		    = 2,                // 抬起
	KEY_UP_WOBBLE 	    = 3,                // 确认弹起消抖状态
	KEY_DOWN_WOBBLE     = 4                 // 确认按下消抖状态
}key_state_type;


typedef enum                                // 用来记录信号量状态
{
	KEY_SEM_USING       = 0,
	KEY_SEM_FREE        = 1
}key_sem_type;


typedef struct
{
	u8 (*get_state)(void);	                // 用于获取按键状态的函数
    
	#if (KEY_USE_SEM == 1)
        key_sem_type sem;				    // 按键互斥信号量
	#endif
    
	#ifdef  KEY_FIXED_PERIOD
        uint8_t time_ms;			        // 用于固定周期调用按键状态更新函数的计时
	#endif
    
	key_state_type state;                   // 按键状态机
	uint8_t times;				            // 按键被按下次数，按下并弹出后加1，使用后由应用程序减1
    
	#if (USER_DATA_EN == 1)
        uint8_t value;				        // 用户变量，可由用户任意使用
	#endif
}key_inf_type;


/************************************************************************************************************
**                            	函数外部声明
*************************************************************************************************************/
void Wp_KeyObjectInit(key_inf_type* key_this, u8(*getState)(void));
void Wp_KeyRefreshState(key_inf_type* theKey);
u8 Wp_KeyAccessTimes(key_inf_type* theKey, access_type option);
void Wp_KeyInit(void);


#endif
/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
