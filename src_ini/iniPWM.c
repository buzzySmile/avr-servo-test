//************************************************
//				Инициализация PWM				//
//************************************************
#include "../include/ini.h"

void iniPWM( )
{
/*
#if  F_CPU == 8000000
    ICR1 = 19999;
//---------------------------------
//| WGM13 | WGM12 | WGM11 | WGM10 |
//---------------------------------
//|   1   |   1   |   1   |   0   | - Fast PWM
//---------------------------------
// CS = 010 = 8x prescaling
TCCR1A = (1<<WGM11);
TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<<CS11);

#elif F_CPU == 16000000
    ICR1 =;
// 8x prescaling
TCCR1A = (1 << WGM11)
TCCR1B = (1 << WGM13) | (1<<WGM12) | (1 << CS10);

#else
#error    No F_CPU has been set or it is an unrecognised value
#endif
*/

TCCR1A = 0;     // disable all PWM on Timer1 whilst we set it up
ICR1 = 19999;   // frequency is every 20ms
// CS = 010 = 8x prescaling
TCCR1A = (1<<WGM11);
TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<<CS11);
/*Выставляем для обоих каналов ШИМ режим вывода ОС** сброс при совпадении. 
  COM1A1:COM1A0 = 1:0 и COM1B1:COM1B0 = 1:0*/
TCCR1A |= (1<<COM1A1)|(0<<COM1A0)|(1<<COM1B1)|(0<<COM1B0);
//we can now adjust the duty cycle of the output pin by setting OCR1A & OCR1B to a value between 0 and ICR1
OCR1A = ICR1 * 2 /20; // 2ms pulse to left motor on PD5
OCR1B = ICR1 * 2 /20; // 2ms pulse to right motor on PD4

}
