#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "EX_Interrupt.h"

#include "Leds_Reverse.h"
static volatile u8 flag=BACKWARD;
static volatile s16 level=FIRST_LAMP;

#include <util/delay.h>

static void Helper_Func_INT1(void)
{
	flag=flag^1; //toggle 0 to be 1 , 1 to be 0
}


void LEDS_voidREVERSE_Init(void)
{
	 EXI_voidEnable(EX_INT1);
	 
	 EXI_voidTriggerEdge(EX_INT1,RISING_EDGE); //External Interrupt occurs when Pin reads ground
	 
	 EXI_voidSetCallBack(EX_INT1,Helper_Func_INT1); //set Call back , to toggle(change direction)
	  DIO_voidWritePort(PA,level); // to see first lamp by default
	  _delay_ms(DELAY_VALUE_INMS); 
}

void LEDS_voidREVERSE_Run(void)
{ 
	// Periodic check in super loop 
	
	
	if(flag==FORWARD) 
	{
	 level=level<<1; //shifting to next lamp in forward direction
	 if(level>LAST_LAMP)
	 {
		 level=FIRST_LAMP; //back to first lamp after reaching last
	 }
	 DIO_voidWritePort(PA,level);
	 _delay_ms(DELAY_VALUE_INMS); //delay to see the change
	}
	if(flag==BACKWARD)
	{
		 level=level>>1; //shifting to next lamp in backward direction
		 if(level<FIRST_LAMP)
		 {
			 level=LAST_LAMP;//back to last lamp after reaching first
		 }
		 DIO_voidWritePort(PA,level);
		  _delay_ms(DELAY_VALUE_INMS); //delay to see the change
	}
}
