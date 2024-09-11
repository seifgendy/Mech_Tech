/*
 * RTOS_KERNEL_interface.h
 *
 *  Created on: Nov 4, 2023
 *      Author: A&G Computer World
 */

#ifndef RTOS_KERNEL_INTERFACE_H_
#define RTOS_KERNEL_INTERFACE_H_


typedef struct
{
	void(*PTaskFun)(void);//the pointer to function(task)
	u16 TaskPeriodicity;//should be the multiplies of tick time


}task_t;



void RTOS_KERNEL_voidStart(void);
void RTOS_KERNEL_voidCreatTask(u8 copy_u8Periority,u16 copy_u16Periodicity,void(*ptrTpFun)(void));//TO CREATE A TASK U SHOULD GIVE ME IT POINTER AND PERIODICITY







#endif /* RTOS_KERNEL_INTERFACE_H_ */
