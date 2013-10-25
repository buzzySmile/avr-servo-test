#include "../include/EERTOS.h"

// Передача пакета по Uart-0
u08 ua_send(       // Результат выполнения функции
 u08  *Address,     // Адрес передаваемого буфера данных
 u08  Quantity,     // Количество байтов передаваемого буфера данных
 u16  Timeout )    // Таймаут на передачу всего буфера данных, мс
{

// взводим флаг таймера
FlagTimeout = 0;
setTimerTask(Task_Timeout, Timeout);

// цикл посылки буфера в порт
while( Quantity != 0 )   			// будем крутиться в этом цыкле, пока подпрограмма прерываний 
  {									// не опустошит наш буфер данных, или до таймаута
	// Ожидание освобождения буфера передатчика
	while ( !( UCSRA & (1<<UDRE)) );
	// Помещение данных в буфер, отправка данных 
	UDR = *Address;
	Address++;
	Quantity--;
	  if( FlagTimeout ) 
	  {
	    return TimerOverflow;
	  } 	
  }
killTimerTask(Task_Timeout);
return TaskSetOk;
}
