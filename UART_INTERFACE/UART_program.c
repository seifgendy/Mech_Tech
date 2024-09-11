/*
 * UART_program.c
 *
 * Created: 9/30/2023 7:45:06 PM
 *  Author: Kareem Hussein
 */ 


/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "UART_interface.h"
#include "UART_private.h"


void UART_init(void)
{
	// Set Buad Rate = 9600
	CLR_BIT(UCSRA,U2X);//disable double speed
	UBRRL = 103;//choose baud rate from table to most common baud rate 9600 bts
	
	u8 initVar = 0x00;                                                       // this var is to overcome the problem of the two registers that have same address
                                                                             // so we are going to write directly to the register using this variable
	SET_BIT(initVar,URSEL);// select the UCSRC(one of the two regs)          // now we are in the bits dimension each bit in the 8bit var shuld do a specific task in the register
	// select UART MODE = Asynchronous                                       //the main problem was that when i read the register one time it get me the value in the required regs and second time it read the other register
	CLR_BIT(initVar,UMSEL);
	// configure no parity that chec transmission error
	CLR_BIT(initVar,UPM0); 
	CLR_BIT(initVar,UPM1); 
	// configure stop bits = 1 that indicate end of signal
	CLR_BIT(initVar,USBS);
	// configure data bits = 8
	SET_BIT(initVar,UCSZ0);
	SET_BIT(initVar,UCSZ1);
	CLR_BIT(UCSRB,UCSZ2);
	// configure no polarity since we are asynchronous
	CLR_BIT(initVar,UCPOL);
	
	UCSRC = initVar; //here i put the var in the req regs // UCSRC = 0b100000110; i could have write this instead of creating the var methos

	//Enable Tx
	SET_BIT(UCSRB,TXEN);
	
	//Enable Rx
	SET_BIT(UCSRB,RXEN);
}


void UART_TxChar(u8 TxData)
{
	UDR = TxData;
	
	// Busy Wait on Data Register empty flag
	while(0 == GET_BIT(UCSRA,UDRE));
}


void UART_RxChar(u8* RxData)
{
	if(RxData != NULL)
	{
		// Busy Wait on Receive Compelete flag
		while(0 == GET_BIT(UCSRA,RXC));
		
		*RxData = UDR;
	}
}


void UART_sendString(u8* TxString)
{
	if(TxString != NULL)
	{
		u8 charCounter=0;
		while(TxString[charCounter] != '\0')
		{
			UART_TxChar(TxString[charCounter]);
			charCounter++;
		}
	}
}
