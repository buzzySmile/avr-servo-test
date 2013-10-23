//************************************************
//		    		intadc.c					//
//************************************************
#include "../include/ini.h"

ISR(ADC_ISR)			
{
	/*
	Disable_Interrupt;
	  OCR1B = (ICR1-(30*ADCH))*2/20;
	Enable_Interrupt;
	*/
}
