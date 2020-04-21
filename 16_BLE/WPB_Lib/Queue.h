#ifndef QUEUE_H_
#define QUEUE_H_


#include "ConfigTypes.h"
#include "CfgTypes.h"
#include <stdlib.h>


#define		QUEUE_GLOBALS

#ifndef   QUEUE_GLOBALS
     #define QUEUE_EXT     
#else 
     #define QUEUE_EXT  extern
#endif 


/*************************************************************************************************************************
 * 												�ṹ�嶨��
*************************************************************************************************************************/
typedef struct SBufferQueue						// ���建����нṹ
{
	uint8 state;								// ����״̬
	uint8 length;								// ���г���

	uint8* init_address;						// �ռ��׵�ַ

	uint8* front;								// ��ͷָ��
	uint8* rear;								// ��βָ��
}BUFFER_QUEUE;


/*************************************************************************************************************************
                                                 ��������
*************************************************************************************************************************/
extern void InitBufferQueue(BUFFER_QUEUE *p_buffer, uint8 length);
extern uint8 TestEmptyBufferQueue(BUFFER_QUEUE *p_buffer);
extern void AddBufferQueue(BUFFER_QUEUE *p_buffer, uint8 item);
extern uint8 OutBufferQueue(BUFFER_QUEUE *p_buffer, uint8 *item);
extern uint8 CheckBufferQueueLength(BUFFER_QUEUE *p_buffer);
extern uint8 CheckBufferQueueState(BUFFER_QUEUE *p_buffer);
extern void ClearBufferQueue(BUFFER_QUEUE *p_buffer);


/*************************************************************************************************************************
                                                 �ṹ���ⲿ����
*************************************************************************************************************************/
QUEUE_EXT BUFFER_QUEUE str_rx_buffer;			// �������ջ�������UART1
QUEUE_EXT BUFFER_QUEUE ble_rx_buffer;           // �������ջ�������UART2
QUEUE_EXT BUFFER_QUEUE motor_rx_buffer;         // �������ջ�������UART3


#endif
/*************************************************************************************************************************
**                                                      �ļ�����
*************************************************************************************************************************/
