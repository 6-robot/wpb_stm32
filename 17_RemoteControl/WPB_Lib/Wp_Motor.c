/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_Motor.c
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
#include "Wp_Motor.h"


UPMOTOR_COMMAND_INFO_STRUCT str_motor_cmd;
UPMOTOR_DATA_INFO_STRUCT str_motor_reply;
WP_MOTOR_DATA_INFO_STRUCT motor_data[4];


/*************************************************************************************************************
** 函数名称:			Wp_SetMotorSpeed
**
** 函数描述:			设置某一电机的速度;
** 						motorid取值范围：1~4;
**					    
** 输入变量:			u8 motorid, long speed;
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
void Wp_SetMotorSpeed(u8 motorid, long speed)
{
	long temp = 0;
	u8 sendbuf[4] = {0};
    
    str_motor_reply.local_id = motorid;					                // 设备ID，暂定被动行走ID为0x02
    str_motor_reply.method_code = 0x00;
    str_motor_reply.parameter_length = 0x04;                            // 仅4个速度参数
    
    temp = speed;                                                       // 速度，速度数据在后
    memcpy(sendbuf, &temp, 4);
    str_motor_reply.parameter[0] = sendbuf[3];
    str_motor_reply.parameter[1] = sendbuf[2];
    str_motor_reply.parameter[2] = sendbuf[1];
    str_motor_reply.parameter[3] = sendbuf[0];
    
	str_motor_reply.p_para = &str_motor_reply.parameter[0];
    
    UART3TXEN;
    Wp_DelayUs(2);
    UpMotorSlaveTxPacket(&str_motor_reply);                             // 发送数据
    Wp_DelayUs(1);
    UART3RXEN;
}

void Motor_SetSpeed(u8 MotorID, float MotorSpeed)
{
	long nSpeed = (long)(MotorSpeed * 10);
	Wp_SetMotorSpeed(MotorID, nSpeed);
	DelayUs(3000);
}


/*************************************************************************************************************
** 函数名称:			Wp_ActiomMotorMode
**
** 函数描述:			执行指令;
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
void Wp_ActiomMotorMode(void)
{
    str_motor_reply.local_id = 0xFE;                                    // 设备ID，暂定被动行走ID为0x02
    str_motor_reply.method_code = 0x01;
    str_motor_reply.parameter_length = 0x00;
    
	str_motor_reply.p_para = &str_motor_reply.parameter[0];
    
    UART3TXEN;
    Wp_DelayUs(2);
    UpMotorSlaveTxPacket(&str_motor_reply);                             // 发送数据
    Wp_DelayUs(1);
    UART3RXEN;
}

void Motors_Action(void)
{
	Wp_ActiomMotorMode();
}


/*************************************************************************************************************************
** 函数名称:			UpMotorSlaveTxPacket
**
** 函数描述:			UpRobot从机数据包的组包(To String)、发送;
**                      返回上位机协议帧;
**
**
** 输入变量:			UPROBOT_DATA_INFO_STRUCT* p_uprobot_send;
** 返回值:				void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				律晔
** 创建日期:			2009-03-14
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void UpMotorSlaveTxPacket(UPMOTOR_DATA_INFO_STRUCT* p_uprobot_send)
{
	uint8_t count = 0;
	uint8_t check_sum = 0;
	
	Wp_Usart3_SendChar(0x55);													                // 开始位1、2
	Wp_Usart3_SendChar(0xAA);
	Wp_Usart3_SendChar(p_uprobot_send->local_id);												// 设备ID
    Wp_Usart3_SendChar(p_uprobot_send->method_code);	                                        // 控制字
	Wp_Usart3_SendChar(p_uprobot_send->parameter_length);										// 参数长度
	
	for(count = 0; count < (p_uprobot_send->parameter_length); count++)
	{
		Wp_Usart3_SendChar(p_uprobot_send->p_para[count]);										// 写数据组
	}
	
	check_sum = 0x55;
	check_sum += 0xAA;
	check_sum += p_uprobot_send->local_id;
	check_sum += p_uprobot_send->method_code;
	check_sum += p_uprobot_send->parameter_length;
    
	for(count = 0; count < (p_uprobot_send->parameter_length); count++)
	{
		check_sum += p_uprobot_send->p_para[count];											    // 校验和计算
	}
    
	Wp_Usart3_SendChar(check_sum);                                                              // 发送数据
    Wp_Usart3_SendChar(check_sum);                                                              // 需要发送两遍校验和，使用SN65HVD75，首次出现此问题
}


/*************************************************************************************************************************
** 函数名称:			UpMotorSlaveRxPacket
**
** 函数描述:			UpMotor从机字段解析(Parser);
**                      解析上位机发送协议帧;
**                      
**					    
** 输入变量:			BUFFER_QUEUE* p_usart_data, UPMOTOR_COMMAND_INFO_STRUCT* p_uprobot_receive;
** 返回值:				uint8;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				律晔
** 创建日期:			2009-03-14
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
uint8_t UpMotorSlaveRxPacket(BUFFER_QUEUE* p_usart_data, UPMOTOR_COMMAND_INFO_STRUCT* p_uprobot_receive)
{	
	static uint8_t count = 0;												// 循环次数计数器
	
	uint8_t temp_buffer = 0;												// 数据缓存
	uint8_t check_sum = 0;													// 校验和
	uint8_t check_sum_count = 0;
	
	while (1)
	{	
		if (TestEmptyBufferQueue(p_usart_data))								// 测试接收数据是否成功
		{
		//	recMotorpackflag = 0;
            
			return 0;
		}
		
		count++;
		
		OutBufferQueue(p_usart_data, &temp_buffer);							// 获取数据
		
		switch (count)
		{
			case 1:															// 匹配启动字1
			{
				if (0x55 != temp_buffer)
				{
					count = 0;
				}
				break;
			}
			case 2:															// 匹配启动字2
			{	
				if (0xAA != temp_buffer)
				{
					count = 0;
				}
				break;
			}
			case 3:															// 设备ID号
			{
				p_uprobot_receive->device_id = temp_buffer;
				break;
			}
            case 4:															// 控制字
			{
				p_uprobot_receive->method_code = temp_buffer;
				break;
			}
			case 5:															// 数据包长度
			{
				p_uprobot_receive->parameter_length = temp_buffer ;
				break;
			}
			default:
			{
				if (count < (6 + p_uprobot_receive->parameter_length))		// 保存参数
				{
					p_uprobot_receive->parameter[count - 6] = temp_buffer;
				}
				else														// 保存校验和
				{
					check_sum = 0x55;								        // 计算检验和
					check_sum += 0xAA;
					check_sum += p_uprobot_receive->device_id;			
                    check_sum += p_uprobot_receive->method_code;
					check_sum += p_uprobot_receive->parameter_length;
					for(check_sum_count = 0; check_sum_count < (p_uprobot_receive->parameter_length); check_sum_count++)
					{
						check_sum += p_uprobot_receive->parameter[check_sum_count];
					}
                    
					count = 0;												// 清计数器
                    
					if (check_sum == temp_buffer)
					{
                    //  recMotorpackflag = 1;
                        
						return 1;											// 无错误
					}
					else
					{
                    //  recMotorpackflag = 0;
                        
						return 0;											// 校验码错误
					}
				}
				break;
			}
		}
	}
    
//    return 0;																// 无效缓冲数据溢出            
}


/*************************************************************************************************************
** 函数名称:			Wp_Usart3_SendChar
**
** 函数描述:			字符发送函数;
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
void Wp_Usart3_SendChar(unsigned char c)
{
    USART_SendData(USART3, c);
    
    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}


/*************************************************************************************************************
** 函数名称:			Wp_Usart3_SendStr
**
** 函数描述:			字符串发送函数;
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
void Wp_Usart3_SendStr(char *str)
{
    while(*str)
    {
        USART_SendData(USART3, *str++);
		
        /* Loop until the end of transmission */
        while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
    }
}			


/*************************************************************************************************************
** 函数名称:			Wp_Usart3Configure
**
** 函数描述:			Uart3初始化函数;
** 						电机模块通讯接口;
**					    
** 输入变量:			u32 baud;
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
void Wp_Usart3Configure(u32 baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;
	
	// 使能串口3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	InitBufferQueue(&motor_rx_buffer, 255);						// 建立接收缓存
	
    // PB10-USART3_Tx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	   			// 推挽复用输出
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
    // PB11-USART3_Rx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       // 浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
 	UART3RXEN;													// 使能接收
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   		// 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			// 50M时钟速度
    GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = baud;				    // 波特率115200bps
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

    USART_ClockInit(USART3, &USART_ClockInitStructure);
    USART_Init(USART3, &USART_InitStructure);
    
    USART_Cmd(USART3, ENABLE);                                  // 使能串口3
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	            // 串口3使用接收中断
}


/*************************************************************************************************************
** 函数名称:			ReceiveUart3Hadler
**
** 函数描述:			自定义的Uart3接收中断服务函数;
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
void ReceiveUart3Hadler(u8 val)
{
    AddBufferQueue(&motor_rx_buffer, val);
}


/*************************************************************************************************************
** 函数名称:			UP_SetUART3Hadler
**
** 函数描述:			传递UART3数据接收中断入口函数;
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
void Wp_SetUART3Hadler(void (*ApplicationAddress)(u8))
{
	if (ApplicationAddress != 0)
		g_UP_Uart3ITAddress = (u32)ApplicationAddress;	
}


/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
