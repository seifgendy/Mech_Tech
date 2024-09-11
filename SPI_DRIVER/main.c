/*
 * main.c
 *
 *  Created on: Oct 7, 2023
 *      Author: A&G Computer World
 */


/*
 * SPI_test.c
 *
 * Created: 10/6/2023 7:34:35 PM
 * Author : AMIT
 */

#define F_CPU 16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "SPI_interface.h"
#include "DIO_interface.h"
#include "GI_interface.h"

void action(u8 RxData);

int main(void)
{
    /* MASTER ECU */
	DIO_setPinDirection(DIO_PORTC,DIO_PIN2,DIO_PIN_OUTPUT);//LED0>>O/P
	DIO_setPinDirection(DIO_PORTB,DIO_PIN5,DIO_PIN_OUTPUT);//MOSI>>O/P
	DIO_setPinDirection(DIO_PORTB,DIO_PIN6,DIO_PIN_INPUT); //MISO>>I/P
	DIO_setPinDirection(DIO_PORTB,DIO_PIN7,DIO_PIN_OUTPUT);//SCK >>O/P
	DIO_setPinDirection(DIO_PORTB,DIO_PIN4,DIO_PIN_OUTPUT);//SS  >>O/P

	GI_enable();
	//u8 data;
	SPI_initMaster();
    while (1)
    {
		DIO_setPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_HIGH); //SS>>O/P HIGH
		_delay_ms(1);
		DIO_setPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_LOW); //SS>>O/P LOW
		/*SPI_transieve(54,&data);
		if(7 == data)
		{
			DIO_togglePinValue(DIO_PORTC,DIO_PIN2);
			_delay_ms(500);
		}*/

		SPI_transmitAsynchronous(54,&action);
		_delay_ms(2000);
    }
}


void action(u8 RxData)
{
	if(7 == RxData)
	{
		DIO_togglePinValue(DIO_PORTC,DIO_PIN2);

	}
}

