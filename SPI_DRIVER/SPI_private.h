/*
 * SPI_private.h
 *
 * Created: 10/6/2023 7:35:58 PM
 *  Author: Kareem Hussein
 */ 
#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

//since  spi regs are arranged after each other
typedef struct
{
	u8 SPCR;  //the regs from smaller addres to higher
	u8 SPSR;
	u8 SPDR;
}SPI_REGS;

#define SPI          ((volatile SPI_REGS*)0x2D) //pointer to regs//to write in a regs do this SPI->SPSR

#define SPR0         0  //prescaler
#define SPR1         1  //prescaler
#define CPHA         2
#define CPOL         3
#define MSTR         4
#define DORD         5  //LSB select
#define SPE          6  //enable bit
#define SPIE         7

#define SPI2X        0 // double speed
#define WCOL         6 // collision flag
#define SPIF         7 // interupt flag

#endif /* SPI_PRIVATE_H_ */
