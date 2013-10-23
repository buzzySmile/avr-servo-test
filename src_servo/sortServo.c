/*
 * sortServo.c
 *
 * Created: 01.06.2012 15:06:47
 *  Author: Admin
 */
#include "../include/servo.h"

// Простейший алгоритм сортировки вставкой. Недалеко ушел от пузырька, но на столь малых количествах
// данных являетя наиболее эффективным. 
void sortServo(void) 
{
u08 i,k;
SArray_def *tmp;
// Сортируем массив указателей
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
