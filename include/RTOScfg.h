#ifndef EERTOSHAL_H
#define EERTOSHAL_H
#include "ini.h"

// RTOS Config
#define RTOS_ISR  			TIMER2_COMP_vect
#define	TaskQueueSize		20
#define MainTimerQueueSize	15

extern void iniRTOS (void);

#endif
