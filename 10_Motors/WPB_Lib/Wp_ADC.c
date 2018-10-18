/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_ADC.c
** 最后修订日期:  		2012-10-10
** 最后版本:			1.0
** 描述:				ADC初始化及模拟量数据处理文件;
**
**-----------------------------------------------------------------------------------------------------------
** 创建人:				吴康
** 创建日期:			2012-02-09
** 版本:				1.0
** 描述:				ADC初始化及模拟量数据处理文件;
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
#include "Wp_ADC.h"


/*************************************************************************************************************
** 函数名称:			Wp_AdcTempConfigure
**
** 函数描述:			ADC-温度传感器的配置;
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
/*
static void Wp_AdcTempConfigure(void)
{
    // 配置通道16的采样速度, 这里因为是测温, 不需要很快, 配置为最慢
    ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_239Cycles5);
    
    // 使能内部温度传感器的参考电压
    ADC_TempSensorVrefintCmd(ENABLE);
}
*/

/*************************************************************************************************************
** 函数名称:			Wp_AdcDMAConfigure
**
** 函数描述:			ADC-DMA的配置;
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
static void Wp_AdcDMAConfigure(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);                          // 允许DMA1
	
	DMA_DeInit(DMA1_Channel1);                                                  // 使用DMA通道1
	DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)(&(ADC1->DR));				// ADC1数据寄存器
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)g_ADValue;						// 获取ADC的数组，ADC采样值缓存
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;							// 片内外设作源头
	DMA_InitStructure.DMA_BufferSize = 16;										// 每次DMA16个数据
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			// 外设地址不增加
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;						// 内存地址增加
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	// 半字
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;			// 半字
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;								// 普通模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;							// 高优先级
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;								// 非内存到内存
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
//	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);								// DMA通道1传输完成中断
	
	DMA_Cmd(DMA1_Channel1, ENABLE);                                             // Enable DMA1 channel1 
}


/*************************************************************************************************************
** 函数名称:			Wp_AdcConfigure
**
** 函数描述:			ADC配置初始化;
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
void Wp_AdcConfigure(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
    
	Wp_AdcDMAConfigure();                                                   // DMA初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	                // 使能ADC外设
    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	// PA1~7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | 
                                  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// PB0~1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	// PC0~5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | 
                                  GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	// ADC1 
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;						// 规则同步模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;							// 连续多通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;						// 连续扫描
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		// 软件启动转换
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;					// 数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 16;								// 16个通道
	ADC_Init(ADC1, &ADC_InitStructure);
	
	// 配置通道16的采样速度,这里因为是测温,不需要很快,配置为最慢 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 2, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 3, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 4, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 5, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 6, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 7, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 8, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 9, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 10, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 11, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 12, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 13, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 14, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 15, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 16, ADC_SampleTime_239Cycles5);
	
	ADC_DMACmd(ADC1, ENABLE);                                               // 允许ADC1的DMA模式
	ADC_Cmd(ADC1, ENABLE);                                                  // 允许ADC1
	
	ADC_ResetCalibration(ADC1);                                             // 重置校准寄存器    
	while (ADC_GetResetCalibrationStatus(ADC1));
	
	ADC_StartCalibration(ADC1);                                             // 开始校准状态
	while (ADC_GetCalibrationStatus(ADC1));
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);                                 // 人工打开ADC转换
}


/*************************************************************************************************************
** 函数名称:			Wp_GetAdcChannelSamplingValue
**
** 函数描述:			获取ADC各通道采样值;
** 						Channel为输入通道只，取值范围：1~15;
**					    0通道为电源电压采集;
** 输入变量:			u8 Channel;
** 返回值:				u16;
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
u16 Wp_GetAdcChannelSamplingValue(u8 Channel)
{
	if (Channel < 16)
		return g_ADValue[Channel];
	else
		return 0;
}
int ADC_GetValue(u8 Channel)
{
	return Wp_GetAdcChannelSamplingValue(Channel);
}

/*************************************************************************************************************
** 函数名称:			Wp_GetChannelAdcVoltageValue
**
** 函数描述:			获取任意一个模拟输入端口电压值;
** 						
**					    
** 输入变量:			u8 channel;
** 返回值:				float;
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
float Wp_GetChannelAdcVoltageValue(u8 channel)
{
    u16 temp = 0;
    float channelvalue = 0.0;
    
    temp = Wp_GetAdcChannelSamplingValue(channel);      // 读取电池电压值，0通道为电源电压采集通道
    channelvalue = ((float)temp * 5.0) / 4096;          // 现在模拟信号输入端1/2分压，测量范围0~5V
    
    return channelvalue;
}

float ADC_GetVoltage(u8 Channel)
{
	return Wp_GetChannelAdcVoltageValue(Channel);
}

/*************************************************************************************************************
** 函数名称:			Wp_GetAdcVoltageValue
**
** 函数描述:			获取所有模拟输入端口电压值;
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
void Wp_GetAdcVoltageValue(void)
{
	u8 i = 0;
    u16 temp = 0;
    
    for (i = 0; i < 15; i++)
    {
        temp = Wp_GetAdcChannelSamplingValue(i+1);          // 读取电池电压值，0通道为电源电压采集通道
        analogvalue[i] = ((float)temp * 5.0) / 4096;        // 现在模拟信号输入端1/2分压，测量范围0~5V
    }
}


/*************************************************************************************************************
** 函数名称:			Wp_AdcGetAllIO
**
** 函数描述:			获取ADC所有通道的IO采样值;
** 						返回16路IO状态，16位无符号整形每一位对应一路;
**					    电源电压采样使用0通道，故0通道让出来不考虑;
** 输入变量:			void;
** 返回值:				u16;
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
u16 Wp_AdcGetAllIO(void)		
{
	u16 temp = 0;
	u8 i = 0;
    
	for (i = 0; i < 15; i++)
	{
		if (g_ADValue[i+1] > 2048)
			temp |= (0x01 << (i+1));
	}
    
	return temp;
}


/*************************************************************************************************************
** 函数名称:			Wp_AdcGetIO
**
** 函数描述:			获取ADC单个通道的IO采样值;
** 						输入通道1~15，返回0或1;
**					    电源电压采样使用0通道，故0通道让出来不考虑;
** 输入变量:			u8 channel;
** 返回值:				u8;
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
u8 Wp_AdcGetIO(u8 channel)
{
	return (g_ADValue[channel] > 500) ? 1 : 0;
}


/*************************************************************************************************************
** 函数名称:			Wp_GetPowerSamplingValue
**
** 函数描述:			获取电源电压采样值;
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
static void Wp_GetPowerSamplingValue(void)
{
	static u8 i = 0;
	
	powertemp[i] = Wp_GetAdcChannelSamplingValue(0);			// 读取电池电压值，0通道为电源电压采集通道
    
    i++;
	if (i >= 32)
		i = 0;
}


/*************************************************************************************************************
** 函数名称:			Wp_FilterPower
**
** 函数描述:			AD模拟量滤波并计算电压值;
** 						
**					    
** 输入变量:			void;
** 返回值:				float;
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
float Wp_FilterPower(void)
{
	u8 i = 0;
	u32 temp = 0;
	float power = 0.0;
	
    Wp_GetPowerSamplingValue();             // 获取采样值
    
	for (i = 0; i < 32; i++)                // 32级均值滤波
	{
		temp = temp + powertemp[i];
	}
    
	temp = temp >> 5;
	power = ((float)temp * 45.50) / 4096;   // 47.386
	power = power + 1.29;                   // 1.29为偏差值
    
	return power;
}


/*************************************************************************************************************
** 函数名称:			Wp_CalculateDistanceChannel
**
** 函数描述:			计算红外测距传感器输入某通道的距离值；
** 						返回距离值单位cm，单位mm;
**					    channel即为ADC通道值：1~15;
** 输入变量:			u8 channel;
** 返回值:				u16;
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
u16 Wp_CalculateDistanceChannel(u8 channel)
{
    float temp = 0.0;
    
    if (0 == channel && channel > 16)
        return 0;
    
    temp = analogvalue[channel - 1];
    if (temp > 3.14)
        return 60;
    else if (temp > 2.31 && temp <= 3.14)
    {
        return ((4.39 - temp)*4.8) * 10;
    }
    else if (temp > 1.31 && temp <= 2.31)
    {
        return ((3.31 - temp)*10) * 10;
    }
    else if (temp > 0.82 && temp <= 1.31)
    {
        return ((2.33 - temp)*20.4) * 10;
    }
    else if (temp > 0.61 && temp <= 0.82)
    {
        return ((1.135 - temp)*95.2) * 10;
    }
    else if (temp > 0.41 && temp <= 0.61)
    {
        return ((0.943 - temp)*150) * 10;
    }
    else if (temp <= 0.41)
    {
        return 800;
    }
    else
    {
        return 0;
    }
}

int Sensor_Distance(u8 Channel)
{
	return Wp_CalculateDistanceChannel(Channel);
}

/*************************************************************************************************************
** 函数名称:			Wp_CalculateLuxChannel
**
** 函数描述:			计算灰度传感器Lux值，单位10mLux;
** 						channel即为ADC通道值：1~15;
**					    
** 输入变量:			u8 channel;
** 返回值:				u16;
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
u16 Wp_CalculateLuxChannel(u8 channel)
{
    float temp = 0.00;
    
    if (0 == channel)
        return 0;
    
    temp = ((analogvalue[channel - 1]-0.99) * 10000) / 180;
    temp = temp * 100;
    
    return (u16)temp;
}

int Sensor_Lux(u8 Channel)
{
	return Wp_CalculateLuxChannel(Channel);
}

/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
