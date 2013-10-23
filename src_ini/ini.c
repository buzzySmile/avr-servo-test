//************************************************
//			Аппартная абстракция проекта		//
//************************************************

#include "../include/ini.h"

inline void ini(void)
{
//IniPort
 //leds
LED_DDR |= (1<<LED1)|(1<<LED2)|(1<<LED3);
 //servos
SERVO_PORT = 0xFF;
SERVO_DDR = 0xFF;

//IniADC
//iniADC();

//IniUSART
iniUART(MYUBRR);

//Init PWM
//iniPWM();

//Init Interrupts


//Init Timers
TIMSK |= 1<<OCIE0;
TCCR0 |= 0x04;
/* На таймере 1
TIMSK |= 1<<OCIE1A;				// разрешаем прерывания Timer/Counter1, Output Compare A Match Interrupt Enable
TCCR1B |= 0b00000011;			// устанавливаем предделитель CS11:0=1:1(Freq = clkT2S/64)
*/
}



