#include "../include/EERTOS.h"

u08 RingBuff[ UA_RING_BUFF_SIZE ];                // Кольцевой буфер для приема КОМАНДЫ
u08 *RingBuffByteAddr;                            // Адрес принятого байта в Кольцевом буфере
u08 RingBuffLastByteNumb = UA_RING_BUFF_SIZE - 1; // Порядковый номер последнего принятого байта в Кольцевом буфере

ISR(USART_RXC_vect)
 {     
	if( ++RingBuffLastByteNumb >= UA_RING_BUFF_SIZE ) 
    {
     RingBuffByteAddr = &RingBuff;  // Адрес принятого байта в Кольцевом буфере КОМАНДЫ
     RingBuffLastByteNumb = 0;      // Порядковый номер последнего принятого байта в Кольцевом буфере
    }
   else 
     RingBuffByteAddr++;            // Адрес принятого байта в Кольцевом буфере КОМАНДЫ

   *RingBuffByteAddr = UDR;       	// Прием байта на свободное место в Кольцевом буфере данных
    FlagRecvCmd = FLAG_UP;          // Бит - признак приема нового байта по Uart-0
 }
