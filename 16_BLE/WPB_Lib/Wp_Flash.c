/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_Flash.c
** 最后修订日期:  		2012-10-10
** 最后版本:			1.0
** 描述:				STM32内部Flash操作文件;
**
**-----------------------------------------------------------------------------------------------------------
** 创建人:				吴康
** 创建日期:			2012-02-09
** 版本:				1.0
** 描述:				STM32内部Flash操作文件;
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
#include "Wp_Flash.h"


WP_FLASH_INFO_STRUCT gflashConfig;
WP_FLASH_INFO_STRUCT greadflashConfig;


/*************************************************************************************************************
** 函数名称:			LoadConfigFromFLASH
**
** 函数描述:			读取FLASH内容;
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
void LoadConfigFromFLASH(void)
{
	 int i = 0;
	 
	 uint32_t flash_start_address = FLASH_START_ADDRESS; 

	 for (i = 0; i < CONFIG_ARRAY_SIZE; i++)
	 {
		  greadflashConfig.r[i] = (uint32_t)(*(volatile uint32_t*)(flash_start_address + 4*i));
	 }
}


/*************************************************************************************************************
** 函数名称:			WriteConfigurationToFlash
**
** 函数描述:			写FLASH内容;
** 						
**					    
** 输入变量:			void;
** 返回值:				int32_t;
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
int32_t WriteConfigurationToFlash(void)
{
    FLASH_Status FLASHStatus;
    uint32_t i = 0;

    uint32_t flash_start_address = FLASH_START_ADDRESS;

    FLASH_Unlock();                                // Flash解锁

    // Clear all pending flags
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
    
    // Erase FLASH page in preparation for write operation
    for (i = 0; i < CONFIG_ARRAY_SIZE; i++ )
    {
        FLASHStatus = FLASH_ErasePage(flash_start_address + 4*i);

        if( FLASHStatus != FLASH_COMPLETE )
        {
            FLASH_Lock();
            
            return FLASHStatus;
        }
    }
	 
    // Write configuration data
    for (i = 0; i < CONFIG_ARRAY_SIZE; i++ )
    {
        // Write FLASH data
        FLASHStatus = FLASH_ProgramWord(flash_start_address + 4*i, gflashConfig.r[i]);

        if (FLASHStatus != FLASH_COMPLETE)
        {
            FLASH_Lock();
            return FLASHStatus;
        }

        // Make sure new flash memory contents match
        if (gflashConfig.r[i] != (uint32_t)( *(volatile uint32_t*)(flash_start_address + 4*i)))
        {
            FLASH_Lock();
            return FLASH_TIMEOUT;
        }
    }
	 
	 FLASH_Lock();
	 
	 return FLASH_COMPLETE;
}


/*************************************************************************************************************
** 函数名称:			GetConfiguration
**
** 函数描述:			获取配置信息;
** 						FLASH与RAM不同，某处的FLASH为空则表示该FLASH内容为0xffffffff;
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
void GetConfiguration(void)
{
    if (FGET_FLASH_UNINITIALIZED())         // 判断是否为空，是否被写数据
    {
    	LED1_ON;
    //	ResetToFactory();                   // 恢复出厂设置
        WriteConfigurationToFlash();
    	Wp_Delay_ms(1000);
    	LED1_OFF;
    }
    else
    {
        LoadConfigFromFLASH();              // 读取FLASH数据
        
        LED1_ON;
        Wp_Delay_ms(100);
        LED1_OFF;
        Wp_Delay_ms(100);
        LED1_ON;
        Wp_Delay_ms(100);
        LED1_OFF;
    }
}


WP_FLASH_INFO_STRUCT gflashConfig = 
{
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9
};

WP_FLASH_INFO_STRUCT greadflashConfig = 
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
