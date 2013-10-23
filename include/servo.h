/*
 * servo.h
 *
 * Created: 01.06.2012 14:44:57
 *  Author: Admin
 */ 
#include "../include/_structs.h"
#include "../include/ini.h"

#ifndef SERVO_H_
#define SERVO_H_

#define SERVO_ISR			TIMER0_COMP_vect

SArray_def Servo[MaxServos];
SArray_def *Servo_sorted[MaxServos];

extern u08 servo_need_update;
extern u08 servo_state;
extern u08 ServoPortState[MaxServos+1];
extern u08 ServoNextOCR[MaxServos+1];
//--------------------------
extern void sortServo(void);
extern void updServo(void);
extern void addServo(u08 Number, u08 Pos);

#endif /* SERVO_H_ */
