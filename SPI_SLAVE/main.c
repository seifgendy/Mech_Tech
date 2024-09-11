/*
 * SPI_slave_test.c
 *
 * Created: 10/6/2023 9:46:34 PM
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
	/* SLAVE ECU */
	DIO_setPinDirection(DIO_PORTC,DIO_PIN7,DIO_PIN_OUTPUT);//LED1>>O/P
    DIO_setPinDirection(DIO_PORTB,DIO_PIN5,DIO_PIN_INPUT); //MOSI>>I/P
    DIO_setPinDirection(DIO_PORTB,DIO_PIN6,DIO_PIN_OUTPUT);//MISO>>O	/P
    DIO_setPinDirection(DIO_PORTB,DIO_PIN7,DIO_PIN_INPUT); //SCK >>I/P
    DIO_setPinDirection(DIO_PORTB,DIO_PIN4,DIO_PIN_INPUT); //SS  >>I/P
	
	GI_enable();
	SPI_initSlave();
	//u8 data;
    while (1) 
    {
		/*SPI_transieve(7,&data);
		if(54 == data)
		{
			DIO_togglePinValue(DIO_PORTC,DIO_PIN7);
			_delay_ms(500);
		}*/
		
		SPI_transmitAsynchronous(7,&action);
		_delay_ms(2000);
    }
}


void action(u8 RxData)
{
	if(54 == RxData)
	{
		DIO_togglePinValue(DIO_PORTC,DIO_PIN7);
		
	}
}