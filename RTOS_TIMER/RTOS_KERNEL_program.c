/*
 * RTOS_KERNEL_program.c
 *
 *  Created on: Nov 4, 2023
 *      Author: A&G Computer World
 */
//THE RTOS IS THE MANAGER OF THE WHOLR SYSTEM IT CAN CALL FROM THE HALL FUNCTIONS LIKE TIMER AND GLOBAL INTRUPTS
//THE KERNEL IS THE MANAGER IN THE RTOS
//THE APPLICATION IMPLEMENT THE TASKS WHILE THE KERNEL CALL THEM
#include "STD_TYPES.h"
#include "BIT_MATH.h"



#include "DIO_interface.h"
#include "GI_interface.h"
#include "RTOS_TIMER_interface.h"
#include "RTOS_KERNEL_interface.h"
#include "RTOS_KERNEL_config.h"
#include "RTOS_KERNEL_private.h"

//THE ARRAY SHOULD BE STATIC GLOBAL SO THAT THE SCHEDULAR AND THE CREAT TASK CAN ACCES IT
static task_t private_arrOfTasks[RTOS_KERNEL_TASK_NUM ] ;


//THIS FUNCTION CALL THE TIMER AND MAKE IT CALL THE SCHEDULAR EVERY 1MS (THIS TIME SHOULD BE CALCULATED ACORDING TO TIME OF EXCUTION OF THE TASKS (FUNCTIONS))
void RTOS_KERNEL_voidStart(void){

	GI_enable();//TO ALLOW TIMER TO GENERATE THE INTURREPTS THAT WILL SEE THE SCHEDULAR TASKS EVERY TIME
	RTOS_TIMER_init(); //START THE TIMER DEDICATED FOR THE RTOS IN THIS CASE TMR2
	RTOS_TIMER_setCompareMatchValue(249); //TO FIRE EVERY 1MS
	RTOS_TIMER_setCallBackCTC(&private_voidScheduler);//THIS FUNC CALL THE SCHEDULER FUNC EVERY  1MS
	RTOS_TIMER_start();


}



void RTOS_KERNEL_voidCreateTask(u8 copy_u8Periority,u16 copy_u16Periodicity,void(*ptrTpFun)(void))
{
//THIS ARRAY THE SCHEDULAR FILL IT UP WHILE THE SHEDULAR WILL LOOP ON IT
//TO AVOID THE DEPENDENCY OF THE SCHEDULAR ON THE NUMBER OF TASKS SO WE PUT THE TASKS IN AN ARRAY
if(copy_u8Periority<RTOS_KERNEL_TASK_NUM && (ptrTpFun != NULL) && ( private_arrOfTasks[copy_u8Periority].PTaskFun == NULL))//to assure the number of priorities is not more than the number of tasks
	//i will make the array arranged according to priority                                                                      //and to avoid overriding a task that is already written before in this priority order so i check if the pointer to func has value then this place already has a func before
{
	private_arrOfTasks[copy_u8Periority].PTaskFun = ptrTpFun ;//put the address of the task that u send to the func and put to u these task in the array of task
	private_arrOfTasks[copy_u8Periority].TaskPeriodicity = copy_u16Periodicity ;//then i put its periority in the same place of the task
}

}


static void private_voidScheduler(void)
{
static u16 local_u16TickCount = 0 ; //this counter to let me know i am on which rtos tick
local_u16TickCount ++ ;//the uart_timer interrupt get me back here after each tick to ask all the tasks again wether should i excute u in this tick or no

u8 Local_u8TaskCounter;//count the number of tasks in the array to stop the for loop on reaching last task
for(Local_u8TaskCounter=0;Local_u8TaskCounter<RTOS_KERNEL_TASK_NUM;Local_u8TaskCounter++)
{

	//to check wether the tick count that we are standing on it is one of the multiplities of the task periodicity which means that the task should be excuted again
	if (local_u16TickCount%(private_arrOfTasks[Local_u8TaskCounter].TaskPeriodicity) == 0 )
	{
if (private_arrOfTasks[Local_u8TaskCounter].PTaskFun != NULL)
{
	//call the pointer that carry the address of the func so know the func is called
	private_arrOfTasks[Local_u8TaskCounter].PTaskFun();
}
	}





}
}
