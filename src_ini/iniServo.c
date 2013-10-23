/*
 * iniServo.c
 * Created: 01.06.2012 15:02:52
 * Author: Admin
 */ 
#include "../include/servo.h"

u08 servo_need_update = 0;
u08 servo_state = 0;
u08 ServoPortState[MaxServos+1];
u08 ServoNextOCR[MaxServos+1];

void iniServo(void)
{
// Присваиваем указателям адреса наших структур
Servo_sorted[0] = &Servo[0];
Servo_sorted[1] = &Servo[1];
Servo_sorted[2] = &Servo[2];
Servo_sorted[3] = &Servo[3];
Servo_sorted[4] = &Servo[4];
Servo_sorted[5] = &Servo[5];

// Заполняем битмаски
Servo[0].Bit = 0b00000001;
Servo[1].Bit = 0b00000010;
Servo[2].Bit = 0b00000100;
Servo[3].Bit = 0b00001000;
Servo[4].Bit = 0b00010000;
Servo[5].Bit = 0b00100000;

// Выставляем все положения на нейтраль -- точно посредине диапазона. 
Servo[0].Position = 50;
Servo[1].Position = 50;
Servo[2].Position = 50;
Servo[3].Position = 50;
Servo[4].Position = 50;
Servo[5].Position = 50;
/* На таймер 1
Servo[0].Position = 194;
Servo[1].Position = 194;
Servo[2].Position = 194;
Servo[3].Position = 194;
Servo[4].Position = 194;
Servo[5].Position = 194;
*/
sortServo();
updServo();

TIMSK |= 1<<OCIE0;	
TCCR0 |= 0x04;
/* На таймере 1
TIMSK |= 1<<OCIE1A;				// разрешаем прерывания Timer/Counter1, Output Compare A Match Interrupt Enable
TCCR1B |= 0b00000011;			// устанавливаем предделитель CS11:0=1:1(Freq = clkT2S/64)
*/
}
