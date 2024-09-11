/*
 * TWI_program.c
 *
 * Created: 10/7/2023 10:36:30 PM
 *  Author: Kareem Hussein
 */ 


 /* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "TWI_interface.h"
#include "TWI_private.h"


void TWI_initMaster(void)
{
	//prescaler = 1 set freq = 400khz
	CLR_BIT(TWSR,TWPS0);
	CLR_BIT(TWSR,TWPS1);
	TWBR = 12;
	
	// enable ack that check that each ack hae certain value from the data sheet the ack help mecheck that each step and part in the frame is succefly send or recieved but i must enable this bit bit to allow the micro cont to send this ack// Enable ACK
	SET_BIT(TWCR,TWEA);
	
	// Enable TWI Peripheral
	SET_BIT(TWCR,TWEN);
}


void TWI_sendStartCondition(void)
{
	// Request Start Condition
	SET_BIT(TWCR,TWSTA);
	
	//CLEAR FLAG TO START CURRENT JOB (THIS IS THE FLAG THAT ALWAYS GET RAISED AFTER NEARLY EVERY THING AND I CANNOT DO ANY THING UNTIL I LOW IT )
	SET_BIT(TWCR,TWINT);
	
	 //BUSY WAIT FOR THE FLAG TO ASSURE THAT MY START REQ IS DONE
	while(0 == GET_BIT(TWCR,TWINT));
	
	//the acknowlgment to make sure that it is positive compare it with the vlu in the data sheet for each acknowlgment in this case 0X08
	while(TWI_STATUS_VALUE != TWI_START_CONDITION_ACK);
}

//the functionthat allow master to stay on the bus it has diff status value thats why i made a separate func for it
void TWI_sendRepStartCondition(void)
{
	// Request Start Condition
	SET_BIT(TWCR,TWSTA);
	
	//CLEAR FLAG TO START CURRENT JOB (THIS IS THE FLAG THAT ALWAYS GET RAISED AFTER NEARLY EVERY THING AND I CANNOT DO ANY THING UNTIL I LOW IT )
	SET_BIT(TWCR,TWINT);
	
	//BUSY WAIT FOR THE FLAG TO ASSURE THAT MY START REQ IS DONE
	while(0 == GET_BIT(TWCR,TWINT));
	
	 //the acknowlgment to make sure that it is positive compare it with the vlu in the data sheet for each acknowlgment in this case 0X10
	while(TWI_STATUS_VALUE != TWI_REP_START_CONDITION_ACK);
}


void TWI_sendStopCondition(void)
{
	// Request Stop Condition
	SET_BIT(TWCR,TWSTO);
	
	 //clr flag to start current job (no need for blocking since stop is the last thing in the frame)
	SET_BIT(TWCR,TWINT);
}

//THE MASTER CALL IT AND GIVE IT ADDRESS
void TWI_sendSlaveAddWithWrite(u8 slaveAdd)
{
	if(slaveAdd<128)
	{
		TWDR = slaveAdd<<1;//SINCE THE ADDRESS IS 7 BIT
		
		// Select read operation //THE 8TH BIT AFTER DATA
		CLR_BIT(TWDR,0);
		
		// Clear SC bit//CLEAR START CONDITION BIT (CONSTRAIN IN THE DATA SHEET)
		CLR_BIT(TWCR,TWSTA);
		
		// Clear flag to start current job
	    SET_BIT(TWCR,TWINT);
	    
	    // Busy Wait for the flag 
	    while(0 == GET_BIT(TWCR,TWINT));//TO BE SURE SLAVE ADDRESS IS SENT
		
		// Check ACK = Master transmit ( slave address + Write request )
		while(TWI_STATUS_VALUE != TWI_SLAVE_ADDRESS_WRITE_ACK);
	}
}


void TWI_sendSlaveAddWithRead(u8 slaveAdd)
{
	if(slaveAdd<128)
	{
		TWDR = slaveAdd<<1;
		
		// Select read operation
		SET_BIT(TWDR,0);
		
		// Clear SC bit
		CLR_BIT(TWCR,TWSTA);
		
		// Clear flag to start current job
	    SET_BIT(TWCR,TWINT);
	    
	    // Busy Wait for the flag 
	    while(0 == GET_BIT(TWCR,TWINT));
		
		 // Check ACK = Master transmit ( slave address + Read request ) ACK
		while(TWI_STATUS_VALUE != TWI_SLAVE_ADDRESS_READ_ACK);
	}
}


void TWI_sendMasterDataByte(u8 TxData)
{
	// Write Data into data register
	TWDR = TxData;
	
	// Clear flag to start current job
	SET_BIT(TWCR,TWINT);
	
	// Busy Wait for the flag 
	while(0 == GET_BIT(TWCR,TWINT));
	
	// Check ACK = Master transmit data ACK
	while(TWI_STATUS_VALUE != TWI_MASTER_DATA_TRANSMIT_ACK);
}


void TWI_receiveMasterDataByte(u8* RxData)
{
	if(RxData != NULL)
	{
		// Clear flag to start current job
	    SET_BIT(TWCR,TWINT);
		
		// Busy Wait for the flag 
	    while(0 == GET_BIT(TWCR,TWINT));
		
		// Check ACK = Master received data with ACK
		while(TWI_STATUS_VALUE != TWI_MASTER_DATA_RECIEVE_ACK);
		
		// Read Data from data register
		*RxData = TWDR;
	}
}
