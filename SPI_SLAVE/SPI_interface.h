/*
 * SPI_interface.h
 *
 * Created: 10/6/2023 7:35:49 PM
 *  Author: Kareem Hussein
 */ 


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_


void SPI_initMaster          (void);
void SPI_initSlave           (void);
void SPI_transieve           (u8 TxData, u8* RxData);
void SPI_transmitAsynchronous(u8 TxData, void(*ptrToFun)(u8 RxData));


#endif /* SPI_INTERFACE_H_ */