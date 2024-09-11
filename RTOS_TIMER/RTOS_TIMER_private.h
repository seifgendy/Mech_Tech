/*
 * RTOS_TIMER_private.h
 *
 *  Created on: Nov 4, 2023
 *      Author: A&G Computer World
 */

#ifndef RTOS_TIMER_PRIVATE_H_
#define RTOS_TIMER_PRIVATE_H_



                             /* RTOS_TIMER REGISTERS*/

// RTOS_TIMER Control Register A
#define TCCR2             (*(volatile u8*)0x45)
#define CS20             0
#define CS21              1
#define CS22              2
#define WGM21              3
#define COM20             4
#define COM21             5
#define  WGM20             6
#define FOC2             7

// Timer/Counter Register
#define TCNT2            (*(volatile u8*)0x44)

// Output Compare Register
#define OCR2             (*(volatile u8*)0x43)

// Timer/Counter Interrupt Mask Register
#define TIMSK            (*(volatile u8*)0x59)
#define TOIE2            6
#define OCIE2            7

// Timer/Counter Interrupt Flag Register
#define TIFR             (*(volatile u8*)0x58)
#define TOV2             6
#define OCF2             7


#endif /* RTOS_TIMER_PRIVATE_H_ */
