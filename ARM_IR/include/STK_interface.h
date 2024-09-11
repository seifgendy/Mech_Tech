#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H

// STK Functions Prototypes
void MSTK_voidInit(void);    /* This Functiontion used to Control Systick (NOTE: This is Pre-Build).
                               And it can be controlled by "STK_config.h".             */

void MSTK_voidSetBusyWait(u32 Copy_u32Ticks);
u32 MSTK_voidGetRemainingTime(void);
u32 MSTK_voidGetElapsedTime(void);
void MSTK_voidResetTimer(void);
void MSTK_voidSTKEnable(void);
void MSTK_voidSTKDisable(void);
void MSTK_voidSetPreloadValue(u32 Copy_u32PreloadValue);
void MSTK_voidSetSingleInterval(void (*CallBackFunction) (void));
void MSTK_voidSetPeriodicInterval(void (*CallBackFunction) (void));
void SysTick_Handler(void);

#endif
