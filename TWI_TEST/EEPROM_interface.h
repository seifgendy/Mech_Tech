/*
 * EEPROM_interface.h
 *
 * Created: 10/13/2023 10:10:16 PM
 *  Author: Kareem Hussein
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_


void EEPROM_init     (void);
void EEPROM_writeByte(u16 wordAddress, u8 data);
void EEPROM_readByte (u16 wordAddress, u8* data);

#endif /* EEPROM_INTERFACE_H_ */