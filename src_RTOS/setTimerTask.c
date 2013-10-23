//************************************************
//		 Функция установки задачи по таймеру 	//
//************************************************
#include "../include/EERTOS.h"

void setTimerTask(TPTR TS, 		// Указатель на функцию
				   u16 NewTime)	// Время выдержки в тиках системного таймера.
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
		MainTimer[index].Time = NewTime;			// Перезаписываем ей выдержку
		if (nointerrupted) 	Enable_Interrupt;		// Разрешаем прерывания если не были запрещены.
		return;										// Выходим. Раньше был код успешной операции. Пока убрал
		}
	}
	

for(index=0;index!=MainTimerQueueSize+1;++index)	// Если не находим похожий таймер, то ищем любой пустой	
	{
	if (MainTimer[index].GoToTask == Idle)		
		{
		MainTimer[index].GoToTask = TS;			// Заполняем поле перехода задачи
		MainTimer[index].Time = NewTime;		// И поле выдержки времени
		if (nointerrupted) 	Enable_Interrupt;	// Разрешаем прерывания
		return;									// Выход. 
		}
		
	}					
	// тут можно сделать return c кодом ошибки - нет свободных таймеров
}
