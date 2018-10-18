/*******************************************************Copyright*********************************************************

**-------------------------------------------------------文件信息---------------------------------------------------------
** 文件名称:			ConfigTypes.h
** 最后修订日期:		2008-11-12
** 最后版本:			1.0
** 描述:				变量类型定义，提供了控制寄存器的操作宏
**
**------------------------------------------------------------------------------------------------------------------------
** 创建人:				律晔
** 创建日期:			2008-07-24
** 版本:				1.0
** 描述:				与BDMC项目统一函数接口
**
**------------------------------------------------------------------------------------------------------------------------
** 修订人:				律晔
** 修订日期:			2009-08-02
** 版本:				1.1
** 描述:				与AVRGCC内的库统一操作宏接口
**
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
** 版本:
** 描述:
**
*************************************************************************************************************************/
#ifndef CONFIGTYPES_H_
#define CONFIGTYPES_H_


#include "stm32f10x.h"
#include <stdlib.h>
#include <stdio.h>


/*************************************************************************************************************************
**                                                  逻辑操作符定义
*************************************************************************************************************************/
//#ifndef FALSE
//  #define  FALSE  0                    /* Boolean value FALSE. FALSE is defined always as a zero value. */
//#endif
//#ifndef TRUE
//  #define  TRUE   1                    /* Boolean value TRUE. TRUE is defined always as a non zero value. */
//#endif

//#ifndef NULL
//  #define  NULL   0
//#endif


#define ERR_MASK		 0b00111111	   /* 错误位遮罩 */

#define ERR_OK           0             /* 正常 */
#define ERR_SPEED        1             /* 超过设备能够处理的速度 */
#define ERR_RANGE        2             /* 参数超出范围 */
#define ERR_VALUE        3             /* 参数的值不正确 */
#define ERR_OVERFLOW     4             /* 定时器溢出 */
#define ERR_MATH         5             /* 计算中溢出 */
#define ERR_ENABLED      6             /* 设备已启用 */
#define ERR_DISABLED     7             /* 设备已被禁用 */
#define ERR_BUSY         8             /* 器件忙 */
#define ERR_NOTAVAIL     9             /* 请求的值或方法无法使用 */
#define ERR_RXEMPTY      10            /* 接收缓存中无数据 */
#define ERR_TXFULL       11            /* 发射机已满 */
#define ERR_BUSOFF       12            /* 总线无法使用 */
#define ERR_OVERRUN      13            /* 溢出错误 */
#define ERR_FRAMING      14            /* 帧错误 */
#define ERR_PARITY       15            /* 奇偶错误 */
#define ERR_NOISE        16            /* 噪声误差 */
#define ERR_IDLE         17            /* 闲置错误 */
#define ERR_FAULT        18            /* 故障 */
#define ERR_BREAK        19            /* 在通讯中接受到打断符号 */
#define ERR_CRC          20            /* CRC等校验错误 */
#define ERR_ARBITR       21            /* 节点丢失仲裁 */
#define ERR_PROTECT      22            /* 保护 */
#define ERR_UNDERFLOW    23            /* 下溢出错误 */
#define ERR_UNDERRUN     24            /* 空栈读出错 */
#define ERR_COMMON       25            /* 设备常见故障 */
#define ERR_LINSYNC      26            /* 总线同步错误 */
#define ERR_DEPENDENCE   27            /* 模块依赖的设备没有启用 */

#define INIT_COMPLETE	 7			   /* 初始化完成标志位 */


#define _BV(bit) (1 << (bit))


/*************************************************************************************************************************
**                                                  SDK变量类型定义
*************************************************************************************************************************/
//typedef unsigned char bool;
typedef unsigned char byte;
typedef unsigned int word;
typedef unsigned long dword;

typedef unsigned       char    uint8;                               /* 无符号8位整型变量  */
typedef signed         char    int8;                                /* 有符号8位整型变量  */
typedef unsigned short int     uint16;                              /* 无符号16位整型变量 */
typedef signed   short int     int16;                               /* 有符号16位整型变量 */
typedef unsigned long  int     uint32;                              /* 无符号32位整型变量 */
typedef signed   long  int     int32;                               /* 有符号32位整型变量 */
typedef                float   fp32;                                /* 单精度浮点数（32位长度） */
typedef                double  fp64;                                /* 双精度浮点数（64位长度） */

typedef signed char    Word8;
typedef unsigned char  UWord8;
typedef short          Word16;
typedef unsigned short UWord16;
typedef long           Word32;
typedef unsigned long  UWord32;
typedef signed char    Int8;
typedef unsigned char  UInt8;
typedef int            Int16;
typedef unsigned int   UInt16;
typedef long           Int32;
typedef unsigned long  UInt32;
typedef int ibool;


/*************************************************************************************************************************
**                                                  SDK函数类型定义
*************************************************************************************************************************/
typedef void tVoidVoid(void);										// 返回值与参数都为void
typedef void tVoidUint8(uint8);										// 无返回，uint8参数
typedef void tVoidUint16(uint16);									// 无返回，uint16参数

typedef uint8 tUint8Void(void);										// 返回8位参数，无传递参数
typedef uint8 tUint8Uint8(uint8);									// 返回8位参数，uint8参数
typedef uint8 tUint8Uint16(uint16);									// 返回8位参数，uint16参数
typedef uint8 tUint8Puint8(uint8*);									// 返回8位参数，uint8*参数
typedef uint8 tUint8Puint16(uint16*);								// 返回8位参数，uint16*参数

typedef void tVoidUint8Uint8(uint8, uint8);							// 无返回，uint8，uint8参数
typedef void tVoidUint8Uint32(uint8, uint32);						// 无返回，uint8，uint32参数

typedef uint8 tUint8Uint8Uint8(uint8, uint8);						// 返回8位参数，uint8，uint8参数
typedef uint8 tUint8Uint8Puint8(uint8, uint8*);						// 返回8位参数，uint8，uint8*参数
typedef uint8 tUint8Uint8Puint16(uint8, uint16*);					// 返回8位参数，uint8，uint16*参数

typedef uint8 tUint8Uint8Uint8Uint16(uint8, uint8, uint16);			// 返回8位参数，uint8，uint8, uint16参数
typedef uint8 tUint8Uint8Uint16Uint16(uint8, uint16, uint16);		// 返回8位参数，uint8，uint16, uint16参数

typedef uint8 tUint8Uint8Puint16Puint16(uint8, uint16*, uint16*);	// 返回8位参数，uint8，uint16, uint16参数

typedef uint8 tUint8Uint8Uint8Puint16(uint8, uint8, uint16*);

typedef uint8 tUint8Uint8Uint8Puint16Puint16(uint8, uint8, uint16*, uint16*);

typedef uint8 tUint8Uint8Uint8Uint8(uint8, uint8, uint8);

typedef uint8 tPuint8Uint8Uint8Puint8(uint8*, uint8, uint8, uint8*);

typedef void tVoidPuint8Uint8(uint8*, uint8);
typedef uint8 tUint8Puint8Uint8(uint8*, uint8);

typedef uint8 tUint8Uint8Uint8Uint16Uint16(uint8, uint8, uint16, uint16);

typedef uint8 tUint8Uint8Uint16Uint16Puint16Puint16(uint8, uint16, uint16, uint16*, uint16*);


/*************************************************************************************************************************
**                                                  寄存器操作宏
*************************************************************************************************************************/
#define SetRegBit(reg, bit)                                     (reg |= _BV(bit))
#define ClrRegBit(reg, bit)                                     (reg &= ~_BV(bit))
#define GetRegBit(reg, bit)                                     (reg & _BV(bit))
#define SetReg(reg, val)                                        (reg = (uint8)(val))
#define GetReg(reg)                                             (reg)
#define SetRegBits(reg, mask)                                   (reg |= (uint8)(mask))
#define GetRegBits(reg, mask)                                   (reg & (uint8)(mask))
#define ClrRegBits(reg, mask)                                   (reg &= (uint8)(~(mask)))
#define SetRegMask(reg, maskAnd, maskOr)                        (reg = (uint8)((GetReg(reg) & ~(maskAnd)) | (maskOr)))
#define SetRegBitVal(reg, bit, val)                             ((val) == 0 ? (reg &= ~_BV(bit)) : (reg |= _BV(bit)))
#define ChangeRegBits(reg, mask)                                (reg ^= (mask))
#define ChangeRegBit(reg, bit)                                  (reg ^= _BV(bit))


/* 变量位长度修改宏 */
#define In16(var,l,h)  (var = ((word)(l)) | (((word)(h)) << 8))
#define In32(var,l,h)  (var = ((dword)(l)) | (((dword)(h)) << 16))

#define Out16(l,h,val) { h = (byte)((val) >> 8); l = (byte)(val); }
#define Out32(l,h,val) { h = (word)((val) >> 16); l = (word)(val); }

#define Output(P, V) SetReg(P,V)
#define Input(P) GetReg(P)


#endif
/*************************************************************************************************************************
**                                                      文件结束
*************************************************************************************************************************/
