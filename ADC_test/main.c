/*
 * ADC_test.c
 *
 * Created: 9/8/2023 11:08:01 PM
 * Author : Kareem Hussein
 */ 


#define F_CPU 16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"


/* MCAL */
#include "ADC_interface.h"
#include "DIO_interface.h"

/* HAL */
#include "LCD_interface.h"


int main(void)
{
	/*DIO_setPinDirection(DIO_PORTC,DIO_PIN2,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTC,DIO_PIN7,DIO_PIN_OUTPUT);*/
	DIO_setPinDirection(DIO_PORTD,DIO_PIN3,DIO_PIN_OUTPUT);// DC
    DIO_setPinDirection(DIO_PORTA,DIO_PIN0,DIO_PIN_INPUT);
	LCD_init();
	ADC_init(ADC_REFERENCE_INTRNAL);//USE INTERNAL SINCE LM MAX IS 1500 MV
	
	u16 digitalVal,analogVal;
	u16 temp;
    while (1) 
    {
		ADC_getDigitalValue(ADC_CHANNEL_0,&digitalVal);
		
		analogVal = ((u32)digitalVal*2560UL)/1024; //U32 OR UL TO AVOID OVERFLOW SINCE THE PRODUCT OF MULTIPLICATION MAY BE MORE THAN MAX OF U16 SO I MADE THE CASTING
		
		
		// FAN control simple system
		temp = analogVal/10; //Data Sheet SINCE LM SENSTEVITY IS 10MV
		
		if (temp>25)
		{
			DIO_setPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_HIGH); // AC ON
			LCD_writeString((u8*)"temp is >> ");
			LCD_writeNumber(temp);
			_delay_ms(1000);
			LCD_clear();
		}
		else
		{
			DIO_setPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_LOW); // AC OFF
			LCD_writeString((u8*)"temp is >> ");
			LCD_writeNumber(temp);
			_delay_ms(1000);
			LCD_clear();
		}
		
		/* POT on LCD
		LCD_writeNumber(analogVal);
		LCD_writeString((u8*)" mv");
		_delay_ms(1000);
		LCD_clear();*/
		
		/* POT
		if(analogVal<1500)
		{
			DIO_setPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_HIGH);
			DIO_setPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_LOW);
			DIO_setPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_LOW);
		}
		else if(analogVal<3000)
		{
			DIO_setPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_LOW);
			DIO_setPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_HIGH);
			DIO_setPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_LOW);
		}
		else if(analogVal<4500)
		{
			DIO_setPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_LOW);
			DIO_setPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_LOW);
			DIO_setPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_HIGH);
		}
		else
		{
			DIO_setPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_LOW);
			DIO_setPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_LOW);
			DIO_setPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_LOW);
		}*/
    }
}

