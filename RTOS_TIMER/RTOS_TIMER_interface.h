/*
 * RTOS_TIMER_interface.h
 *
 *  Created on: Nov 4, 2023
 *      Author: A&G Computer World
 */

#ifndef RTOS_TIMER_INTERFACE_H_
#define RTOS_TIMER_INTERFACE_H_




                /*************** APIS PROTOTYPES ***************/
void RTOS_TIMER_init                (void);
void RTOS_TIMER_start               (void);
void RTOS_TIMER_stop                (void);
//void RTOS_TIMER_setCallBackOVF      (void(*ptrToFun)(void));
void RTOS_TIMER_setCallBackCTC      (void(*ptrToFun)(void));
void RTOS_TIMER_setCompareMatchValue(u8 copy_u8CompareValue);
void RTOS_TIMER_setDelay_ms_usingCTC(u16 delay_ms);




#endif /* RTOS_TIMER_INTERFACE_H_ */
