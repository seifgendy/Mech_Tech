/*
 * main.c
 *
 *  Created on: May 5, 2024
 *      Author: seif gendy
 */
#include "../include/BIT_MATH.h"
#include "../include/STD_TYPES.h"

#include "../include/GPIO_interface.h"
#include "../include/RCC_interface.h"
#include "../include/UART_interface.h"


//this lab send the data that it recieves through uart
void main(void)
{
	RCC_voidInit();
	RCC_voidEnablePrephiralClock(RCC_AHB, RCC_AHB_GPIOAEN);
	RCC_voidEnablePrephiralClock(RCC_APB2, RCC_APB2_USART1);
	MUSART1_voidInit();
	u8 ReceivedData;
	while(1)
	{
		MUSART1_voidReceiveDataSynchronous(&ReceivedData);
		MUSART1_voidSendDataSynchronous(ReceivedData);
	}
}




