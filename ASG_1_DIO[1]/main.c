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
#include <util/delay.h>

int main (){


	DIO_setPinDirection(DIO_PORTC,DIO_PIN2,DIO_PIN_OUTPUT);



	while(1)
	{



			DIO_togglePinValue(DIO_PORTC,DIO_PIN2);
			_delay_ms(500); // Delay for 500 milliseconds



	}
}
