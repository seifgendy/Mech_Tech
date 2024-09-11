/*
 * SPI_program.c
 *
 * Created: 10/6/2023 7:35:37 PM
 *  Author: Kareem Hussein
 */ 


/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "SPI_interface.h"
#include "SPI_private.h"

static void (*private_pCallBackSPI)(u8)=NULL;

void SPI_initMaster(void)
{
	//select Data Order LSB transmitted first
	SET_BIT(SPI->SPCR,DORD);
	
	// select Master Mode
	SET_BIT(SPI->SPCR,MSTR);
	
	// select CLK Polarity Falling => Rising , select CLK Phase Setup => Sample
	SET_BIT(SPI->SPCR,CPOL);
	SET_BIT(SPI->SPCR,CPHA);
	
	// select CLK Rate = FCPU/16 (1 MHZ)
	SET_BIT(SPI->SPCR,SPR0);
	CLR_BIT(SPI->SPCR,SPR1);
	CLR_BIT(SPI->SPSR,SPI2X);
	
	// Enable SPI
	SET_BIT(SPI->SPCR,SPE);
}


void SPI_initSlave(void)
{
	//select Data Order LSB transmitted first
	SET_BIT(SPI->SPCR,DORD);
	
	// select Slave Mode
	CLR_BIT(SPI->SPCR,MSTR);
	
	// select CLK Polarity Falling => Rising , select CLK Phase Setup => Sample
	SET_BIT(SPI->SPCR,CPOL);
	SET_BIT(SPI->SPCR,CPHA);
	
	// Enable SPI
	SET_BIT(SPI->SPCR,SPE);
}


void SPI_transieve(u8 TxData, u8* RxData)
{
	if(RxData!=NULL)
	{
		//Check on Colision Flag
		while(1 == GET_BIT(SPI->SPSR,WCOL));
		SPI->SPDR = TxData;
		
		//Busy Wait
		while(0 == GET_BIT(SPI->SPSR,SPIF));
		
		*RxData = SPI->SPDR;
	}
}


void SPI_transmitAsynchronous(u8 TxData, void(*ptrToFun)(u8))
{
	if(ptrToFun!=NULL)
	{
		// SPI Interrupt Enable
		SET_BIT(SPI->SPCR,SPIE);
		
		private_pCallBackSPI = ptrToFun;
		
		//Check on Colision Flag
		while(1 == GET_BIT(SPI->SPSR,WCOL));
		SPI->SPDR = TxData;
	}
}


void __vector_12(void) __attribute__ ((signal));
void __vector_12(void)
{
	if(private_pCallBackSPI!=NULL)
	{
		private_pCallBackSPI(SPI->SPDR);
	}
}