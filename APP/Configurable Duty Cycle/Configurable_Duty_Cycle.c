#include "StdTypes.h"
#include "Utils.h"

#include "DIO_Interface.h"
#include "Timer0.h"

#include "LCD_Interface.h"
#include "KeyPad_Interface.h"

#include "Configurable_Duty_Cycle.h"

#include <util/delay.h>

Operation_Phase_Type OP ; 


void Configurable_Duty_Cycle_void_Init(void)
{
	DIO_voidInit();
	H_LCD_void_Init();
	KEYPAD_voidInit();
	
	{
		Timer0_CFG CFG ; 
		CFG.OC_Mode=OC0_NON_INVERTING;
		CFG.Scaler=TIMER0_SCALER_8;
		CFG.Timer_Mode=TIMER0_FASTPWM_MODE;
		
		Timer0_void_Init(&CFG);
		
	}
	
}



static u16 stringToInt( u8 *str ,u16 *pnum , u8 size)
{
	u8  i=0 , flag=0 ;
	
	u16 n = 0 ;
	
	if(str[0]=='-')
	{
		flag=1;
		i=1;
	}
	for(; i<size; i++)
	{
		if(str[i]>='0'&&str[i]<='9')
		n=n*10+(str[i]-'0');
		else
		return 0;
	}
	if(flag==1)
	{
		n=n*(-1);
	}
	*pnum=n;
	return 1;
}


void Configurable_Duty_Cycle_void_Operation(void)
{
	u8 key = NO_KEY ;
	
	static u8 ip[MAX_POSSIBLE_DIGITS]={NULL,NULL,NULL};
	
	static u8  i = NULL ;
	
	u8 size = NULL;
	
	
	
	
	if (OP == PHASE_ONE)
	{
		H_LCD_void_SendString("Enter Duty Cycle");
		H_LCD_void_SetCursor(1,0);
		
		OP = PHASE_TWO ;
	}
	
	
	
	
	
	if (OP == PHASE_TWO )
	{
		
		key = KEYPAD_u8Getkey();
		
		if ( key != NO_KEY && key != '=')
		{
			if( key >='0' && key <='9')
			{
				H_LCD_void_SendChar(key);
				
				ip [i] = key ;
				
				i++ ;
			}
		}
		
		if( i == MAX_POSSIBLE_DIGITS || key== '=')
		
		{
			OP = PHASE_THREE ;
			size = i ;
			i = NULL ;
		}
	}
	
	
	
	
	
	if ( OP == PHASE_THREE )
	{
		_delay_ms(500);
		u16 num = NULL ;
		
		stringToInt ( ip , &num , size ); 
		
		if( num >= LEAST_DUTY_CYCLE && num <= MAX_DUTY_CYCLE )
		{
			
			H_LCD_void_Clear_Display() ; 
			
			DIO_voidWritePin(PINC0,HIGH);
			DIO_voidWritePin(PINC1,LOW);
			
			Timer0_void_setphaseCorrectPWM(TWO_M_FREQ0,num);   //SET PWM 
			H_LCD_void_SendString("Duty Now is ");
			H_LCD_void_SendIntNumber(num);
			H_LCD_void_SendString("%");
			
			
		}
		
		else
		{
			H_LCD_void_Clear_Display() ; 
			H_LCD_void_SendString("NOT Valid!! ");
		}
		
            _delay_ms(1000); 
	
	        H_LCD_void_Clear_Display() ;
	 
	        OP = PHASE_ONE ;
	
	}
	
	
	
}