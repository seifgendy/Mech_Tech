// LIBRARY Inclusions
#include "STD_TYPES.h"
#include "BIT_MATH.h"

//Lower layer Inclusion


//self layer inclusion 
  

//self files inclucion 
#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"

#define     RCC_AHB_PRESCALER_MASK  0b1111  //it is 4 ones since we need to change the value of 4 bits in that register

// pre-build configuration it do what the below functions do but run by pre processor and consume less memory and not all function are flashed only the right condition and cannot be changed at runtime  

void RCC_voidInit(void)
{
	//////////////////////////////////////////////
	#if RCC_CLOCK_SOURCE == RCC_CLK_HSI
	SET_BIT(RCC_CR , 0);
	CLR_BIT(RCC_CR, 16);
    CLR_BIT(RCC_CR, 24);
	
	//polling (busy wait on the read only bit)
while (GET_BIT(RCC_CR ,1 ) == 0 );	
	//select this clocksource to enter your processor
CLR_BIT(RCC_CFGR , 0);
CLR_BIT(RCC_CFGR , 1);
//////////////////////////////////////////////////////////	
	
	#elif RCC_CLOCK_SOURCE == RCC_CLK_HSE
	CLR_BIT(RCC_CR , 0);
	SET_BIT(RCC_CR, 16);
    CLR_BIT(RCC_CR, 24);
//////////////////////////////////////////////////////////	
		//polling (busy wait on the read only bit)
while (GET_BIT(RCC_CR ,17 ) == 0 );	
	//select this clocksource to enter your processor
SET_BIT(RCC_CFGR , 0);
CLR_BIT(RCC_CFGR , 1);

//////////////////////////////////////////////////
  #elif RCC_CLOCK_SOURCE == RCC_CLK_PLL
	
	#if RCC_CLK_PLL_SRC  == RCC_CLK_HSI
	 CLR_BIT(RCC_PLLCFGR , 22);
	
	#elif RCC_CLK_PLL_SRC  == RCC_CLK_HSE
     SET_BIT(RCC_PLLCFGR , 22);  
	
	#else
			#error "RCC_CLK_PLL_SRC Configuration Error"
#endif
/////////////////////////////////////////////////

	CLR_BIT(RCC_CR , 0);
	SET_BIT(RCC_CR, 24); // enable PLL
    CLR_BIT(RCC_CR, 16);
	
	
	//polling (busy wait on the read only bit)
while (GET_BIT(RCC_CR ,25 ) == 0 );	
	//select this clocksource to enter your processor
CLR_BIT(RCC_CFGR , 0);
SET_BIT(RCC_CFGR , 1);


	#else
		#error "RCC_CLOCK_SOURCE configuration Error"  
#endif


/////////////////////////////////////////////////////
//AHB prescaller value


/**

#if RCC_AHB_PRESCALER == RCC_AHB_DIV_1
	CLR_BIT(RCC_CFGR , 4 );
	CLR_BIT(RCC_CFGR , 5 );
	CLR_BIT(RCC_CFGR , 6 );
	CLR_BIT(RCC_CFGR , 7 );
	
#elif RCC_AHB_PRESCALER == RCC_AHB_DIV_2        old way and not practical
	CLR_BIT(RCC_CFGR , 4 );
	CLR_BIT(RCC_CFGR , 5 );
	CLR_BIT(RCC_CFGR , 6 );
	SET_BIT(RCC_CFGR , 7 );

**/
 
// better method with bitmasking

RCC_CFGR  &= ~(RCC_AHB_PRESCALER_MASK << 4 ) ;
RCC_CFGR  |= (RCC_AHB_PRESCALER << 4 );

////////////////////////////////////////////////////
//APB1 prescaller value

RCC_CFGR  &= ~(RCC_APB1_PRESCALER_MASK << 10 ) ;
RCC_CFGR  |= (RCC_APB1_PRESCALER << 10 );
//APB2 prescaller value
RCC_CFGR  &= ~(RCC_APB2_PRESCALER_MASK << 13 ) ;
RCC_CFGR  |= (RCC_APB2_PRESCALER << 13 );
// 10 and 13 according to the bits starting position in the register 
		
}



 /*
      0 -> HSI 
	  1 -> HSE
	  2 -> PLL
 */



/*
 this is the enable func of this prephiral it take the clock src and according to its value it acces the RCC_CR register which is the register in RCC 
responsible for having the pins that select the activated clock src

*/


void RCC_voidEnableClockSource(u8 copy_u8ClockSource)

{
///////////////////////////////////////////////////////////////////////
if(copy_u8ClockSource == RCC_HSI  )
{
	SET_BIT(RCC_CR,0);  //put in bit zero in register RCC_CR value one   
}
///////////////////////////////////////////////////////////////////////
else if (copy_u8ClockSource == RCC_HSE)
{
SET_BIT(RCC_CR,16);
}
///////////////////////////////////////////////////////////////////////
else if (copy_u8ClockSource == RCC_PLL)
{
SET_BIT(RCC_CR,24);
}
///////////////////////////////////////////////////////////////////////
	

}





/*
this is the disable function

*/

	void RCC_voidDisableClockSpource(u8 copy_u8ClockSource)

{
///////////////////////////////////////////////////////////////////////
if(copy_u8ClockSource == RCC_HSI )
{
	CLR_BIT(RCC_CR,0);  //put in bit zero in register RCC_CR value zero   
}
///////////////////////////////////////////////////////////////////////
else if (copy_u8ClockSource == RCC_HSE)
{
    CLR_BIT(RCC_CR,16);
}
///////////////////////////////////////////////////////////////////////
else if (copy_u8ClockSource == RCC_PLL)
{
    CLR_BIT(RCC_CR,24);
}
///////////////////////////////////////////////////////////////////////
	

}

//this function allow you to send your clocks to a specific prephiral on a specific bus  ch 6.3.9

   //RCC_voidEnablePrephiralClock( RCC_AHB , RCC_GPIOA); //example on gpio prephiral 

    void RCC_voidEnablePrephiralClock( u8 Copy_u8BusName , u8 Copy_u8PeripheralName)  
	{
		
		switch(Copy_u8BusName)
		{
			
		case RCC_AHB:
            SET_BIT(RCC_AHB1ENR , Copy_u8PeripheralName);// in order to set this bus you need to acces this register and set this bit 
			//note that AHB1 only have GGPIOA prephiral
			
        break;
		/////////
		case RCC_APB1:
        SET_BIT(RCC_APB1ENR , Copy_u8PeripheralName);// in order to set this bus you need to acces this register and set this bit 
			//note that APB1  have more than one  prephiral
        break;	
		/////////
		case RCC_APB2:
             SET_BIT(RCC_APB2ENR , Copy_u8PeripheralName);// in order to set this bus you need to acces this register and set this bit 
			//note that APB2 have more than one prephiral
        break;				
		//////////
		default:
		// ERROR
		break;
		
		}
		
			
	}
	
	
	    void RCC_voidDisablePrephiralClock( u8 Copy_u8BusName , u8 Copy_u8PeripheralName)  
	{
		
		switch(Copy_u8BusName)
		{
			
		case RCC_AHB:
            CLR_BIT(RCC_AHB1ENR , Copy_u8PeripheralName);// in order to set this bus you need to acces this register and set this bit 
			//note that AHB1 only have GGPIOA prephiral
			
        break;
		/////////
		case RCC_APB1:
             CLR_BIT(RCC_APB1ENR , Copy_u8PeripheralName);// in order to set this bus you need to acces this register and set this bit 
			//note that APB1  have more than one  prephiral
        break;	
		/////////
		case RCC_APB2:
             CLR_BIT(RCC_APB2ENR , Copy_u8PeripheralName);// in order to set this bus you need to acces this register and set this bit 
			//note that APB2 have more than one prephiral
        break;				
		//////////
		default:
		// ERROR
		break;
		
		}
		
			
	} 
