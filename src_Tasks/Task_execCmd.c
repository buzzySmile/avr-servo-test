//************************************************
//	   Task_execCmd - исполнение команды		//
//************************************************
#include "../include/EERTOS.h"
#include "../include/servo.h"


void Task_execCmd(UA_CMD *p_Cmd)
{
  u08 ix;
  for (ix = 0; ix < MaxServos; ix++)
	{
	  Servo[ix].Position = (*p_Cmd).Servo[ix].Servo_pos;
	}


sortServo();				// Сортируем таблицы
servo_need_update = 1;		// Запрос на обновление автомата
}
