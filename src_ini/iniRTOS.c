#include "../include/RTOScfg.h"

//RTOS Запуск системного таймера
inline void iniRTOS (void)
{
TCCR2 |= 0b00001000;			// устанавливаем режим 1<<WGM21
								// WGM21:0=1:0 - Clear Timer on Compare(CTC)(Автосброс после достижения регистра сравнения)
TCCR2 |= 0b00000100;			// устанавливаем предделитель 1<<CS22(Freq = clkT2S/64)
								
TCNT2 = 0;						// Установить начальное значение счётчиков
OCR2  = LO(TimerDivider); 		// Установить значение в регистр сравнения
TIMSK |= 1<<OCIE2;				// Разрешаем прерывание RTOS - запуск ОС

Enable_Interrupt;		// Enable the Global Interrupt Enable flag so that interrupts can be processed
}
