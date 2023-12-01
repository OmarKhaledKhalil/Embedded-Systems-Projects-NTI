#include "StdTypes.h"

#include "Utils.h"

#include "DIO_Interface.h"

#include "Timer0.h"

#include "Small_OS.h"


Operation_Status_Type Operation1_Flag = OP_OFF ;
Operation_Status_Type Operation2_Flag = OP_OFF ;
Operation_Status_Type Operation3_Flag = OP_OFF ;

static void Schedular_Function (void)
{
	    static u32 Counter = NULL  ;
		
		if( Counter != NULL )
	{
	    if( Counter % REQUIRED_OVF_FOR_HALF_SECOND   == NULL )
	  {  
		    Operation1_Flag = OP_ON   ;
		
		if( Counter % REQUIRED_OVF_FOR_ONE_SECOND    == NULL )
		{
			Operation2_Flag = OP_ON   ;
		}
		
		if( Counter % REQUIRED_OVF_FOR_THREE_SECOND  == NULL )
		{
			Operation3_Flag = OP_ON   ;
			Counter         = NULL ;
		}
		
	  }
	}
	        Counter ++ ;
	
}



void Small_OS_void_Init(void)
{
	DIO_voidInit() ;
	
	{
		Timer0_CFG CFG  ;
		
		CFG.Scaler     = TIMER0_SCALER_8    ;  
		CFG.Timer_Mode = TIMER0_NORMAL_MODE ;  
		Timer0_void_Init( &CFG )            ;                
	}
	
	
	Timer0_void_OVF_SetCallBack(Schedular_Function) ; 
	Timer0_void_SetCounts(TIMER_STARTING_VALUE)     ;
	Timer0_void_OV_InterruptEnable()                ;
	
	
}


void Small_OS_void_Operation(void)
{
	
	//TASK 1 
	
	if( Operation1_Flag == OP_ON )
	{
		if( DIO_ReadPin(BUTTON_PIN) == LOW )
		{
			DIO_voidTogglePin(BLUE_LED_PIN) ;
		}
		    Operation1_Flag = OP_OFF        ;
	}
	
	
	//TASK 2
	
	if( Operation2_Flag == OP_ON )
	{
		DIO_voidTogglePin(RED_LED_PIN)  ;
		
		Operation2_Flag = OP_OFF        ;
	}
	
	
	//TASK 3
	
	if( Operation3_Flag == OP_ON )
	{
		DIO_voidTogglePin(GREEN_LED_PIN)  ;
		
		Operation3_Flag = OP_OFF          ;
		
		
		Timer0_void_SetCounts(TIMER_STARTING_VALUE) ;
	}
	
}

