#include "../include/EERTOS.h"

// командный пакет
UA_CMD CmdBuff;

u08 ua_cmd(         // Результат выполнения функции
 u08 *CmdBuffAddr, 	// Адрес буфера КОМАНДЫ
 u08 CmdBuffSize )   // Размер буфера (длина) КОМАНДЫ
{
 u08 iy, ix;                                    // Локальный индекс
 u08 TmpBuff[ UA_RING_BUFF_SIZE ];      		// Временный Буфер
 u08 *p_TmpBuff = &TmpBuff[0];
 u08 RecpRes;                          			// Результат приема
 u08 CmdCheckSum = CHSUM_OFFSET;             	// Контрольная сумма найденной КОМАНДЫ

// Инициализация КОМАНДЫ байтами, соответствующими ее отсутствию
 memset( CmdBuffAddr, 0xFF, CmdBuffSize ); 

// Анализ затребованного размера буфера для КОМАНДЫ
 if( CmdBuffSize > UA_RING_BUFF_SIZE)
  return( -1 );

// Копирование последних принятых CmdBuffSize байт из Кольцевого буфера во временный буфер
 Disable_Interrupt;
 // Копировать будем с хвоста
 iy = RingBuffLastByteNumb;       				// Порядковый номер последнего принятого байта в Кольцевом буфере
 p_TmpBuff += CmdBuffSize - 1;      			// Адрес последнего элемента буфера для приема КОМАНДЫ

 for( ix = 0; ix < CmdBuffSize; ix++ ) {
  *p_TmpBuff-- = RingBuff[ iy ];
  if( iy-- == 0 )
   iy = UA_RING_BUFF_SIZE - 1;
 }
 Enable_Interrupt;

// Поиск КОМАНДЫ во временном буфере ...
 if( (TmpBuff[0] == CMD_BYTE_1) && (TmpBuff[1] == CMD_BYTE_2) ) 
 {
	for( iy = 0; iy < CmdBuffSize; iy++ ) 
	{
	*( CmdBuffAddr + iy ) = TmpBuff[iy];        // Очередной байт - в КОМАНДУ
	CmdCheckSum += *( CmdBuffAddr + iy );       // Очередной байт - в контрольную сумму
	}

  if( CmdCheckSum == 0 )
   return 0;
  else
   return( ChecksumError );
 }
 else
  return( CmdError );
}
