/*
 * TWI_test.c
 *
 * Created: 10/7/2023 10:35:41 PM
 * Author : AMIT
 */ 


/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "TWI_interface.h"

/* HAL */
#include "EEPROM_interface.h"
#include "LCD_interface.h"


int main(void)
{
    /* Replace with your application code */
	u8 data;
	LCD_init();
	EEPROM_init();
	EEPROM_writeByte(200,'D');
	EEPROM_readByte(200,&data);
	LCD_sendChar(data);
    while (1) 
    {
    }
}

