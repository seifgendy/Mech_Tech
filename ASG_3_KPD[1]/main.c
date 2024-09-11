#define F_CPU 16000000UL
#include <util/delay.h>

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "KPD_interface.h"
#include "LCD_interface.h"








int main (){


	LCD_init() ;
	KPD_init();
    u8 key;
 int x  ;
 int  y  ;
long long int answer ;
u8 operation ;
u8 sc ;
	while(1)
	{


KPD_getValue(&key);


if(key != KPD_NOT_PRESSED)
{
	DIO_setPinDirection(DIO_PORTA,DIO_PIN3,DIO_PIN_OUTPUT);
	DIO_setPinValue(DIO_PORTA,DIO_PIN3,DIO_PIN_HIGH);
	_delay_ms(100);
	DIO_setPinValue(DIO_PORTA,DIO_PIN3,DIO_PIN_LOW);

	// display keypad value
	if (key == '0'){

		LCD_SendNumber4bit(key - '0');
		if (sc != 1 )
		{
			x = x * 10 + (key - '0');
		}
		else {
			y = y * 10 + (key - '0');
		}
			}




	else if(key == '1')
	{
		LCD_SendNumber4bit(key - '0');
if (sc != 1 )
{
	x = x * 10 + key - '0' ;
}
else {
	y = y * 10 + key - '0' ;
}



	}
	else if(key == '2')
		{
		LCD_SendNumber4bit(key - '0');
		if (sc != 1 )
		{
			x = x * 10 + key - '0' ;
		}
		else {
			y =  y * 10 + key - '0' ;
		}
		}
	else if(key == '3')
		{
		LCD_SendNumber4bit(key - '0');
		if (sc != 1 )
		{
			x =x * 10 + key - '0' ;
		}
		else {
			y = y * 10 +key - '0' ;
		}
		}

	else if(key == '4')
		{
		LCD_SendNumber4bit(key - '0');
		if (sc != 1 )
		{
			x = x * 10 +key - '0' ;
		}
		else {
			y =y * 10 + key - '0' ;
		}
		}

	else if(key == '5')
		{
		LCD_SendNumber4bit(key - '0');
		if (sc != 1 )
		{
			x = x * 10 +key - '0' ;
		}
		else {
			y = y * 10 +key - '0' ;
		}
		}

	else if(key == '6')
		{
		LCD_SendNumber4bit(key - '0' );
		if (sc != 1 )
		{
			x = x * 10 +key - '0' ;
		}
		else {
			y = y * 10 +key - '0' ;
		}
		}

	else if(key == '7')
		{
		LCD_SendNumber4bit(key - '0');
		if (sc != 1 )
		{
			x = x * 10 +key - '0' ;
		}
		else {
			y = y * 10 + key - '0' ;
		}
		}

	else if(key == '8')
		{
		LCD_SendNumber4bit(key - '0');
		if (sc != 1 )
		{
			x = x * 10 +key - '0' ;
		}
		else {
			y = y * 10 + key - '0' ;
		}

		}

	else if(key == '9')
		{
		LCD_SendNumber4bit(key - '0');
		if (sc != 1 )
		{
			x = x * 10 + key - '0' ;
		}
		else {
			y = y * 10 +key - '0' ;
		}

		}


	else if(key == '+')
			{
		 LCD_sendChar('+');
		 operation = 1 ;
		 sc = 1 ;
			}

	else if(key == '-')
				{
			 LCD_sendChar('-');
			 operation = 2 ;
			 sc = 1 ;
				}


	else if(key == '*')
				{
			 LCD_sendChar('*');
			 operation = 3 ;
			 sc = 1 ;
				}

	else if(key == '/')
				{
			 LCD_sendChar('/');
			 operation = 4 ;
			 sc = 1 ;
				}

	else if(key == 'D')
					{
		LCD_clear();
x = 0 ;
sc = 0 ;
operation = 0 ;
y = 0 ;
answer = 0 ;
					}



	else if(key == '=')
					{
				 LCD_sendChar('=');
				 switch (operation){

				 case 1 :
				 answer = x + y ;
				 LCD_SendNumber4bit(answer);
				 break ;

				 case 2 :
				 				 answer = x - y ;
				 				 LCD_SendNumber4bit(answer);
				 break ;


				 case 3 :
							 				 answer = x * y ;
							 				 LCD_SendNumber4bit(answer);
							 break ;


				 case 4 :
							 				 answer = x / y ;
							 				 LCD_SendNumber4bit(answer);
							 break ;


				 }
					}
	}
}
}
