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


#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H


#define STK_AHB                0
#define STK_AHB_DIV_8          1
#define STK_DISABLE            1
#define STK_ENABLE             0





//here i use structs to define registers since they take successive places in the memory
typedef struct
{
   volatile u32 CTRL ;
   volatile u32 LOAD ;       //or u32 *STK[4];  this is how to do it by array then
   volatile u32 VAL  ;      // STK[0] = 0xE000E010    STK[1] = 0xEoooE014 and so on
   volatile u32 CALIB;

}STK_t;  //the new struct data type name is stk_t



// now lets give this data type the first address of first register and it will carry on

         //new ptr name    //pointer of type stk_t with address 0xE000E010
#define     STK         ((volatile STK_t *)0xE000E010)
//if i want to access a register do this (STK -> CTRL)



#endif
