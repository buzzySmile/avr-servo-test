//************************************************
//			Хидер аппартной абстракция			//
//************************************************

#ifndef INI_H
#define INI_H

//#include </usr/lib/avr/include/...>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include "avr/pgmspace.h"
#include "avrlibdefs.h"
#include "avrlibtypes.h"


//Clock Config
#define F_CPU 8000000L		// Clock Speed

//System Timer Config
#define Prescaler	  		64
#define	TimerDivider  		(F_CPU/Prescaler/1000)		// 1 mS


//USART Config
#define USART_BAUDRATE 9600L
#define MYUBRR (((F_CPU/(USART_BAUDRATE*16UL)))-1)
#define HI(x) ((x)>>8)
#define LO(x) ((x)& 0xFF)

//PORT Defines
#define LED1 		4
#define LED2		5
#define	LED3		7

#define LED_DDR		DDRD
#define LED_PORT 	PORTD

#define SERVO_DDR	DDRA
#define SERVO_PORT 	PORTA

#define STATUS_REG 			SREG
#define Interrupt_Flag		SREG_I
#define Disable_Interrupt	cli()
#define Enable_Interrupt	sei()

// Peripheral INT
#define ADC_ISR  			ADC_vect		// ADC_vect -- прерывание по завершению конверсии АЦП

// Функция инициализации
extern void ini(void);
extern void iniServo(void);
extern void iniADC(void);
extern void iniUART(u08);
//extern void iniPWM(void);

#endif
