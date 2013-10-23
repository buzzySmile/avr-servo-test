//************************************************
//		 Функция установки задачи по таймеру 	//
//************************************************
#include "../include/EERTOS.h"

void killTimerTask(TPTR TS) 	// Указатель на функцию
{
u08		index=0;
u08		nointerrupted = 0;

if (STATUS_REG & (1<<Interrupt_Flag)) 			// Проверка запрета прерывания, аналогично функции выше
	{
	Disable_Interrupt;
	nointerrupted = 1;
	}


for(index=0;index!=MainTimerQueueSize+1;++index)	//Прочесываем очередь таймеров
	{
	if(MainTimer[index].GoToTask == TS)				// Если уже есть запись с таким адресом
		{
		MainTimer[index].GoToTask = Idle;			// Перезаписываем ей выдержку
		if (nointerrupted) 	Enable_Interrupt;		// Разрешаем прерывания если не были запрещены.
		return;										// Выходим. Раньше был код успешной операции. Пока убрал
		}
	}
Enable_Interrupt;
}
	
