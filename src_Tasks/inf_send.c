//************************************************
//		Задача по миганию светодиода			//
//		 			Task #1						//
//************************************************
#include "../include/EERTOS.h"
#include "../include/_structs.h"
#include "../include/servo.h"

UA_INF Ua_InfBuff = {INF_BYTE_1, INF_BYTE_2,	// Начало
					 0xFF, 0xFF,		// 0 серв
					 0xFF, 0xFF,		// 1 серв
					 0xFF, 0xFF,		// 2 серв
					 0xFF, 0xFF,		// 3 серв
					 0xFF, 0xFF,		// 4 серв
					 0xFF, 0xFF };		// 5 серв

void inf_send (void)
{
	u08 ix;
	for (ix = 0; ix < MaxServos; ix++)
	{
		Ua_InfBuff.Servo[ix].Servo_Addr = ix;
		Ua_InfBuff.Servo[ix].Servo_pos = Servo[ix].Position;
	}
	ua_send(&Ua_InfBuff.First, sizeof(UA_INF), 50);

	/// Мигаем светодиодом, когда посылаем сообщение
	if( ((LED_PORT)&(1 << LED3)) == 0)        
       LED_PORT |= (1 << LED3);  // Turn on LED3
    else 
       LED_PORT &= ~(1 << LED3); // Turn off LED3
	        
	setTimerTask(inf_send,2000);
}
