//************************************************
//					main.c						//
//************************************************

#include "include/ini.h"
#include "include/EERTOS.h"

//==============================================================================
int main(void)
{
ini();			// Инициализируем периферию
iniServo();		// Инициализируем сервы
resetRTOS();	// Сбрасываем ядро
iniRTOS();		// Старт(инициализация) ядра. 

// Запуск фоновых задач.
Task2();
Task_setServo();
inf_send();

	while(1) 		// Главный цикл диспетчера
	{
		wdt_reset();	// Сброс собачьего таймера
		TaskManager();	// Вызов диспетчера
		// у приема байт по UART не меньший приоритет, чем у RTOS 
		if(FlagRecvCmd)
	 	{
			FlagRecvCmd = FLAG_DOWN;		
			// парсим буфер на наличие новой команды
			// при ее наличии вносим задачу в диспетчер	
			if(ua_cmd( &CmdBuff.First, sizeof( CmdBuff )) == 0)
			{}
				//setTask(Task_execCmd(&CmdBuff.First));
		}
	}

return 0;
}
