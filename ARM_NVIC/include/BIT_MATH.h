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
//header guard file
#ifndef BIT_MATH_H
#define BIT_MATH_H



#define		SET_BIT(REG, BIT)		(REG |= (1 << BIT ))    // (REG = REG | (1 << BIT ))    
#define		CLR_BIT(REG, BIT)		(REG &= ~(1 << BIT ))   // (REG = REG & (~(1 << BIT )))    
#define		TOG_BIT(REG, BIT)		(REG ^= (1 << BIT ))    // (REG = REG ^ (1 << BIT ))    
#define		GET_BIT(REG, BIT)		((REG >> BIT ) & 0x01 ) // (REG = REG | (1 << BIT ))    
 
 
 
 
 
 #endif