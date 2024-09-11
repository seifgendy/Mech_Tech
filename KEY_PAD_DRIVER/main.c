#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "KPD_interface.h"

int main (){
	DIO_setPinDirection(DIO_PORTC,DIO_PIN2,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTC,DIO_PIN7,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTD,DIO_PIN3,DIO_PIN_OUTPUT);


	KPD_init();
u8 key;


	while(1)
	{


KPD_getValue(&key);


if(key != KPD_NOT_PRESSED)
{
// display keypad value
	if (key == '0'){
		DIO_setPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_HIGH);
			DIO_setPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_LOW);
			DIO_setPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_LOW);

	}

	else if(key == '1')
	{
		DIO_setPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_LOW);
					DIO_setPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_HIGH);
					DIO_setPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_LOW);

	}
	else if(key == '2')
		{
		DIO_setPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_LOW);
					DIO_setPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_LOW);
					DIO_setPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_HIGH);

		}
	else if(key == '3')
		{
		DIO_setPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_HIGH);
					DIO_setPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_HIGH);
					DIO_setPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_HIGH);

		}
	else{

		DIO_setPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_LOW);
							DIO_setPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_LOW);
							DIO_setPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_LOW);

	}
}


	}
}


