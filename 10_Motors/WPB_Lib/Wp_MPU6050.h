/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_MPU6050.h
** 最后修订日期:  		2012-10-10
** 最后版本:			1.0
** 描述:				操作MPU6050_DMP相关;
**
**-----------------------------------------------------------------------------------------------------------
** 创建人:				吴康
** 创建日期:			2012-02-09
** 版本:				1.0
** 描述:				操作MPU6050_DMP相关;
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
#ifndef WP_MPU6050_H
#define WP_MPU6050_H


#include "stm32f10x.h"
#include <stdio.h>						// printf函数用
#include "stdlib.h"
#include <string.h>
#include "math.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "inv_mpu.h"
#include "Wp_UART.h"
#include "Wp_IIC.h"


/************************************************************************************************************
**                            	宏定义相关
*************************************************************************************************************/
/* Data requested by client. */
#define PRINT_ACCEL     (0x01)
#define PRINT_GYRO      (0x02)
#define PRINT_QUAT      (0x04)

#define ACCEL_ON        (0x01)
#define GYRO_ON         (0x02)

#define MOTION          (0)
#define NO_MOTION       (1)

/* Starting sampling rate. */
#define DEFAULT_MPU_HZ  (100)
#define FLASH_SIZE      (512)
#define FLASH_MEM_START ((void*)0x1800)

/*	Others	*/
#define q30  			1073741824.0f



typedef union UFloatConv
{
	unsigned long int temp_uint32;
	float temp_float;
}TYPE_CONV_UNION;


typedef struct WpDmpDataInfo
{
//	float q0 = 1.0f;
//	float q1 = 0.0f;
//	float q2 = 0.0f;
//	float q3 = 0.0f;
//	char *ptr;
	float Pitch;								// 欧拉角
	float Yaw;
	float Roll;
	unsigned long sensor_timestamp;
	short gyro[3];								// 陀螺
	short accel[3];								// 加计
	short sensors;								// 温度
	unsigned char more;
	long quat[4];								// 四元数
}WP_DMP_DATA_INFO_STRUCT;


/************************************************************************************************************
**                            	宏定义相关
*************************************************************************************************************/
extern TYPE_CONV_UNION type_conv;
extern WP_DMP_DATA_INFO_STRUCT wp_dmp_data;

/*
extern float q0, q1, q2, q3;
extern char *ptr;
extern float Pitch, Yaw, Roll;				// 欧拉角
extern unsigned long sensor_timestamp;
extern short gyro[3], accel[3], sensors;	// 陀螺，加计，温度
extern unsigned char more;
extern long quat[4];						// 四元数
*/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nCount);
/* Private functions ---------------------------------------------------------*/

struct rx_s {
    unsigned char header[3];
    unsigned char cmd;
};
struct hal_s {
    unsigned char sensors;
    unsigned char dmp_on;
    unsigned char wait_for_tap;
    volatile unsigned char new_gyro;
    unsigned short report;
    unsigned short dmp_features;
    unsigned char motion_int_mode;
    struct rx_s rx;
};
static struct hal_s hal = {0};

/* USB RX binary semaphore. Actually, it's just a flag. Not included in struct
 * because it's declared extern elsewhere.
 */
//volatile unsigned char rx_new;

/* The sensors can be mounted onto the board in any orientation. The mounting
 * matrix seen below tells the MPL how to rotate the raw data from thei
 * driver(s).
 * TODO: The following matrices refer to the configuration on an internal test
 * board at Invensense. If needed, please modify the matrices to match the
 * chip-to-body matrix for your particular set up.
 */
static signed char gyro_orientation[9] = {-1, 0, 0,
                                           0,-1, 0,
                                           0, 0, 1};

enum packet_type_e {
    PACKET_TYPE_ACCEL,
    PACKET_TYPE_GYRO,
    PACKET_TYPE_QUAT,
    PACKET_TYPE_TAP,
    PACKET_TYPE_ANDROID_ORIENT,
    PACKET_TYPE_PEDO,
    PACKET_TYPE_MISC
};


/************************************************************************************************************
**                            	外部函数声明
*************************************************************************************************************/
unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx);
void run_self_test(void);
void Wp_MPU6050DMP_Init(void);
void Wp_GetMpu6050Dmp(void);
float Gyro_GetPitch(void);
float Gyro_GetRoll(void);
float Gyro_GetYaw(void);


#endif
/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
