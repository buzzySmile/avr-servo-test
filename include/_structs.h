#include "avrlibtypes.h"

#ifndef _structs_h
#define _structs_h

// 4х байтовая переменная произвольного типа
typedef union {
 s08      Char[ 4 ]; // Array of char
 u08     Uchar[ 4 ]; // Array of unsigned char
 s16       Int[ 2 ]; // Integer
 u16      Uint[ 2 ]; // Unsigned Integer
 s32           Long; // Long
 u32          Ulong; // Unsigned long
 float        Float; // Float
} VALUE;

typedef struct 	{
		u08 Position;	// позиция сервопривода
		u08 Bit;		// бит порта,который нам надо сбросить
		}  SArray_def;	
		
typedef struct {
 u08				  Servo_Addr; // Адрес сервомашинки
 u08				   Servo_pos; // Позиция сервомашинки
 //VALUE			   Servo_pos; // Позиция сервомашинки
} SERVO;

#define MaxServos			   6
/*! ------------------------------------------------------------------
** ПАКЕТ КОМАНДА
**------------------------------------------------------------------*/
#define CMD_BYTE_1          0xC1 // token-1
#define CMD_BYTE_2          0xC2 // token-2

//  КОМАНДА, принимаемая по Uart-1
typedef struct {
 u08                       First;
 u08                      Second;
 SERVO			Servo[MaxServos];
 //u08                 PWM_Speed; // Скорость позиционирования
 u08					checksum;
} UA_CMD;
#define UA_RING_BUFF_SIZE  sizeof( UA_CMD )

/*! ------------------------------------------------------------------
** ИНФОРМАЦИЯ
**------------------------------------------------------------------*/
#define INF_BYTE_1     		0xF1 // token-1
#define INF_BYTE_2     		0xF2 // token-2

typedef struct {
 u08                       First; // Первый байт
 u08                      Second; // Второй байт
 SERVO			Servo[MaxServos];
} UA_INF;

#endif
