/*
 *
 main.c
 *
 *  Created on: Apr 1, 2024
 *  Author: seif gendy
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"


void main(void)
{
	/*Initialize The System Clock*/
	RCC_voidInit();
	/*Enable Peripheral Clock For GPIOA*/
	RCC_voidEnablePeripheralClock(RCC_AHB, RCC_AHB_GPIOAEN);
	/*Set PA0 To Be Output PP Low Speed*/
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN0, GPIO_OUTPUT);
	MGPIO_voidSetPinOutputType(GPIO_PORTA, GPIO_PIN0, GPIO_OUTPUT_PP);
	MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, GPIO_PIN0, GPIO_LOW_SPEED);

	/*Set PA1 To Be Output PP Low Speed*/
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN1, GPIO_OUTPUT);
	MGPIO_voidSetPinOutputType(GPIO_PORTA, GPIO_PIN1, GPIO_OUTPUT_PP);
	MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, GPIO_PIN1, GPIO_LOW_SPEED);

	/*Initialize The Group and Sub Priority bits in NVIC*/
	MNVIC_voidInit();
	/*Enable Interrupt For EXTI0*/
	MNVIC_voidPeripheralInterruptControl(6, MNVIC_INT_ENABLE);
	/*Enable Interrupt For EXTI1*/
	MNVIC_voidPeripheralInterruptControl(7, MNVIC_INT_ENABLE);
	/*Set The EXTI0 Priority*/
	MNVIC_voidSetPeripheralPriority(6, 0b0000); // EXTI0 : GRP 0 SUB 2
	/*Set The EXTI1 Priority*/
	MNVIC_voidSetPeripheralPriority(7, 0b0100); // EXTI1 : GRP 0 SUB 0
	/*Fire EXTI0 Interrupt, Set Pending Flag For EXTI0*/
	MNVIC_voidSetPendingFlag(6);

	asm("NOP");

	while(1)
	{

	}
}

//the ISR of the sixth prephiral and in it fired the interrupt of the seventh prephiral but if its priority is lower then it will not break this interrupt that toggle a led
void EXTI0_IRQHandler(void)
{
	MNVIC_voidSetPendingFlag(7);
	static u8 Local_u8LEDState = 0;
	Local_u8LEDState ^= 1;
	MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN0, Local_u8LEDState);
}



void EXTI1_IRQHandler(void)     //the ISR of the seventh external prephiral in the vector table that i have just given it a priority of group 0 sub 0
{
	static u8 Local_u8LEDState = 0;
	Local_u8LEDState ^= 1;
	MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, Local_u8LEDState);
}






