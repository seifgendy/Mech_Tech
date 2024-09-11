/*
 * UART_interface.h
 *
 * Created: 9/30/2023 7:45:16 PM
 *  Author: Kareem Hussein
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_


void UART_init      (void);
void UART_TxChar    (u8 TxData);
void UART_RxChar    (u8* RxData);
void UART_sendString(u8* TxString);
/*
u8*  UART_receiveString(); 
*/


#endif /* UART_INTERFACE_H_ */