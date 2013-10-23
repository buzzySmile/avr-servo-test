//************************************************
//			 Заголовочный файл ядра     		//
//************************************************

#ifndef EERTOS_H
#define EERTOS_H

#include "_structs.h"
#include "RTOScfg.h"

#define USART_RX_ISR		USART_RXC_vect	// USART_RXC_vect -- Rx Complete

#define FLAG_DOWN   	0 // Значение флага - сброшен
#define FLAG_UP     	1 // Значение флага - установлен

#define CHSUM_OFFSET 0x55 // Смещение для вычисления контрольной суммы

// Тип: Указатель-пустышка - Просто адрес, без типа
typedef void (*TPTR)(void);

volatile struct {									
				TPTR GoToTask; 			// Указатель перехода
				u16 Time;				// Выдержка в мс
				} MainTimer[MainTimerQueueSize+1];	// Очередь таймеров

//RTOS Errors Пока не используются.
#define TaskSetOk			 'A'
#define TaskQueueOverflow	 'B'
#define TimerUpdated		 'C'
#define TimerSetOk			 'D'
#define TimerOverflow		 'E'
#define ChecksumError		 'F'
#define CmdError		 	 'G'

extern u08 FlagTimeout;
extern u08 FlagRecvCmd;

extern void resetRTOS(void);
extern void Idle(void);

// UART connection
extern u08 RingBuff[ UA_RING_BUFF_SIZE ];
extern u08 *RingBuffByteAddr;
extern u08 RingBuffLastByteNumb;

extern UA_CMD CmdBuff;

extern void setTask(TPTR TS);
extern void setTimerTask(TPTR TS, u16 NewTime);
extern void killTimerTask(TPTR TS);

extern void TaskManager(void);

// Прототипы задач ============================================================
void Task1 (void);
void Task2 (void);
void Task_setServo(void);
void Task_execCmd(UA_CMD *);
void Task_Timeout(void);
u08 ua_send(u08*, u08, u16);
u08 ua_cmd(u08 *, u08);
void inf_send (void);

#endif
