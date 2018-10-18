/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_Globle.h
** 最后修订日期:  		2012-10-10
** 最后版本:			1.0
** 描述:				系统全局变量和函数;
**
**-----------------------------------------------------------------------------------------------------------
** 创建人:				吴康
** 创建日期:			2012-02-09
** 版本:				1.0
** 描述:				系统全局变量和函数;
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
#ifndef WP_GLOBLE_H
#define WP_GLOBLE_H


#include "stm32f10x.h"
#include "Wp_Key.h"


/************************************************************************************************************
**                            	外部变量声明
*************************************************************************************************************/
extern volatile u32 g_SysTickTimer;			// 1ms精确系统时钟计时器计数器（用户不可修改）

extern u32 g_UP_Uart1ITAddress;				// Uart1中断入口函数
extern u32 g_UP_Uart2ITAddress;				// Uart2中断入口函数
extern u32 g_UP_Uart3ITAddress;				// Uart3中断入口函数
extern u32 g_USR_UartReciever;
extern u32 g_USR_BleReciever;

extern u32 g_UP_ExtiFlag;					// 外部中断使能的通道
extern u32 g_UP_ExtiITAddress;				// 外部中断入口函数

extern bool g_UP_bTimerIT[4];				// 是否启用串口数据接收中断
extern u32 g_UP_iTimerTime[4];				// 计时周期
extern u32 g_UP_TimerITAddress;				// 定时器中断入口函数

extern u16 g_ADValue[16]; 					// 当前ADC值寄存器
extern float analogvalue[15];               // 各个通道电压值

extern u16 powertemp[32];					// AD采集值缓存，滤波用
extern float powervalue;					// 计算得到的电池电压值
extern float Sys_Voltage;
extern u16 powervalueint;                   // 滤波计算得到的电池电压值，单位mV

extern u16 positionvalue[3];				// 霍尔传感器值

extern u8 sendtemp[8];						// UART1发送缓存，DMA使用
extern u8 receivebuf[20];                   // UART1接收缓存，DMA使用

//extern u8 transparent_sign;		        // 透明传输标志
//extern u8 recflag;

extern u8 keyvalue;                         // 按键值，不同按键值OLED显示界面不同
extern key_inf_type key_up;
extern key_inf_type key_down;
extern key_inf_type key_back;
extern key_inf_type key_ok;

extern u8 gpioinputvalue;                   // 输入IO口的值
extern u8 gpiooutputvalue;                  // 输出IO口的值

extern char *blename;                       // 蓝牙模块名称

extern u8 oled_x;                           // OLED光标位置
extern u8 oled_y;

extern u16 exflashid;                       // 片外FLASH ID

extern u16 luxvalue[6];                     // 灰度传感器测量光通量值
extern float grayscaleSensor[6];            // 灰度传感器测量电压值
extern u16 infrareddistance[8];             // 红外传感器测距值，单位cm，测量范围10~80cm

extern int motorspeedbuffer[4];             // 四个电机模块的速度缓存


/************************************************************************************************************
**                            	外部函数声明
*************************************************************************************************************/
void get_ms(unsigned long *time);

void delay_us(u32 n);
void delay_ms(u32 n);

void Wp_DelayUs(u32 us);
void DelayUs(u32 us);
void Wp_Delay_ms(u32 ms);
void Wp_DelayMs(u32 us);
void DelayMs(u32 us);


#endif
/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
