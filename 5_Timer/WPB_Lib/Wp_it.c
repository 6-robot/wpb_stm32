/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* stm32f10x_it.c
* 所有中断响应函数，一般如果中断比较简易，则直接在此编写，否则
* 可调用HAL模块中各自对应的处理函数处理中断。
* 09.7.3 改进为适应3.0库的中断名字,兼容HD系列的芯片.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "Wp_sys.h"


/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : NMIException
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMIException(void)
{
}

/*******************************************************************************
* Function Name  : HardFaultException
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFaultException(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : MemManageException
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManageException(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : BusFaultException
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFaultException(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : UsageFaultException
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFaultException(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : DebugMonitor
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMonitor(void)
{
}

/*******************************************************************************
* Function Name  : SVCHandler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVCHandler(void)
{
}

/*******************************************************************************
* Function Name  : PendSVC
* Description    : This function handles PendSVC exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSVC(void)
{
}

/*******************************************************************************
* Function Name  : SysTickHandler
* Description    : 系统时钟，一般调教到1MS中断一次
*******************************************************************************/
void SysTick_Handler(void)
{
	if (g_SysTickTimer)
		g_SysTickTimer--;
}

void EXTI_IRQHandler(u32 flag)
{
	if(g_UP_ExtiITAddress != 0)
		(*((void(*)(u32))g_UP_ExtiITAddress))(flag);
}

void EXTI0_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line0);
	EXTI_IRQHandler(EXTI_Line0);
}

void EXTI1_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line1);
	EXTI_IRQHandler(EXTI_Line1);
}

void EXTI2_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line2);
	EXTI_IRQHandler(EXTI_Line2);
}

void EXTI3_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line3);
	EXTI_IRQHandler(EXTI_Line3);
}

void EXTI4_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line4);
	EXTI_IRQHandler(EXTI_Line4);
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line5);
		EXTI_IRQHandler(EXTI_Line5);
	}
	else if(EXTI_GetITStatus(EXTI_Line6) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line6);
		EXTI_IRQHandler(EXTI_Line6);
	}
	else if(EXTI_GetITStatus(EXTI_Line7) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line7);
		EXTI_IRQHandler(EXTI_Line7);
	}
	else if(EXTI_GetITStatus(EXTI_Line8) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line8);
		EXTI_IRQHandler(EXTI_Line8);
	}
	else if(EXTI_GetITStatus(EXTI_Line9) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line9);
		EXTI_IRQHandler(EXTI_Line9);
	}
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line10) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line10);
		EXTI_IRQHandler(EXTI_Line10);
	}
	else if(EXTI_GetITStatus(EXTI_Line11) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line11);
		EXTI_IRQHandler(EXTI_Line11);
	}
	else if(EXTI_GetITStatus(EXTI_Line12) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line12);
		EXTI_IRQHandler(EXTI_Line12);
	}
	else if(EXTI_GetITStatus(EXTI_Line13) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line13);
		EXTI_IRQHandler(EXTI_Line13);
	}
	else if(EXTI_GetITStatus(EXTI_Line14) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line14);
		EXTI_IRQHandler(EXTI_Line14);
	}
	else if(EXTI_GetITStatus(EXTI_Line15) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line15);
		EXTI_IRQHandler(EXTI_Line15);
	}
}

void DMA1_Channel1_IRQHandler(void)             // ADC采集使用
{
	if (DMA_GetITStatus(DMA1_IT_TC1))           // 清DMA中断标志
 	{
		DMA_ClearITPendingBit(DMA1_IT_GL1);		// 清除全部中断标志
	}
}

void DMA1_Channel4_IRQHandler(void)             // UART1发送使用
{   
    DMA_ClearFlag(DMA1_FLAG_TC4);               // 清DMA中断标志
    
    DMA_Cmd(DMA1_Channel4, DISABLE);            // 关闭DMA
}   

void DMA1_Channel5_IRQHandler(void)             // UART1接收使用
{   
    DMA_ClearFlag(DMA1_FLAG_TC5);               // 清DMA中断标志
}

extern void Wp_Sev_TimerPro(void);
void TIM2_IRQHandler(void)
{
	Wp_Sev_TimerPro();                          // 系统伺服中断服务函数
}

extern void Wp_User_TimerPro(void);
void TIM3_IRQHandler(void)
{
	Wp_User_TimerPro();                         // 用户定时器中断入口函数
}

extern void Wp_Pwm_TimerPro(void);
void TIM4_IRQHandler(void)
{	
	Wp_Pwm_TimerPro();                          // 定时器4中断服务函数服务于PWM输出
}

void USART1_IRQHandler(void)
{
	// 接收中断
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
        
		if (g_UP_Uart1ITAddress != 0)
			(*((void(*)(u8))g_UP_Uart1ITAddress))(USART_ReceiveData(USART1));
	}
	
	// 溢出-如果发生溢出需要先读SR,再读DR寄存器 则可清除不断入中断的问题
	if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) == SET)
	{
		USART_ClearFlag(USART1, USART_FLAG_ORE);	    // 读SR
		USART_ReceiveData(USART1);				        // 读DR
	}
}

void USART2_IRQHandler(void)
{
	// 接收中断
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        
		if (g_UP_Uart2ITAddress != 0)
			(*((void(*)(u8))g_UP_Uart2ITAddress))(USART_ReceiveData(USART2));
	}
	// 溢出-如果发生溢出需要先读SR,再读DR寄存器 则可清除不断入中断的问题
	if (USART_GetFlagStatus(USART2, USART_FLAG_ORE) == SET)
	{
		USART_ClearFlag(USART2, USART_FLAG_ORE);	    // 读SR
		USART_ReceiveData(USART2);				        // 读DR
	}
}

void USART3_IRQHandler(void)
{
	// 接收中断
	if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
	{
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
        
		if (g_UP_Uart3ITAddress != 0)
			(*((void(*)(u8))g_UP_Uart3ITAddress))(USART_ReceiveData(USART3));
	}
    
	// 溢出-如果发生溢出需要先读SR,再读DR寄存器 则可清除不断入中断的问题
	if (USART_GetFlagStatus(USART3, USART_FLAG_ORE) == SET)
	{
		USART_ClearFlag(USART3, USART_FLAG_ORE);	    // 读SR
		USART_ReceiveData(USART3);				        // 读DR
	}
}

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
