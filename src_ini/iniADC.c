//************************************************
//				Инициализация АЦП				//
//************************************************
#include "../include/ini.h"

inline void iniADC(void)
{
// set the prescalar for the ADC (must be 50…200кГц)
// this prescalar needs to be set so that the ADC input frequency is between 50 KHz and 200 KHz. 
// The ADC clock is derived from the system clock. With a system frequency of 16 MHz, 
// a prescaler of 128 will result in an ADC frequency of 125 Khz.
ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
// set the ADC reference voltage
ADMUX |= (1 << REFS0);
// using ADC0 here, which corresponds with all 5 MUX bits being zero
// -ADMUX = ...
// Разрешаем прерывания.
ADCSRA |= (1 << ADIE);
// setting the ADLAR bit in the ADMUX register, we can left align the ADC value. 
// This puts the highest 8 bits of the measurement in the ADCH register, with the rest in the ADCL register.
ADMUX |= (1 << ADLAR);
// Непрерывные последовательные преобразования, одно за другим.
// ADATE: ADC Auto Trigger Enable
ADCSRA |= 1<<ADATE;
//To enable the ADC, set the ADEN bit in ADCSRA:
ADCSRA |= (1 << ADEN);
// To start the ADC measurements, the ADSC bit in ADCSRA needs to be set:
ADCSRA |= (1 << ADSC);

//ADC Auto Trigger Source
//ADTS2 ADTS1 ADTS0 	Trigger Source
//  0 	  0		0 		Free Running mode(Initial Value)

}
