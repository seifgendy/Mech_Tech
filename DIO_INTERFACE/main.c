/*
 * main.c

 *
 *  Created on: Sep 8, 2023
 *      Author: A&G Computer World
 */

#include <avr/io.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"


int main (){

	DIO_setPinDirection(DIO_PORTB,DIO_PIN0,DIO_PIN_INPUT);
	DIO_setPinDirection(DIO_PORTD,DIO_PIN2,DIO_PIN_INPUT);
	DIO_setPinDirection(DIO_PORTD,DIO_PIN6,DIO_PIN_INPUT);
	DIO_setPinDirection(DIO_PORTC,DIO_PIN2,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTC,DIO_PIN7,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTD,DIO_PIN3,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTA,DIO_PIN3,DIO_PIN_OUTPUT);
	u8 sw0,sw1,sw2 ;

	while(1)
	{

		DIO_getPinValue(DIO_PORTB,DIO_PIN0,&sw0);
		if(sw0 == 1)
		{

			DIO_togglePinValue(DIO_PORTC,DIO_PIN2);

		}



		DIO_getPinValue(DIO_PORTD,DIO_PIN2,&sw2);
				if(sw2 == 1)
				{

					DIO_togglePinValue(DIO_PORTD,DIO_PIN3);
	}

				DIO_getPinValue(DIO_PORTD,DIO_PIN6,&sw1);
						if(sw1 == 1)
						{

							DIO_setPinValue(DIO_PORTA,DIO_PIN3,DIO_PIN_HIGH);
							DIO_setPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_HIGH);
						}
							else {

								DIO_setPinValue(DIO_PORTA,DIO_PIN3,DIO_PIN_LOW);
								DIO_setPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_LOW);

							}
	}
}
