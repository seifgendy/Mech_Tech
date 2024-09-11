/*

 * main.c
 *
 *  Created on: Apr 9, 2024
 *  Author: seif gendy Computer World
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"
#include "STK_interface.h"
#include "EXTI_interface.h"


#define NO_START	0
#define START		1

void GetFrame(void);
void TakeAction(void);//function to be done at interrupt
void APP_voidPlay(void);


u8 u8ButtonData = 0;
u8 APP_u8StartBitFlag = NO_START;//to know wether this is the first falling edge or no
u8 u8EdgeCounter = 0;
u32 u32ReceivedFrame[100];//array for storing recieved bits

void main(void)
{
	/*Initialize The System Clock*/
	RCC_voidInit();
	/*Enable GPIOA Peripheral Clock*/
	RCC_voidEnablePrephiralClock( RCC_AHB , RCC_AHB_GPIOAEN);
	RCC_voidEnablePrephiralClock( RCC_APB2 ,RCC_APB2_SYSCF);


	/*Set RGB LED Pins, PA1, PA2, and PA3*/
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN1, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN2, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN3, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN4, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN5, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN6, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN7, GPIO_OUTPUT);


	MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, GPIO_PIN1, GPIO_LOW_SPEED);
	MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, GPIO_PIN2, GPIO_LOW_SPEED);
	MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, GPIO_PIN3, GPIO_LOW_SPEED);
	MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, GPIO_PIN4, GPIO_LOW_SPEED);
	MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, GPIO_PIN5, GPIO_LOW_SPEED);
	MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, GPIO_PIN6, GPIO_LOW_SPEED);
    MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, GPIO_PIN7, GPIO_LOW_SPEED);



	MGPIO_voidSetPinOutputType(GPIO_PORTA, GPIO_PIN1, GPIO_OUTPUT_PP);
	MGPIO_voidSetPinOutputType(GPIO_PORTA, GPIO_PIN2, GPIO_OUTPUT_PP);
	MGPIO_voidSetPinOutputType(GPIO_PORTA, GPIO_PIN3, GPIO_OUTPUT_PP);
	MGPIO_voidSetPinOutputType(GPIO_PORTA, GPIO_PIN4, GPIO_OUTPUT_PP);
	MGPIO_voidSetPinOutputType(GPIO_PORTA, GPIO_PIN5, GPIO_OUTPUT_PP);
	MGPIO_voidSetPinOutputType(GPIO_PORTA, GPIO_PIN6, GPIO_OUTPUT_PP);
	MGPIO_voidSetPinOutputType(GPIO_PORTA, GPIO_PIN7, GPIO_OUTPUT_PP);

	/*Set PA0 To Be Input Float*/
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN0, GPIO_INPUT);

	/*Initialize The SysTick*/
	MSTK_voidInit();

	/*Initialize The NVIC*/
	MNVIC_voidInit();

	/*NVIC Enable Interrupt For EXTI0*/
	MNVIC_voidPeripheralInterruptControl(6, MNVIC_INT_ENABLE);

    /*initialize to accept interrupt at this port*/
	MEXTI_voidInit(EXTI_PORTA   , EXTI_PIN0);

	/*Enable EXTI0*/
	MEXTI_voidEnableInterrupt(MEXTI_EXTI0);

	/*Setup EXTI0 To Sense The Falling Edge*/
	MEXTI_voidChangeSenseMode(MEXTI_EXTI0, MEXTI_FALLING);

	/*Set The Callback function for EXTI0*/
	MEXTI_voidSetCallBack(MEXTI_EXTI0, &GetFrame);






	while(1)
	{
		;
	}
}
//will come here at each falling edge interrupt from the ir led
void GetFrame(void)
{
	if(APP_u8StartBitFlag == NO_START)//new frame
	{
		MSTK_voidSetPreloadValue(1000000);
		MSTK_voidSetSingleInterval(&TakeAction);
		APP_u8StartBitFlag = START;//to know at the second time that it is not the first falling edge so not the start of a new frame
	}
	else//if not the begining of the frame so start storing the data of the pressed button in an array
	{
		u32ReceivedFrame[u8EdgeCounter] = MSTK_voidGetElapsedTime();//the array that will store the data of the frame and the values in it are the number of ms from which i will indicate wether 0 or 1
		MSTK_voidResetTimer();
		MSTK_voidSetPreloadValue(1000000);
		u8EdgeCounter++;
	}
}


//this function decodes the frame sent from time to zeros and ones
void TakeAction(void)
{
	u8 Local_u8LoopCounter = 0;
	for(Local_u8LoopCounter = 0; Local_u8LoopCounter < 8; Local_u8LoopCounter++)
	{
		//check if the value of get elapsed type is from 1000 to 1500 then it is a zero else then it is a one
		if(		(u32ReceivedFrame[17+Local_u8LoopCounter] >= 1000) &&
				(u32ReceivedFrame[17+Local_u8LoopCounter] <= 1500))
		{
			CLR_BIT(u8ButtonData, Local_u8LoopCounter);
		}
		else
		{
			SET_BIT(u8ButtonData, Local_u8LoopCounter);
		}
	}
	u8EdgeCounter = 0;
	APP_u8StartBitFlag = NO_START;
	MSTK_voidSTKEnable();
	APP_voidPlay();
}


void APP_voidPlay(void)
{

	switch(u8ButtonData)
	{
	case 12:
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_PIN_TOGGLE);
		break;
	case 24:
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN2, GPIO_PIN_TOGGLE);
		break;
	case 94:
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN3, GPIO_PIN_TOGGLE);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN4, GPIO_PIN_TOGGLE);
		break;
	case 8:
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN4, GPIO_PIN_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN5, GPIO_PIN_HIGH);
		break;
	case 28:
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN6, GPIO_PIN_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN7, GPIO_PIN_LOW);
		break;
	case 90:
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_PIN_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN2, GPIO_PIN_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN3, GPIO_PIN_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN4, GPIO_PIN_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN5, GPIO_PIN_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN6, GPIO_PIN_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN7, GPIO_PIN_LOW);

		break;
	case 66:
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_PIN_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN2, GPIO_PIN_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN3, GPIO_PIN_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN4, GPIO_PIN_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN5, GPIO_PIN_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN6, GPIO_PIN_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN7, GPIO_PIN_HIGH);
		break;
	case 82:
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_PIN_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN2, GPIO_PIN_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN3, GPIO_PIN_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN4, GPIO_PIN_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN5, GPIO_PIN_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN6, GPIO_PIN_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN7, GPIO_PIN_HIGH);
		break;
	case 74:
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_PIN_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN2, GPIO_PIN_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN3, GPIO_PIN_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN4, GPIO_PIN_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN5, GPIO_PIN_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN6, GPIO_PIN_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN7, GPIO_PIN_LOW);
		break;
	default:
		break;
	}
}

/* Power Button -> 69
 * Mute Button -> 71
 * 1 Button -> 12
 * 2 Button -> 24
 * 3 Button -> 94
 * 4  8
 * 5  28
 * 6  90
 * 7  66
 * 8  82
 * 9  74
 * */






