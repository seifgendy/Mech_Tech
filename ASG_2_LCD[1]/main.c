/*

 * main.c
 *
 *  Created on: Sep 27, 2023
 *      Author: seif gendy
 */

#define F_CPU 16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "LCD_interface.h"
#include "DIO_interface.h"

int main(void)
{

	DIO_setPinDirection (DIO_PORTD, DIO_PIN2, DIO_PIN_INPUT);
	DIO_setPinDirection (DIO_PORTD, DIO_PIN6, DIO_PIN_INPUT);

	 LCD_init() ;

	 u8 PinValue ;
	 u8 PinValue2 ;
	 u8 num = 0 ;

    while (1)
    {
    	DIO_getPinValue                (DIO_PORTD, DIO_PIN2,  &PinValue);
    	DIO_getPinValue                (DIO_PORTD, DIO_PIN6,  &PinValue2);



    	if (PinValue == 1)
    	{
    		 LCD_clear();
    		num ++ ;
    		if ( num > 9){

    			num = 9 ;

    		}
    	 LCD_SendNumber4bit(num);

    	 while (PinValue == 1 )
    	 {
    		 DIO_getPinValue                (DIO_PORTD, DIO_PIN2,  &PinValue);
    	 }
    	 PinValue = NULL ;
    	}



        	if (PinValue2 == 1)
        	{
        		 LCD_clear();
        		num -- ;
        		if (num > 9  )
        		{
        			num = 0 ;
        		}
        	 LCD_SendNumber4bit(num);

        	 while (PinValue2 == 1 )
        	    	 {
        	    		 DIO_getPinValue                (DIO_PORTD, DIO_PIN6,  &PinValue2);
        	    	 }
        	    	 PinValue = NULL ;

        	}



    }
}


