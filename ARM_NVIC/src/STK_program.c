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
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"



void MSTK_voidInit(void)
{
 ////////clock source selection/////////
#if STK_CLK_SRC == STK_AHB
SET_BIT (STK->CTRL , 2 ) ;

#elif STK_CLK_SRC == STK_AHB_DIV_8
CLR_BIT (STK->CTRL , 2 ) ;

#else
#error "STK_CLK_SRC CONFIGURATION_ERROR "

#endif
///////////////////interrupt enable////////////////
#if STK_INT_CTRL == STK_ENABLE
SET_BIT (STK->CTRL , 1 ) ;

#elif STK_INT_CTRL == STK_DISABLE
CLR_BIT (STK->CTRL , 1 ) ;

#else
#error "STK_INT_CTRL CONFIGURATION_ERROR "

#endif

///////enable systick//////////////
#if STK_CTRL == STK_ENABLE
SET_BIT(STK->CTRL , 0);
#elif STK_CTRL == STK_DISABLE
CLR_BIT(STK->CTRL , 0);
#error "STK_CTRL CONFIGURATION_ERROR"
#endif
}

//alternative of delay function
void MSTK_voidSetBusyWait(u32 copy_u32Ticks)
{
//load ticks values in the load register
STK -> LOAD = copy_u32Ticks ;
//wait for tick interrupt
while ( GET_BIT(STK -> CTRL,16) == 0 );
//clear the flag
STK -> VAL = 0 ;



}
