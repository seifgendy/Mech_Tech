/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "RTOS_TIMER_interface.h"
#include "RTOS_TIMER_private.h"


static void (*private_pCallBackCTC)(void)=NULL;


void RTOS_TIMER_init(void)
{

    // Select Mode = CTC Mode
	CLR_BIT(TCCR2,WGM20);
	SET_BIT(TCCR2,WGM21);

	// Enable OC Interrupt
	SET_BIT(TIMSK,OCIE2);

}


void RTOS_TIMER_start(void)
{
	// Select Prescaler Value = 64
	SET_BIT(TCCR2,CS20);
	SET_BIT(TCCR2,CS21);
	CLR_BIT(TCCR2,CS22);
}


void RTOS_TIMER_stop(void)
{
	// Select Prescaler Value = 0
	    CLR_BIT(TCCR2,CS20);
		CLR_BIT(TCCR2,CS21);
		CLR_BIT(TCCR2,CS22);
}


void RTOS_TIMER_setCompareMatchValue(u8 copy_u8CompareValue)
{
	OCR2 = copy_u8CompareValue;
}

void RTOS_TIMER_setCallBackCTC(void(*ptrToFun)(void))
{
	if(ptrToFun!=NULL)
	{
		private_pCallBackCTC = ptrToFun;
	}
}


void __vector_4(void) __attribute__ ((signal));
void __vector_4(void)
{
	//call action
			if(private_pCallBackCTC != NULL)
			{
				private_pCallBackCTC();
			}

}






