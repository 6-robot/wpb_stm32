/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_HallSensor.c
** 最后修订日期:  		2012-10-10
** 最后版本:			1.0
** 描述:				读取霍尔传感器相关函数;
**
**-----------------------------------------------------------------------------------------------------------
** 创建人:				吴康
** 创建日期:			2012-02-09
** 版本:				1.0
** 描述:				读取霍尔传感器相关函数;
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
#include "Wp_HallSensor.h"


/*************************************************************************************************************
** 函数名称:			SendClk
**
** 函数描述:			传感器输入脉冲;
** 						输入变量为传感器编号1~3;
**					    
** 输入变量:			u8 num;
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
void SendClk(u8 num)
{
	switch (num)
	{
		case 1:
			Fir_CLK_H;
			break;
		case 2:
			Sec_CLK_H;
			break;
		case 3:
			Thi_CLK_H;
			break;
		default:
			break;
	}
	delay_us(1);
}


/*************************************************************************************************************
** 函数名称:			ReadPosition
**
** 函数描述:			读霍尔传感器函数;
** 						输入变量为传感器编号1~3;
**					    
** 输入变量:			u8 sensor_num;
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
u16 ReadPosition(u8 sensor_num)
{
	u16 positionvalue = 0;
	u8 tempvalue = 0;
	u8 i = 0;
	
	switch (sensor_num)
	{
		case 1:
		{
			Fir_CS_L;									// 拉低片选引脚
			delay_us(2);	
		
			Fir_CLK_L;
			delay_us(1);
			
			for (i = 0; i < 12; i++)
			{
				SendClk(1);
				tempvalue = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3);
				Fir_CLK_L;
				delay_us(1);
				
				positionvalue += tempvalue << (11 - i);
				positionvalue |= positionvalue;
				
				tempvalue = 0;
			}
			for (i = 0; i < 5; i++)
			{
				SendClk(1);
				Fir_CLK_L;
				delay_us(1);
			}
			Fir_CLK_H;
			delay_us(2);
			
			Fir_CS_H;									// 拉高片选引脚
			delay_us(2);
		}
			break;
		case 2:
		{
			Sec_CS_L;									// 拉低片选引脚
			delay_us(2);	

			Sec_CLK_L;
			delay_us(1);
			
			for (i = 0; i < 12; i++)
			{
				SendClk(2);
				tempvalue = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2);
				Sec_CLK_L;
				delay_us(1);
				
				positionvalue += tempvalue << (11 - i);
				positionvalue |= positionvalue;
				
				tempvalue = 0;
			}
			for (i = 0; i < 5; i++)
			{
				SendClk(2);
				Sec_CLK_L;
				delay_us(1);
			}
			Sec_CLK_H;
			delay_us(2);
			
			Sec_CS_H;									// 拉高片选引脚
			delay_us(2);
		}
			break;
		case 3:
		{
			Thi_CS_L;									// 拉低片选引脚
			delay_us(2);	

			Thi_CLK_L;
			delay_us(1);
			
			for (i = 0; i < 12; i++)
			{
				SendClk(3);
				tempvalue = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_15);
				Thi_CLK_L;
				delay_us(1);
				
				positionvalue += tempvalue << (11 - i);
				positionvalue |= positionvalue;
				
				tempvalue = 0;
			}
			for (i = 0; i < 5; i++)
			{
				SendClk(3);
				Thi_CLK_L;
				delay_us(1);
			}
			Thi_CLK_H;
			delay_us(2);
			
			Thi_CS_H;									// 拉高片选引脚
			delay_us(2);
		}
			break;
		default:
			break;
	}
	
	return positionvalue;
}


/*************************************************************************************************************
** 函数名称:			Wp_GetPositionValue
**
** 函数描述:			读霍尔传感器函数;
** 						输入变量为传感器编号1~3;
**					    
** 输入变量:			u8 sensor_num;
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
void Wp_GetPositionValue(void)
{
//	u8 i = 0;
	
	/*	读取霍尔传感器的值	*/
/*	for (i = 0; i < 3; i++)
	{
		positionvalue[i] = ReadPosition(1+i);
	}
*/
    positionvalue[0] = ReadPosition(1);
}


/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
