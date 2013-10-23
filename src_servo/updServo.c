/*
 * updServo.c
 *
 * Created: 01.06.2012 15:08:08
 *  Author: Admin
 */ 
#include "../include/servo.h"

void updServo(void)
{
u08 i,j,k;

for(i=0,k=0;i<MaxServos;i++,k++)
{
	if(Servo_sorted[i]->Position != Servo_sorted[i+1]->Position)
	{
		ServoNextOCR[k] = Servo_sorted[i]->Position;
		ServoPortState[k+1] = Servo_sorted[i]->Bit;
	}
	else
	{
		ServoNextOCR[k] = Servo_sorted[i]->Position;
		ServoPortState[k+1] = Servo_sorted[i]->Bit;
		
		for(j=1;(Servo_sorted[i]->Position == Servo_sorted[i+j]->Position)&&(i+j<MaxServos);j++)
			{
				ServoPortState[k+1] |= Servo_sorted[i+j]->Bit;
			}
		i+=j-1;
	}
}	
ServoNextOCR[k] = 0xFF;
}
