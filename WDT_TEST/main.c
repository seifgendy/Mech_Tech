/*
 * WDT_test.c
 *
 * Created: 9/23/2023 11:39:56 PM
 * Author : Kareem Hussein
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "WDT_interface.h"
#include "DIO_interface.h"

int main(void)
{
    /* Replace with your application code */
	DIO_setPinDirection(DIO_PORTC,DIO_PIN2,DIO_PIN_OUTPUT);
	
	WDT_Start();
	DIO_setPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_HIGH);
	_delay_ms(1000);
	DIO_setPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_LOW);
    while (1) 
    {
    }
	WDT_Stop();
}

