/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_Dma.c
** 最后修订日期:  		2012-10-10
** 最后版本:			1.0
** 描述:				DMA初始化文件;
**
**-----------------------------------------------------------------------------------------------------------
** 创建人:				吴康
** 创建日期:			2012-02-09
** 版本:				1.0
** 描述:				DMA初始化文件;
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
#include "Wp_Dma.h"


/*************************************************************************************************************
** 函数名称:			Wp_Uart1RxDmaInit
**
** 函数描述:			UART1接收数据DMA初始化;
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
void Wp_Uart1RxDmaInit(void)
{
    DMA_InitTypeDef DMA_InitStructure;
    
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    
	DMA_DeInit(DMA1_Channel5);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);				// 源头BUF
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)(&receivebuf[0]);				// 目标BUF
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;							// 外设作源头
	DMA_InitStructure.DMA_BufferSize = 62;										// BUF大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			// 外设递增模式禁止
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;						// 内存地址递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;		// 外设字节为单位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			    // 内存字节为单位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;								// 循环模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;							// 4优先级之一的(高优先)
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;								// 非内存到内存
	DMA_Init(DMA1_Channel5, &DMA_InitStructure);
	
    DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);								// DMA5传输完成中断  
    
    USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);                              // 采用DMA方式接收  
	
	DMA_Cmd(DMA1_Channel5, ENABLE);												// 使能DMA，正式允许DMA    
}


/*************************************************************************************************************
** 函数名称:			Wp_Uart1TxDmaInit
**
** 函数描述:			UART1发送数据DMA初始化;
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
void Wp_Uart1TxDmaInit(void)  
{   
    DMA_InitTypeDef DMA_InitStructure;  
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    
    /* DMA channel4 Configuration */
    DMA_DeInit(DMA1_Channel4);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);          // 外设地址
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)(&sendtemp[0]);             // 串口发送缓存
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;                      // 外设作为目的地址
    DMA_InitStructure.DMA_BufferSize = 62;                                  // BufferSize，缓存大小
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        // 外设递增模式禁止
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 // 内存地址自增
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // 传输方式：字节
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         // 内存存储方式：字节 
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                         // DMA工作模式，只传输一次
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;                     // 4优先级之一的(高优先)
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            // 非内存到内存
    DMA_Init(DMA1_Channel4, &DMA_InitStructure);  
    
    /* Enable DMA Channel4Transfer Complete interrupt */  
    DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);                         // 使能发送完成中断
    
    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);                          // 采用DMA方式发送
    
//  USART_Cmd(USART1, ENABLE);                                              // 启动串口
    
    DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);                         // 传输完成则进入DMA中断
}


/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
