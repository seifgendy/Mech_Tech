
// Library Inclusion
# include "../include/STD_TYPES.h"
# include "../include/BIT_MATH.h"

// Lower Layer Inclusion

// Self Layer Inclusion

// Self Files Inclusion
# include "../include/STK_interface.h"
# include "../include/STK_private.h"
# include "../include/STK_config.h"

static void (*pNotificationFunction)(void) = NULLPTR;
static u8 u8IntervalTypeFlag = SINGLE_INTERVAL;

void MSTK_voidInit(void)
{
  // Select STK Clock Source (STK_AHB_DIV_1 or STK_AHB_DIV_8)
  #if STK_SRC_CLK == STK_AHB_DIV_1
     SET_BIT(STK->CTRL, STK_BIT_2);
  #elif STK_SRC_CLK == STK_AHB_DIV_8
     CLR_BIT(STK->CTRL, STK_BIT_2);
  #else
     #error "STK_CLOCK_SOURCE Configuration Error"
  #endif

  // Control STK Interrupt (Enable or Disable)
  #if STK_INTERRUPT == STK_ENABLE
     SET_BIT(STK->CTRL, STK_BIT_1);
  #elif STK_INTERRUPT == STK_DISABLE
     CLR_BIT(STK->CTRL, STK_BIT_1);
  #else
     #error "STK_Interrupt Configuration Error"
  #endif

  // Control STK Power (Enable or Disable)
  #if STK_POWER == STK_ENABLE
     SET_BIT(STK->CTRL, STK_BIT_0);
  #elif STK_POWER == STK_DISABLE
     CLR_BIT(STK->CTRL, STK_BIT_0);
  #else
     #error "STK_Power Configuration Error"
  #endif
}


void MSTK_voidSetBusyWait(u32 Copy_u32Ticks)
{
   STK->LOAD =  Copy_u32Ticks;
   while(GET_BIT(STK->CTRL, STK_BIT_16) == ZERO);
   STK->VAL= 0;
}


u32 MSTK_voidGetRemainingTime(void)
{
  return STK->VAL;
}


u32 MSTK_voidGetElapsedTime(void)
{
	u32 Local_u32ElapsedTime;
	Local_u32ElapsedTime = STK->LOAD - STK->VAL;
    return Local_u32ElapsedTime;
}


void MSTK_voidResetTimer(void)
{
    STK -> VAL = ZERO;
}


void MSTK_voidSTKEnable(void)
{
	SET_BIT(STK->CTRL, STK_BIT_0);
}


void MSTK_voidSTKDisable(void)
{
	CLR_BIT(STK->CTRL, STK_BIT_0);
}


void MSTK_voidSetPreloadValue(u32 Copy_u32PreloadValue)
{
    STK -> LOAD = Copy_u32PreloadValue;
}


void MSTK_voidSetSingleInterval(void (*CallBackFunction) (void))
{
    pNotificationFunction = CallBackFunction;
    u8IntervalTypeFlag = SINGLE_INTERVAL;
    SET_BIT(STK->CTRL, STK_BIT_0);
}


void MSTK_voidSetPeriodicInterval(void (*CallBackFunction) (void))
{
    pNotificationFunction = CallBackFunction;
    u8IntervalTypeFlag = PERIODIC_INTERVAL;
}


void SysTick_Handler(void)
{
    u8 LocalTempVar = ZERO;
    if(u8IntervalTypeFlag == SINGLE_INTERVAL)
    {
        // Disable Timer
        STK -> LOAD = ZERO;
        STK -> VAL = ZERO;
        CLR_BIT(STK->CTRL, STK_BIT_0);
    }
    if(pNotificationFunction != NULLPTR)
    {
        pNotificationFunction();
    }
    // Flag Clearance
    LocalTempVar = GET_BIT(STK -> CTRL, STK_BIT_16);
}
