//************************************************
//		    		iniUSART.c					//
//************************************************
#include "../include/ini.h"

inline void iniUART( u08 ubrr)
{
/* //???*/
UCSRA = 0;

/* Set baud rate */
// Load upper 8-bits of the baud rate value into the high byte of the UBRR register
UBRRH = HI(ubrr);
// Load lower 8-bits of the baud rate value into the low byte of the UBRR register
UBRRL = LO(ubrr);

/* Turn on the transmission and reception circuitry */
UCSRB = (1<<RXEN)|(1<<TXEN);

// Use 8-bit character sizes - URSEL bit set to select the UCRSC register
/* ???? Set frame format: 8data, 2stop bit */
UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);

// Enable the USART Recieve Complete interrupt (USART_RXC)
UCSRB |= (1 << RXCIE); 
}
