/*********************************************
 * Author:				SEIF GENDY
 * Creation Data:		09 Mar, 2024
 * Version:				v1.0
 * Compiler:			GNU ARM-GCC
 * Controller:			STM32F401CCU6
 * Layer:				MCAL
 ********************************************/
/*********************************************
 * Version	  Date				  Author				  Description
 * v1.0		  09 Mar, 2024	     SEIF GENDY		        Initial Creation
*********************************************/

#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H


void MSTK_voidInit(void);                       //enable the prephiral
void MSTK_voidSetBusyWait(u32 copy_u32Ticks);   // alternative of delay function 


#endif