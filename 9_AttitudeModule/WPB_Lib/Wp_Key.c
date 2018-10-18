/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_Key.c
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
#include "Wp_Key.h"


/*************************************************************************************************************
** 函数名称:			key_delay1ms
**
** 函数描述:			按键专用延时函数，大概一毫秒;
** 						
**					    
** 输入变量:			uint8_t nms;
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
#ifndef  KEY_FIXED_PERIOD
static void key_delay1ms(uint8_t nms)
{
	unsigned int i = 0;
    
	for(; nms > 0; nms--)
    {
		for(i = 400; i > 0; i--);
    }
}
#endif


/*************************************************************************************************************
** 函数名称:			KeyDown_state
**
** 函数描述:			检测按键输出电平状态;
** 						按下按键输出低电平，没有按下按键输出高电平;
**					    
** 输入变量:			void;
** 返回值:				uint8_t;
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
static u8 KeyUp_state(void)
{
    if (1 == CHECKKEYUP)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
static u8 KeyDown_state(void)
{
    if (1 == CHECKKEYDOWN)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
static u8 KeyBack_state(void)
{
    if (1 == CHECKKEYBACK)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
static u8 KeyOk_state(void)
{
    if (1 == CHECKKEYOK)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


/*************************************************************************************************************
** 函数名称:			Wp_KeyObjectInit
**
** 函数描述:			初始化一个按键对象;
** 						key_this：指向按键对象的指针;
**					    getState：状态检测函数指针;
**
** 输入变量:			key_inf_type* key_this, uint8_t(*getState)(void);
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
void Wp_KeyObjectInit(key_inf_type* key_this, u8(*getState)(void))
{
	key_this->get_state = getState;     // 按键状态获取入口函数
    
	key_this->state = KEY_DOWN;         // 初始化为按键按下有效
	key_this->times	= 0;                // 按键按下次数
    
	#if (USER_DATA_EN == 1)             // 不使能用户数据
        key_this->value	= 0;
	#endif
    
	#if (KEY_USE_SEM == 1)              // 不使能按键互斥信号量
        key_this->sem = KEY_SEM_FREE;
	#endif
    
	#ifdef  KEY_FIXED_PERIOD
        key_this->time_ms = 0;	        // 用于固定周期调用状态更新函数的计时
	#endif
}


/*************************************************************************************************************
** 函数名称:			Key_RefreshState
**
** 函数描述:			更新按键状态;
** 						调用频率：满足按键更新最快频率，一般要求调用频率在20HZ以上;
**					    
** 输入变量:			key_inf_type* theKey;
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
void Wp_KeyRefreshState(key_inf_type* theKey)
{
	#if KEY_USE_SEM == 1
	if (KEY_SEM_FREE == theKey->sem)
	{
		theKey->sem = KEY_SEM_USING;
	#endif
		switch (theKey->state)
		{
			case KEY_UP:
			{
				if ((*(theKey->get_state))())                // 获取电平状态
				{
					#ifdef  KEY_FIXED_PERIOD
                        theKey->time_ms = 0;
                        theKey->state = KEY_DOWN_WOBBLE;    // 进行消抖延时
					#else
					theKey->state = KEY_DOWN_WOBBLE;
                    
					key_delay1ms(KEY_WOBBLE_TIME);          // 去抖动
                    
					if ((*(theKey->get_state))())
					{
						theKey->state = KEY_DOWN;
					}
					#endif
				}
			}
            break;
			
			#ifdef  KEY_FIXED_PERIOD
			case KEY_DOWN_WOBBLE:
			{
				theKey->time_ms += KEY_FIXED_PERIOD;
				if(theKey->time_ms >=KEY_WOBBLE_TIME)
				{
					if((*(theKey->get_state))())
					{
						theKey->state = KEY_DOWN;
					}
                    else
					{
						theKey->state = KEY_UP;
					}
				}
			}
            break;
			#endif

			case KEY_DOWN:
			{
				if ((*(theKey->get_state))() == 0)
				{
					#ifdef  KEY_FIXED_PERIOD
                        theKey->time_ms = 0;
                        theKey->state = KEY_UP_WOBBLE;      // 进行消抖延时
					#else
					key_delay1ms(KEY_WOBBLE_TIME);
                    
					if ((*(theKey->get_state))() == 0)
					{
						theKey->state = KEY_UP;
						theKey->times++;
						if (theKey->times > 250)
                        {
							theKey->times = 1;             // 最多允许按下250次没处理
                        }
					}
					#endif
				}
			}
            break;

			#ifdef  KEY_FIXED_PERIOD
			case KEY_UP_WOBBLE:
			{
				theKey->time_ms += KEY_FIXED_PERIOD;
				if(theKey->time_ms >= KEY_WOBBLE_TIME)
				{
					if(0 == (*(theKey->get_state))())
					{
						theKey->state = KEY_UP;
						theKey->times++;
						if (theKey->times > 250)
							theKey->times = 250;            // 最多允许按下250次没处理
					}
                    else
					{
						theKey->state = KEY_DOWN;
					}
				}
			}
            break;
			#endif
		}
    
	#if KEY_USE_SEM == 1
		theKey->sem = KEY_SEM_FREE;
	}
	#endif
}


/*************************************************************************************************************
** 函数名称:			Key_AccessTimes
**
** 函数描述:			对按键值的访问，主要是封装对信号量的访问;
**                      option：选项;
**                      详见access_type定义，主要分read和write两类不可按位或；write有3种情况，不可按位或;
**					    如果只是读取则不用对option进行配置;
**                      如果是write类型的访问，则要KEY_ACCESS_WRITE位或上“KEY_ACCESS_CLEAR或者其它两个中的一个;
** 						调用频率：满足按键更新最快频率，一般要求调用频率在20HZ以上;
**					    返回值：->times的值;
**
** 输入变量:			key_inf_type* theKey, access_type option;
** 返回值:				uint8_t;
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
u8 Wp_KeyAccessTimes(key_inf_type* theKey, access_type option)
{
	u8 times_temp = 0;
	
	#if KEY_USE_SEM == 1
	if(KEY_SEM_FREE == theKey->sem)
	{
		theKey->sem = KEY_SEM_USING;
	#endif
	
        if ((option & KEY_ACCESS_WRITE) == KEY_ACCESS_WRITE)
        {
            if ((option & KEY_ACCESS_CLEAR) == KEY_ACCESS_CLEAR)
            {
                theKey->times = 0;			
            }
            if ((option & KEY_ACCESS_DECREASE) == KEY_ACCESS_DECREASE)
            {
                if (0 == theKey->times)
                {
                    theKey->times = theKey->times;
                }
                else
                {
                    (theKey->times)--;
                }
            }
            if ((option & KEY_ACCESS_INCREASE) == KEY_ACCESS_INCREASE)
            {
                if (KEY_TIMES_MAX == theKey->times)
                {
                    theKey->times = theKey->times;
                }
                else
                {
                    (theKey->times)++;
                }
            }
        }
		
        times_temp = theKey->times;
        
	#if KEY_USE_SEM == 1
		theKey->sem = KEY_SEM_FREE;
	}
	#endif
	
	return times_temp;
}


extern key_inf_type key_up;
extern key_inf_type key_down;
extern key_inf_type key_back;
extern key_inf_type key_ok;
/*************************************************************************************************************
** 函数名称:			Wp_GpioKeyInit
**
** 函数描述:			Gpio connect Key Init;
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
void Wp_KeyInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    
    /*  PD12, PD13, PD14, PD15默认按键输入口	    */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			// 上拉输入
	GPIO_Init(GPIOD, &GPIO_InitStructure);					// GPIOD初始化
    
    Wp_KeyObjectInit(&key_up, KeyUp_state);                 // 初始化一个按键对象
    Wp_KeyObjectInit(&key_down, KeyDown_state);             // 初始化一个按键对象
    Wp_KeyObjectInit(&key_back, KeyBack_state);             // 初始化一个按键对象
    Wp_KeyObjectInit(&key_ok, KeyOk_state);                 // 初始化一个按键对象
}


/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
