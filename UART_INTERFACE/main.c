
#define F_CPU 16000000UL
#include <util/delay.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "UART_interface.h"
#include "LCD_interface.h"
int main() {

	 DIO_setPinDirection(DIO_PORTD, DIO_PIN1, DIO_PIN_OUTPUT); //SET TX PIN AS OUTPUT
	 DIO_setPinDirection(DIO_PORTD, DIO_PIN0, DIO_PIN_INPUT); // SET RX PIN AS INPUT
     UART_init();
     LCD_init();
     u8 DATA = 0xff ;

    while (1) {

    /*
        UART_sendString("EMBEDDED D54");
    	UART_TxChar('D');
        _delay_ms(500);
      */

        do {
        UART_RxChar(&DATA);
        }
        while(DATA == 0xff);


        LCD_sendChar(DATA);

    }

    return 0;
}
