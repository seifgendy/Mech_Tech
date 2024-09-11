


#define F_CPU 16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"


void LCD_init(void)
{
	// Intialize LCD pins As OutPut Pins
	DIO_setPinDirection(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_RW_PORT, LCD_RW_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_D4_PORT, LCD_D4_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_D5_PORT, LCD_D5_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_D6_PORT, LCD_D6_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_D7_PORT, LCD_D7_PIN, DIO_PIN_OUTPUT);

	_delay_ms(35);

	// set Rs pin = 0 (write command)
	DIO_setPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_LOW);
	// set Rw pin = 0 (write)
	DIO_setPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_PIN_LOW);
	private_writeHalfPort(0b0010);
	/* Enable Pulse *//* H => L */
	DIO_setPinValue(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_LOW);
    // Function Set command 2*16 LCD , 4 Bit Mode
	LCD_sendCmnd(0b00101000);
	_delay_us(45);

	// Display on off Control (DisplayOn, Cursor on, Blink on)
	LCD_sendCmnd(0b00001111);
	_delay_us(45);

	// Clear Display
	LCD_sendCmnd(0b00000001);
	_delay_ms(2);

	LCD_sendCmnd(0b00000110);
}

void LCD_sendCmnd(u8 Cmnd)
{
	// set Rs pin = 0 (write command)
	DIO_setPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_LOW);

	// set Rw pin = 0 (write)
	DIO_setPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_PIN_LOW);

	// Write The Most 4 bits Of command on Data Pins
	private_writeHalfPort(Cmnd>>4);

	/* Enable Pulse *//* H => L */
	DIO_setPinValue(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_LOW);

	// Write The Least 4 bits Of command on Data Pins
	private_writeHalfPort(Cmnd);

	/* Enable Pulse *//* H => L */
	DIO_setPinValue(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_LOW);
}


void LCD_sendChar(u8 data)
{
	// set Rs pin = 1 (write data)
	DIO_setPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_HIGH);

	// set Rw pin = 0 (write)
	DIO_setPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_PIN_LOW);

	// Write The Most 4 bits Of data on Data Pins
	private_writeHalfPort(data>>4);

	/* Enable Pulse *//* H => L */
	DIO_setPinValue(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_LOW);

	// Write The Least 4 bits Of data on Data Pins
	private_writeHalfPort(data);

	/* Enable Pulse *//* H => L */
	DIO_setPinValue(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_LOW);
}


void LCD_writeString(u8* String)
{
	u8 counter=0;
	while(String[counter]!='\0')
	{
		LCD_sendChar(String[counter]);
		++counter;
	}
}


void LCD_clear(void)
{
	// Clear Display
	LCD_sendCmnd(0b00000001);
	_delay_ms(2);
}


static void private_writeHalfPort(u8 value)
{
	if(GET_BIT(value,0) == 1)
	{
		DIO_setPinValue(LCD_D4_PORT, LCD_D4_PIN, DIO_PIN_HIGH);
	}
	else
	{
		DIO_setPinValue(LCD_D4_PORT, LCD_D4_PIN, DIO_PIN_LOW);
	}

	if(GET_BIT(value,1) == 1)
	{
		DIO_setPinValue(LCD_D5_PORT, LCD_D5_PIN, DIO_PIN_HIGH);
	}
	else
	{
		DIO_setPinValue(LCD_D5_PORT, LCD_D5_PIN, DIO_PIN_LOW);
	}

	if(GET_BIT(value,2) == 1)
	{
		DIO_setPinValue(LCD_D6_PORT, LCD_D6_PIN, DIO_PIN_HIGH);
	}
	else
	{
		DIO_setPinValue(LCD_D6_PORT, LCD_D6_PIN, DIO_PIN_LOW);
	}

	if(GET_BIT(value,3) == 1)
	{
		DIO_setPinValue(LCD_D7_PORT, LCD_D7_PIN, DIO_PIN_HIGH);
	}
	else
	{
		DIO_setPinValue(LCD_D7_PORT, LCD_D7_PIN, DIO_PIN_LOW);
	}
}

// send a number of many digits
void LCD_SendNumber4bit(long long int num)
{
    signed char i = 0;
    unsigned char rem;
    unsigned char arr[16];

    if (num < 0)
    {
        LCD_sendChar('-');
        num = num * -1;
    }
    else if (num == 0)
    {
        LCD_sendChar('0');
        return; // Exit the function since there are no digits to process.
    }

    while (num != 0 && i < 16)
    {
        rem = num % 10;
        arr[i] = rem;
        num = num / 10;
        i++;
    }

    for (i = i - 1; i >= 0; i--)
    {
        LCD_sendChar(arr[i] + '0');
    }
}


