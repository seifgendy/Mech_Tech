/****************************************************************************************
* Author:				seif gendy
* Creation Data:		19 Apr, 2024
* Version:				v1.0
* Compiler:				GNU ARM-GCC
* Controller:			STM32F401CCU6
* Layer:				HAL
****************************************************************************************/
/***************************************************************************************
* Version	  Date				  	Author				  			Description
* v1.0		  26 Apr, 2024			seif gendy		            	Initial Creation
***************************************************************************************/
#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"

#include "../include/GPIO_interface.h"
#include "../include/STK_interface.h"
#include "../include/SPI_interface.h"

#include "../include/TFT_interfae.h"
#include "../include/TFT_private.h"
#include "../include/TFT_config.h"



void HTFT_voidInit(void)
{
    // Set A0 Of TFT To be Output Pin//Ao is command or data selection pin
    MGPIO_voidSetPinMode(HTFT_A0_PORT_PIN, GPIO_OUTPUT);
    // Set RST Of TFT To be Output Pin
    MGPIO_voidSetPinMode(HTFT_RST_PORT_PIN, GPIO_OUTPUT);

    // Initialization Sequence
    // Rest Pulses  these values are not in data sheet trial and error
    MGPIO_voidSetPinValue(HTFT_RST_PORT_PIN, GPIO_PIN_HIGH);
    MSTK_voidSetBusyWait(100);
    MGPIO_voidSetPinValue(HTFT_RST_PORT_PIN, GPIO_PIN_LOW);
    MSTK_voidSetBusyWait(1);
    MGPIO_voidSetPinValue(HTFT_RST_PORT_PIN, GPIO_PIN_HIGH);
    MSTK_voidSetBusyWait(100);
    MGPIO_voidSetPinValue(HTFT_RST_PORT_PIN, GPIO_PIN_LOW);
    MSTK_voidSetBusyWait(100);
    MGPIO_voidSetPinValue(HTFT_RST_PORT_PIN, GPIO_PIN_HIGH);
    MSTK_voidSetBusyWait(120000);
    // el command ely ba2olo feh esha mn el noom
    voidSendCommand(SLPOUT_CMD);
    MSTK_voidSetBusyWait(150000);
    // el command ely ba5tar beh ana mashy 3la anhy color code
    voidSendCommand(COLMOD_CMD);
    HTFT_voidSendData(TFT_COLOR_MODE);
    // display command 
    voidSendCommand(DISPON_CMD);
}




static void voidSendCommand(u8 Copy_u8Command)
{
    u8 Local_u8Dummy;
    // Set A0 Pin To Be Low For Command option
    MGPIO_voidSetPinValue(HTFT_A0_PORT_PIN, GPIO_PIN_LOW);
    //send command over spi protocol
    Local_u8Dummy = MSPI1_u8TrancieveSynchronous(Copy_u8Command);
}



void HTFT_voidSendData(u8 Copy_u8Data)
{
    u8 Local_u8Dummy;
    // Set A0 Pin To Be Low For Command option
    MGPIO_voidSetPinValue(HTFT_A0_PORT_PIN, GPIO_PIN_HIGH);
     //send command over spi protocol
    Local_u8Dummy = MSPI1_u8TrancieveSynchronous(Copy_u8Data);
}



void HTFT_voidSetWindow(u8 Copy_u8X0, u8 Copy_u8X1, u8 Copy_u8Y0, u8 Copy_u8Y1)
{
    // Send Set X Addresses Command 0x2A so that it know i will choose now my x boundries
    voidSendCommand(X_ADD_CMD);
    // the first byte of the first x boundry
    HTFT_voidSendData(0);
    // the second byte of the first x boundry
    HTFT_voidSendData(Copy_u8X0);
    // the first byte of the second x boundry
    HTFT_voidSendData(0);
    // the second byte of the second x boundry
    HTFT_voidSendData(Copy_u8X1);


    // Send Set y Addresses Command 0x28 so that it know i will choose now my y boundries
    voidSendCommand(Y_ADD_CMD);
    // the first byte of the first y boundry
    HTFT_voidSendData(0);
    // the second byte of the first y boundry
    HTFT_voidSendData(Copy_u8Y0);
    // the first byte of the second y boundry
    HTFT_voidSendData(0);
    // the second byte of the second y boundry
    HTFT_voidSendData(Copy_u8Y1);
}


void HTFT_voidDisplayPartialImage(u16 *Copy_pu16Image, u16 xStart, u16 xEnd, u16 yStart, u16 yEnd)
{
    u16 Local_u16LoopCounter = 0;
    u8 Local_u8Data;
    u16 width = xEnd - xStart + 1;  // Calculate width of the window
    u16 height = yEnd - yStart + 1; // Calculate height of the window

    // Set the window where the image will be displayed
    HTFT_voidSetWindow(xStart, xEnd, yStart, yEnd);

    // Send Write RAM Command
    voidSendCommand(RAM_WR_CMD);

    // Iterate over the image array and send data
    for(u16 y = 0; y < height; y++)
    {
        for(u16 x = 0; x < width; x++)
        {
            // Calculate the correct index for the image data
            u16 pixelIndex = y * width + x;

            // Send MSB First
            Local_u8Data = (u8)(Copy_pu16Image[pixelIndex] >> 8);
            HTFT_voidSendData(Local_u8Data);

            // Send LSB Then
            Local_u8Data = (u8)Copy_pu16Image[pixelIndex];
            HTFT_voidSendData(Local_u8Data);
        }
    }
}




void HTFT_voidClearScreen(u16 color)
{
    u16 Local_u16LoopCounter = 0;
    u8 Local_u8Data;

    // Set the window to cover the entire screen
    HTFT_voidSetWindow(0, 127, 0, 159); // Assuming the screen resolution is 128x160

    // Send Write RAM Command
    voidSendCommand(RAM_WR_CMD);

    // Fill the entire screen with the specified color
    for(Local_u16LoopCounter = 0; Local_u16LoopCounter < 20480; Local_u16LoopCounter++)
    {
        // Send MSB First
        Local_u8Data = (u8)(color >> 8);
        HTFT_voidSendData(Local_u8Data);

        // Send LSB Then
        Local_u8Data = (u8)color;
        HTFT_voidSendData(Local_u8Data);
    }
}





void DisplayShape32x32(u16 *shapeArray, u16 xStart, u16 yStart)
{
    u16 xEnd = xStart + 31; // End x position for 32x32 grid
    u16 yEnd = yStart + 31; // End y position for 32x32 grid

    // Set the window on the TFT screen to match the 32x32 grid
    HTFT_voidSetWindow(xStart, xEnd, yStart, yEnd);

    // Send the command to start writing to the display RAM
    voidSendCommand(RAM_WR_CMD);

    // Loop over the shape array and send pixel data to the TFT screen
    for (u16 i = 0; i < 1024; i++) // 32 * 32 = 1024
    {
        u8 msb = (u8)(shapeArray[i] >> 8); // Most significant byte
        u8 lsb = (u8)shapeArray[i];        // Least significant byte

        HTFT_voidSendData(msb); // Send MSB first
        HTFT_voidSendData(lsb); // Send LSB second
    }
}








void MoveShapeTopToBottom(u16 *shapeArray, u16 startX, u16 shapeWidth, u16 shapeHeight, u16 delayMs)
{
    // Initialize the starting Y position at the top of the screen
    u16 posY = 0;

    // Get the screen height, assuming the TFT screen height is 160 pixels
    u16 screenHeight = 160;

    // Loop to move the shape downwards
    while (posY + shapeHeight <= screenHeight)
    {
        // Clear the previous position
        HTFT_voidClearScreen(0x0000);

        // Display the shape at the current position
        HTFT_voidDisplayPartialImage(shapeArray, startX, posY, shapeWidth, shapeHeight);

        // Increment the Y position to move the shape down
        posY += 1;

        // Delay for a smooth animation
        MSTK_voidSetBusyWait(delayMs * 1000);  // Delay in milliseconds
    }
}



