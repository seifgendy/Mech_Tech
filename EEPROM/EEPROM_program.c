/*
 * EEPROM_program.c
 *
 * Created: 10/7/2023 11:53:53 AM
 *  Author: Kareem Hussein
 */ 

#define F_CPU   16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "TWI_interface.h"

/* HAL */
#include "EEPROM_interface.h"
#include "EEPROM_private.h"


void EEPROM_init(void)
{
	TWI_initMaster();
}

//THE TRICK IS IN SENDING THE ADDRESS ASSUME WORSTE CASE THAT ADDRESS IS 1111 1111 111 WHICH IS THE LARGEST ADDRESS IN LARGEST EEPROM
//TO STORE IT IN TWO REG THE 8 LEAST SIG COULD BE PUT IN REGS BY JUST CASTING THEM FROM U16 TO U8 OR IT IS AUTOMATICLLY DONE
//BUT FOR THE 8 MOST I RIGHT SHIFT TO GET THEM THEM I OR THEM WITH SOME NOMBERS TO TAKE FROM THEM THE BITS THAT I MIND FROM THE ADDRESS (WHAT LEFT FROM THE 11 BIT)

void EEPROM_writeByte(u16 wordAddress, u8 data)
{
	u8 address = (wordAddress>>8) | EEPROM_FIXED_ADDRESS;
	
	// Send start condition
	TWI_sendStartCondition();
	
	// Send slave address with write operation
	TWI_sendSlaveAddWithWrite(address);
	
	// Send word address
	TWI_sendMasterDataByte((u8)wordAddress);
	
	// Send byte data
	TWI_sendMasterDataByte(data);
	
	// Send stop condition
	TWI_sendStopCondition();
	
	// Self-timed Write Cycle delay
	_delay_ms(5);
}


void EEPROM_readByte(u16 wordAddress, u8* data)
{
	u8 address = (wordAddress>>8) | EEPROM_FIXED_ADDRESS;
	
	// Send start condition
	TWI_sendStartCondition();
	
	// Send slave address with write operation
	TWI_sendSlaveAddWithWrite(address);
	
	// Send word address
	TWI_sendMasterDataByte((u8)wordAddress);
	
	// Send Repeated start condition TO SWITCH FROM WRITE TO READ
	TWI_sendRepStartCondition();
	
	// Send slave address with read operation
	TWI_sendSlaveAddWithRead(address);
	
	// Read byte data
	TWI_receiveMasterDataByte(data); //INSTEAD OF (&R) *data = R
	
	// Send stop condition
	TWI_sendStopCondition();
	
	// Self-timed Write Cycle delay
	_delay_ms(5);
}
