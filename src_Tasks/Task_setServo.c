#include "../include/servo.h"

//Sinus
u08 SinState=0;
const u08 SinTable[] PROGMEM = {76,74,68,60,50,41,33,27,26,29,35,43,53,62,70,75};

void Task_setServo(void)
{

setTimerTask(Task_setServo, 1000);			// Перезапуск задачи через с

if(Servo[1].Position > 75)
	Servo[1].Position = 30;
Servo[1].Position++;

	Servo[0].Position = pgm_read_byte(&SinTable[(SinState+3)&0x0F]);
//Servo[4].Position = pgm_read_byte(&SinTable[(SinState+4)&0x0F]);
//Servo[5].Position = pgm_read_byte(&SinTable[(SinState+5)&0x0F]);

SinState++;

sortServo();				// Сортируем таблицы
servo_need_update = 1;		// Запрос на обновление автомата
}
