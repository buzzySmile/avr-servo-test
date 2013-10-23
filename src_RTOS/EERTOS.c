//************************************************
//				Ядро диспетчера					//
//************************************************

#include "../include/EERTOS.h"

// определяем флаг таймаута
u08 FlagTimeout = 0;
// и флаг получения байта по UART
u08 FlagRecvCmd = 0;

// Очередь задач
// Тип данных - массив указателей на функции
volatile static TPTR	TaskQueue[TaskQueueSize+1];			// очередь указателей

// RTOS Подготовка-Инициализация. Очистка очередей
inline void resetRTOS(void)
{
 u08	index;

 for(index=0;index!=TaskQueueSize+1;index++)	// Во все позиции записываем Idle
	{
	TaskQueue[index] = Idle;
	}

 for(index=0;index!=MainTimerQueueSize+1;index++) // Обнуляем все таймеры.
	{
	MainTimer[index].GoToTask = Idle;
	MainTimer[index].Time = 0;
	}
}

// Функция установки задачи в очередь. Передаваемый параметр - указатель на функцию
// Отдаваемое значение - код ошибки.
void setTask(TPTR TS)
{

 u08		index = 0;
 u08		nointerrupted = 0;

 if (STATUS_REG & (1<<Interrupt_Flag))  // Если прерывания разрешены, то запрещаем их.
	{
	Disable_Interrupt;
	nointerrupted = 1;					// И ставим флаг, что мы не в прерывании. 
	}

 while(TaskQueue[index]!=Idle) 			// Прочесываем очередь задач на предмет свободной ячейки
	{									// с значением Idle - конец очереди.
	index++;
	if (index==TaskQueueSize+1) 		// Если очередь переполнена то выходим не солоно хлебавши
		{
		if (nointerrupted)	Enable_Interrupt; 	// Если мы не в прерывании, то разрешаем прерывания
		return;									// Раньше функция возвращала код ошибки - очередь переполнена. Пока убрал.
		}
	}
												// Если нашли свободное место, то
 TaskQueue[index] = TS;							// Записываем в очередь задачу
 if (nointerrupted) Enable_Interrupt;				// И включаем прерывания если не в обработчике прерывания.
}

/*=================================================================================
Диспетчер задач ОС. Выбирает из очереди задачи и отправляет на выполнение.
*/

inline void TaskManager(void)
{
u08		index=0;
TPTR	GoToTask = Idle;		// Инициализируем переменные

Disable_Interrupt;				// Запрещаем прерывания!!!
GoToTask = TaskQueue[0];		// Хватаем первое значение из очереди

if (GoToTask==Idle) 			// Если там пусто
	{
	Enable_Interrupt;			// Разрешаем прерывания
	(Idle)(); 					// Переходим на обработку пустого цикла
	}
else
	{
	for(index=0;index!=TaskQueueSize;index++)	// В противном случае сдвигаем всю очередь
		{
		TaskQueue[index]=TaskQueue[index+1];
		}

	TaskQueue[TaskQueueSize]= Idle;				// В последнюю запись пихаем затычку

	Enable_Interrupt;							// Разрешаем прерывания
	(GoToTask)();								// Переходим к задаче
	}
}
