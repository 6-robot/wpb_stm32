/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_OLED.h
** 最后修订日期:  		2012-10-10
** 最后版本:			1.0
** 描述:				OLED驱动函数;
**
**-----------------------------------------------------------------------------------------------------------
** 创建人:				吴康
** 创建日期:			2012-02-09
** 版本:				1.0
** 描述:				OLED驱动函数;
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
#ifndef WP_OLED_H
#define WP_OLED_H


#include "stm32f10x.h"
#include "Wp_Globle.h"


/************************************************************************************************************
**                            	宏定义
*************************************************************************************************************/
// 飞线版本
/*
#define OLED_SCL     GPIO_Pin_11      						// SCLK D0
#define OLED_SDA     GPIO_Pin_10      						// MOSI D1
#define OLED_RST     GPIO_Pin_8      						// RST
#define OLED_DC      GPIO_Pin_9      						// DC
*/
// 正常版本

#define OLED_SCL     GPIO_Pin_10      						// SCLK D0
#define OLED_SDA     GPIO_Pin_11      						// MOSI D1
#define OLED_RST     GPIO_Pin_9      						// RST
#define OLED_DC      GPIO_Pin_8      						// DC


#define OLED_D0_OL	 GPIO_ResetBits(GPIOD, OLED_SCL)	    // D0 IO口输出低电平
#define OLED_D0_OH	 GPIO_SetBits(GPIOD, OLED_SCL)  	    // D0 IO口输出高电平

#define OLED_D1_OL	 GPIO_ResetBits(GPIOD, OLED_SDA)	    // D1 IO口输出低电平
#define OLED_D1_OH	 GPIO_SetBits(GPIOD, OLED_SDA) 		    // D1 IO口输出高电平

#define OLED_RST_OL	 GPIO_ResetBits(GPIOD, OLED_RST)	    // RST IO口输出低电平
#define OLED_RST_OH	 GPIO_SetBits(GPIOD, OLED_RST) 		    // RST IO口输出高电平

#define OLED_DC_OL	 GPIO_ResetBits(GPIOD, OLED_DC)		    // DC IO口输出低电平
#define OLED_DC_OH	 GPIO_SetBits(GPIOD, OLED_DC) 		    // DC IO口输出高电平

#define XLevelL		 0x00
#define XLevelH		 0x10
#define XLevel		 ((XLevelH & 0x0F)*16 + XLevelL)
#define Max_Column	 132		                            // 1.3寸OLED实际的分辨率为132*64，实际使用128*64
#define Max_Row		 64
#define	Brightness	 0xCF
#define X_WIDTH 	 132		                            // 1.3寸OLED实际的分辨率为132*64，实际使用128*64
#define Y_WIDTH 	 64


/************************************************************************************************************
**                            	外部函数声明
*************************************************************************************************************/
void Wp_OledInit(void);														    // OLED初始化
void Wp_FillOled(void);												        // OLED满屏函数
void Wp_ClearOled(void);															// OLED清屏函数
void OLED_Clear(void);

void OLED_P6x8Char(u8 x, u8 y, char ch);                                            // 固定位置显示一小大字符
void OLED_P6x8Str(unsigned char x, unsigned char y, char ch[]);			            // 固定位置显示小字符串
void OLED_P8x16Char(u8 x, u8 y, char ch);                                           // 固定位置显示一个大字符
void OLED_P8x16Str(unsigned char x, unsigned char y, char ch[]);			        // 固定位置显示大字符串
void OLED_String(unsigned char X, unsigned char Y, char String[]);

void OLED_Dis6x8CharNum(unsigned char x, unsigned char y, unsigned char Number); 	// 显示小数字
void OLED_Dis8x16CharNum(unsigned char x, unsigned char y, unsigned char Number);	// 显示大数字

void Wp_DisIntNum(unsigned char x, unsigned char y, int num, unsigned char n);			    		            // 显示数字及位数
void OLED_Int(unsigned char X, unsigned char Y, int Value, unsigned char Lenght);
void Wp_Disfloat(unsigned char x, unsigned char y, float real, unsigned char n);						                // 显示浮点数
void Wp_DisfloatIntegerandDecimal(unsigned char x, unsigned char y, float real, unsigned char N1, unsigned char N2);    // 显示浮点数位数
void OLED_Float(unsigned char X, unsigned char Y, float Value, unsigned char IntPart, unsigned char FraPart);

void Wp_DisP16x16DotArray(unsigned char x, unsigned char y, unsigned char n);                                           // 显示汉字点阵
void Wp_DisP16x16HanZiArray(unsigned char x, unsigned char y, const unsigned char hanzi[], unsigned char n);


#endif
/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
