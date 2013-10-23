/*
 * addServo.c
 *
 * Created: 01.06.2012 15:09:22
 *  Author: Admin
 */
#include "../include/servo.h" 

void addServo(u08 Number, u08 Pos)
{
u08 i,k;
SArray_def *tmp;

// Вписали новое значение
Servo[Number].Position = Pos;

// Сортируем массив
for(i=1;i<MaxServos;i++)
	{
	for(k=i;((k>0)&&(Servo_sorted[k]->Position < Servo_sorted[k-1]->Position));k--)
		{
		tmp = Servo_sorted[k];					// Swap [k,k-1] 
		Servo_sorted[k]=Servo_sorted[k-1];
		Servo_sorted[k-1]=tmp;
		}

	}

}
