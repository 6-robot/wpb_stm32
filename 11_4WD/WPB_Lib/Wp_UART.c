/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_UART.c
** 最后修订日期:  		2012-10-10
** 最后版本:			1.0
** 描述:				串口驱动文件;
**
**-----------------------------------------------------------------------------------------------------------
** 创建人:				吴康
** 创建日期:			2012-02-09
** 版本:				1.0
** 描述:				串口驱动文件;
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
#include "Wp_UART.h"


/*************************************************************************************************************
** 函数名称:			Wp_Usart1Configure
**
** 函数描述:			Uart1初始化函数;
** 						与上位机通讯接口;
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
void Wp_Usart1Configure(u32 baud)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;
	
	/*	USART1初始化	    */
	// 使能串口1，PA口，AFIO总线
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO | RCC_APB2Periph_USART1, ENABLE);
	
	InitBufferQueue(&str_rx_buffer, 200);										// 建立接收缓存
                                                                                // 接收缓存改为200字节后，测试没有死机
    // PA9-USART1_Tx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;								// 推挽输出-TX
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    // PA10-USART1_Rx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;						// 浮空输入-RX
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	UART1Cts_H;
    
	/* PA8作为Uart1CTS引脚  */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   						// 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							// 50M时钟速度
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
    USART_InitStructure.USART_BaudRate = baud;								    // 115200bps
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;					// 8bits
	USART_InitStructure.USART_StopBits = USART_StopBits_1;						// 1bit停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;							// 无校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

	USART_ClockInit(USART1, &USART_ClockInitStructure);
    USART_Init(USART1, &USART_InitStructure);
    
    USART_Cmd(USART1, ENABLE);                                                  // Enable the USART1
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                              // 串口1使用接收中断
}


/*************************************************************************************************************
** 函数名称:			Wp_Usart2Configure
**
** 函数描述:			Uart2初始化函数;
** 						BLE模块通讯接口;
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
void Wp_Usart2Configure(u32 baud)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;
	
	/*	USART2初始化	*/
	// 使能串口2，PD口，AFIO总线
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    
	GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE); 							// GPIO重映射函数
	
    InitBufferQueue(&ble_rx_buffer, 128);                                       // 建立缓冲区
    
    // PD5-USART2_Tx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;								// 推挽输出-TX
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    // PD6-USART2_Rx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;						// 浮空输入-RX
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    USART_InitStructure.USART_BaudRate = baud;							        // 115200bps
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;					// 8bits
	USART_InitStructure.USART_StopBits = USART_StopBits_1;						// 1bit停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;							// 无校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
	
	USART_ClockInit(USART2, &USART_ClockInitStructure);
    USART_Init(USART2, &USART_InitStructure);
    
    USART_Cmd(USART2, ENABLE);                                                  // Enable the USART2
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);                              // 串口2使用接收中断
}


/*************************************************************************************************************
** 函数名称:			USART1_Putc
**
** 函数描述:			发送单字符函数;
** 
**					          
** 输入变量:			unsigned char c;
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
void Wp_Usart1_SendChar(unsigned char c)
{
    USART_SendData(USART1, c);
	
	/* Loop until the end of transmission */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void UART_SendChar(unsigned char Value)
{
	Wp_Usart1_SendChar(Value);
}


/*************************************************************************************************************
** 函数名称:			Wp_Usart1_SendStr
**
** 函数描述:			发送字符串函数;
** 
**					          
** 输入变量:			char *str;
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
void Wp_Usart1_SendStr(char *str)
{
    while(*str)
    {
        USART_SendData(USART1, *str++);
		
        /* Loop until the end of transmission */
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
}

void UART_SendString(char String[])
{
	Wp_Usart1_SendStr(String);
}
/*************************************************************************************************************
** 函数名称:			Wp_Usart2_SendChar
**
** 函数描述:			发送单字符函数;
** 
**					          
** 输入变量:			unsigned char c;
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
void Wp_Usart2_SendChar(unsigned char c)
{
	USART_SendData(USART2, c);
	
	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
}


/*************************************************************************************************************
** 函数名称:			Wp_Usart2_SendStr
**
** 函数描述:			发送字符串函数;
** 
**					          
** 输入变量:			char *str;
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
void Wp_Usart2_SendStr(char *str)
{
    while(*str)
    {
        USART_SendData(USART2, *str++);
		
        /* Loop until the end of transmission */
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
    }
}


/*************************************************************************************************************
** 函数名称:			Wp_Usart1_SendInt
**
** 函数描述:			以字符的形式输出INT型数据;
** 
**					          
** 输入变量:			int16_t num;
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
void Wp_Usart1_SendInt(int16_t num)
{
	Wp_Usart1_SendChar(num >> 8);			        // 先发送高８位
	Wp_Usart1_SendChar((uint8_t)(num & 0xff));		// 再发送低８位
}


/*************************************************************************************************************
** 函数名称:			Wp_Usart2_SendInt
**
** 函数描述:			以字符的形式输出INT型数据;
**                      
**					    
** 输入变量:			int16_t num;
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
void Wp_Usart2_SendInt(int16_t num)
{
	Wp_Usart2_SendChar(num >> 8);			        // 先发送高８位
	Wp_Usart2_SendChar((uint8_t)(num & 0xff));		// 再发送低８位
}


/*************************************************************************************************************
** 函数名称:			ReceiveUart1Hadler
**
** 函数描述:			自定义的Uart1接收中断服务函数;
** 
**					    
** 输入变量:			u8 val;
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
void ReceiveUart1Hadler(u8 val)
{	
	AddBufferQueue(&str_rx_buffer, val);
	
	if (g_USR_UartReciever)
				(*((void(*)(u8))g_USR_UartReciever))(val);
}


/*************************************************************************************************************
** 函数名称:			ReceiveUart2Hadler
**
** 函数描述:			自定义的Uart2接收中断服务函数;
** 
**					          
** 输入变量:			u8 val;
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
void ReceiveUart2Hadler(u8 val)
{
  AddBufferQueue(&ble_rx_buffer, val);
	if (g_USR_BleReciever)
				(*((void(*)(u8))g_USR_BleReciever))(val);
}


/*************************************************************************************************************
** 函数名称:			Wp_SetUART1Hadler
**
** 函数描述:			传递UART1数据接收中断入口函数;
**                      
**					   	
** 输入变量:			void (*ApplicationAddress)(u8);
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
void Wp_SetUART1Hadler(void (*ApplicationAddress)(u8))
{
	if (ApplicationAddress != 0)
		g_UP_Uart1ITAddress = (u32)ApplicationAddress;
}

void UART_SetHandler(void (*HandlerName)(u8))
{
	if (HandlerName != 0)
		g_USR_UartReciever = (u32)HandlerName;
}


/*************************************************************************************************************
** 函数名称:			Wp_SetUART2Hadler
**
** 函数描述:			传递UART2数据接收中断入口函数;
**                      
**					   	
** 输入变量:			void (*ApplicationAddress)(u8);
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
void Wp_SetUART2Hadler(void (*ApplicationAddress)(u8))
{
	if (ApplicationAddress != 0)
		g_UP_Uart2ITAddress = (u32)ApplicationAddress;
}


void BLE_SetHandler(void (*HandlerName)(u8))
{
	if (HandlerName != 0)
		g_USR_BleReciever = (u32)HandlerName;
}

/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
