/*
 * EEPROM_interface.h
 *
 * Created: 10/7/2023 11:54:03 AM
 *  Author: Kareem Hussein
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_


void EEPROM_init     (void);
void EEPROM_writeByte(u16 wordAddress, u8 data);  //MAX ADDRESS 11BIT
void EEPROM_readByte (u16 wordAddress, u8* data);

#endif /* EEPROM_INTERFACE_H_ */
