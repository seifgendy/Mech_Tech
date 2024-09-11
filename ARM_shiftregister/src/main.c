
/*
#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"

#include "../include/RCC_interface.h"
#include "../include/GPIO_interface.h"
#include "../include/STK_interface.h"

// Function Prototype
void LEDMAT_voidDisplay_BY_ShiftREG(u8 * Copy_pu8Data);

//Active One COL Only
const u8 Set_COL_Array[] = {0b11111110, 0b11111101, 0b11111011, 0b11110111,
							0b11101111, 0b11011111, 0b10111111, 0b01111111};
//main Function
void main(void)
{
	u8 Local_u8PinInit;

	// LED Matrix - The first letter of my name
	u8 FirstLetterName[] ={0x7f,0x49,0x49,0x49,0x49,0x49,0x00,0x00};
	// LED Matrix - Za3bola Animations
	u8 ANIM0_P1[] ={0xa0,0x52,0x3d,0x5a,0x60,0x00,0x00,0x00};
	u8 ANIM0_P2[] ={0xa0,0x52,0x3d,0x5a,0x90,0x00,0x00,0x00};
	u8 ANIM1_P1[] ={0xa0,0x52,0x3d,0x5a,0x80,0x20,0x00,0x00};
	u8 ANIM1_P2[] ={0xa0,0x52,0x3d,0x5a,0x80,0x00,0x10,0x00};
	u8 ANIM1_P3[] ={0xa0,0x52,0x3d,0x5a,0x80,0x00,0x00,0x08};
	u8 ANIM1_P4[] ={0xa0,0x52,0x3d,0x5a,0x80,0x00,0x04,0x00};
	u8 ANIM1_P5[] ={0xa0,0x52,0x3d,0x5a,0x80,0x02,0x00,0x00};
	u8 ANIM1_P6[] ={0xa0,0x50,0x3a,0x5d,0x83,0x00,0x00,0x00};

	RCC_voidInit();
	RCC_voidEnablePrephiralClock(RCC_AHB, RCC_AHB_GPIOAEN);

	for(Local_u8PinInit=0; Local_u8PinInit<3; Local_u8PinInit++)
	{
     MGPIO_voidSetPinMode(GPIO_PORTA, Local_u8PinInit, GPIO_OUTPUT);
     MGPIO_voidSetPinOutputType(GPIO_PORTA, Local_u8PinInit, GPIO_OUTPUT_PP);
     MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, Local_u8PinInit, GPIO_LOW_SPEED);
	}
	MSTK_voidInit();

 while(1)
 {
	// The first letter of my name
    for(u8 LOCAL_u8Times=0; LOCAL_u8Times<15; LOCAL_u8Times++)
    {
      for(u8 LOCAL_u8Count=0; LOCAL_u8Count<10; LOCAL_u8Count++)
	  {
			 LEDMAT_voidDisplay_BY_ShiftREG(FirstLetterName);
      }
    }

	// Za3bola-Animation Part1
	for(u8 LOCAL_u8Times=0; LOCAL_u8Times<10; LOCAL_u8Times++)
	{

	  for(u8 LOCAL_u8Count=0; LOCAL_u8Count<10; LOCAL_u8Count++)
	  {
		 LEDMAT_voidDisplay_BY_ShiftREG(ANIM0_P1);
	   }

	   for(u8 LOCAL_u8Count=0; LOCAL_u8Count<10; LOCAL_u8Count++)
	   {
		  LEDMAT_voidDisplay_BY_ShiftREG(ANIM0_P2);
	   }
	}


	// Za3bola-Animation Part2
	for(u8 LOCAL_u8Times=0; LOCAL_u8Times<4; LOCAL_u8Times++)
		{
		   for(u8 LOCAL_u8Count=0; LOCAL_u8Count<10; LOCAL_u8Count++)
		   {
			  LEDMAT_voidDisplay_BY_ShiftREG(ANIM0_P1);
		   }

		   for(u8 LOCAL_u8Count=0; LOCAL_u8Count<10; LOCAL_u8Count++)
		   {
			  LEDMAT_voidDisplay_BY_ShiftREG(ANIM1_P1);
	       }

		   for(u8 LOCAL_u8Count=0; LOCAL_u8Count<10; LOCAL_u8Count++)
		    {
			   LEDMAT_voidDisplay_BY_ShiftREG(ANIM1_P2);
		    }

		   for(u8 LOCAL_u8Count=0; LOCAL_u8Count<10; LOCAL_u8Count++)
		    {
			   LEDMAT_voidDisplay_BY_ShiftREG(ANIM1_P3);
		    }

		   for(u8 LOCAL_u8Count=0; LOCAL_u8Count<10; LOCAL_u8Count++)
		   {
			   LEDMAT_voidDisplay_BY_ShiftREG(ANIM1_P4);
	       }

		   for(u8 LOCAL_u8Count=0; LOCAL_u8Count<10; LOCAL_u8Count++)
		    {
			   LEDMAT_voidDisplay_BY_ShiftREG(ANIM1_P5);
		    }

		   for(u8 LOCAL_u8Count=0; LOCAL_u8Count<10; LOCAL_u8Count++)
		    {
			   LEDMAT_voidDisplay_BY_ShiftREG(ANIM1_P6);
		    }

		   for(u8 LOCAL_u8Count=0; LOCAL_u8Count<10; LOCAL_u8Count++)
		    {
			   LEDMAT_voidDisplay_BY_ShiftREG(ANIM1_P5);
		    }

		   for(u8 LOCAL_u8Count=0; LOCAL_u8Count<10; LOCAL_u8Count++)
		   {
			   LEDMAT_voidDisplay_BY_ShiftREG(ANIM1_P4);
	       }

		   for(u8 LOCAL_u8Count=0; LOCAL_u8Count<10; LOCAL_u8Count++)
		    {
			   LEDMAT_voidDisplay_BY_ShiftREG(ANIM1_P3);
		    }

		   for(u8 LOCAL_u8Count=0; LOCAL_u8Count<10; LOCAL_u8Count++)
		    {
			   LEDMAT_voidDisplay_BY_ShiftREG(ANIM1_P2);
		    }

		   for(u8 LOCAL_u8Count=0; LOCAL_u8Count<10; LOCAL_u8Count++)
		   {
			   LEDMAT_voidDisplay_BY_ShiftREG(ANIM1_P1);
	       }
	     }
 }
}
//put to me the values that light the first coulmn wich is 01111111 since it is 8 bits values so i do this iteration 8 times and then put to me the value that light the proper rows in the first column by asking him about the values of the first bit in each of the 8 data elements thats why  i do the secnd part 8 times then send this two 8 bits by the storage clock then wait 2500 bec it is the first frame which is a partially lighten coulmn now then do this 8 times to pass by the 8 coulmns after the calling of this func i will have displayed the full image coulmn by coulmn once now i have to call this func multiple times to see the image for a while
void LEDMAT_voidDisplay_BY_ShiftREG(u8 * Copy_pu8Data)
{
	u8 Local_u8CountLoop;
	u8 Local_u8LoopCounter;

	for(Local_u8LoopCounter=0; Local_u8LoopCounter<8; Local_u8LoopCounter++)
	{
    // Set Only One COL
	for (Local_u8CountLoop=0; Local_u8CountLoop<8; Local_u8CountLoop++)
	{
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN0, GET_BIT(Set_COL_Array[Local_u8LoopCounter], (7-Local_u8CountLoop)));
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_PIN_HIGH);
		MSTK_voidSetBusyWait(10);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_PIN_LOW);
	}

   // SET Rows value
   for (Local_u8CountLoop=0; Local_u8CountLoop<8; Local_u8CountLoop++)
   {
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN0, GET_BIT(*(Copy_pu8Data+Local_u8LoopCounter), (7-Local_u8CountLoop)));
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_PIN_HIGH);
		MSTK_voidSetBusyWait(10);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_PIN_LOW);
   }
   // Send Data To Storage REG
	MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN2, GPIO_PIN_HIGH);
	MSTK_voidSetBusyWait(10);
	MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN2, GPIO_PIN_LOW);
  // Delay 50 FPS
    MSTK_voidSetBusyWait(2500);
	}
}
*/














/*
#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"

#include "../include/RCC_interface.h"
#include "../include/GPIO_interface.h"
#include "../include/STK_interface.h"

// Function Prototype
void LEDMAT_voidDisplay_BY_ShiftREG(u8 * Copy_pu8Data);

//Active One COL Only
const u8 Set_COL_Array[] = {0b01101110, 0b11111101, 0b11111011, 0b11110111,
							0b11101111, 0b11011111, 0b10111111, 0b01111111};
//main Function
void main(void)
{
	u8 Local_u8PinInit;

	// LED Matrix - The first letter of my name
	u8 FirstLetterName[] ={0x7f,0x49,0x49,0x49,0x49,0x49,0x00,0x00};


	RCC_voidInit();
	RCC_voidEnablePrephiralClock(RCC_AHB, RCC_AHB_GPIOAEN);

	for(Local_u8PinInit=0; Local_u8PinInit<3; Local_u8PinInit++)
	{
     MGPIO_voidSetPinMode(GPIO_PORTA, Local_u8PinInit, GPIO_OUTPUT);
     MGPIO_voidSetPinOutputType(GPIO_PORTA, Local_u8PinInit, GPIO_OUTPUT_PP);
     MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, Local_u8PinInit, GPIO_LOW_SPEED);
	}
	MSTK_voidInit();

 while(1)
 {
	// The first letter of my name
    for(u8 LOCAL_u8Times=0; LOCAL_u8Times<15; LOCAL_u8Times++)
    {
      for(u8 LOCAL_u8Count=0; LOCAL_u8Count<10; LOCAL_u8Count++)
	  {
			 LEDMAT_voidDisplay_BY_ShiftREG(FirstLetterName);
      }
    }


 }
}
//put to me the values that light the first coulmn wich is 01111111 since it is 8 bits values so i do this iteration 8 times and then put to me the value that light the proper rows in the first column by asking him about the values of the first bit in each of the 8 data elements thats why  i do the secnd part 8 times then send this two 8 bits by the storage clock then wait 2500 bec it is the first frame which is a partially lighten coulmn now then do this 8 times to pass by the 8 coulmns after the calling of this func i will have displayed the full image coulmn by coulmn once now i have to call this func multiple times to see the image for a while
void LEDMAT_voidDisplay_BY_ShiftREG(u8 * Copy_pu8Data)
{
	u8 Local_u8CountLoop;
	u8 Local_u8LoopCounter = 0 ;


	for (Local_u8CountLoop=0; Local_u8CountLoop<8; Local_u8CountLoop++)
	{
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN0, GET_BIT(Set_COL_Array[Local_u8LoopCounter], (7-Local_u8CountLoop)));
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_PIN_HIGH);
		MSTK_voidSetBusyWait(10);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_PIN_LOW);
	}






   // Send Data To Storage REG
	MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN2, GPIO_PIN_HIGH);
	MSTK_voidSetBusyWait(10);
	MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN2, GPIO_PIN_LOW);

	}
*/



#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"


void ShiftREG(u8 data) {

     u8 data1 = data ;

	// SET the first register
    for (int i = 0; i <=7  ; i++) {
    	data1 = data ;
        MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN0,  ((data1 >> i) & 0x01) );
        // Toggle GPIO_PIN1 to shift data
        MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_PIN_HIGH);
        MSTK_voidSetBusyWait(10);
        MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_PIN_LOW);
    }

    // Send Data To Storage REG
    MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN2, GPIO_PIN_HIGH);
    MSTK_voidSetBusyWait(10);
    MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN2, GPIO_PIN_LOW);


}



void main(void)
{


	  u8 data = 0b10010010 ;




	RCC_voidInit();
	RCC_voidEnablePrephiralClock(RCC_AHB, RCC_AHB_GPIOAEN);



     MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN0, GPIO_OUTPUT);
     MGPIO_voidSetPinOutputType(GPIO_PORTA, GPIO_PIN0, GPIO_OUTPUT_PP);
     MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, GPIO_PIN0, GPIO_LOW_SPEED);

     MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN1, GPIO_OUTPUT);
     MGPIO_voidSetPinOutputType(GPIO_PORTA, GPIO_PIN1, GPIO_OUTPUT_PP);
     MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, GPIO_PIN1, GPIO_LOW_SPEED);

     MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN2, GPIO_OUTPUT);
     MGPIO_voidSetPinOutputType(GPIO_PORTA, GPIO_PIN2, GPIO_OUTPUT_PP);
     MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, GPIO_PIN2, GPIO_LOW_SPEED);



	MSTK_voidInit();



    ShiftREG(data);


}

