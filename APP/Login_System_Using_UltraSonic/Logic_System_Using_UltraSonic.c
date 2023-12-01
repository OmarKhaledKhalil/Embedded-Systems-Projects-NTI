#include "StdTypes.h"
#include "Utils.h"

#include "DIO_Interface.h"
#include "Timer1.h"
#include "LCD_Interface.h"
#include "KeyPad_Interface.h"
#include "UltraSonic.h"

#include "Logic_System_Using_UltraSonic.h"

#include <util/delay.h>

static System_State_Type System_Status = SYSTEM_OFF;
static u16 Distance = 100000 ;

static u8  flag     = NULL   ;
void Login_System_Using_UltraSonic_Init (void)
{
	DIO_voidInit();
	H_LCD_void_Init();
	KEYPAD_voidInit();
	{
		Timer1_CFG CFG;
		
		CFG.Scaler=TIMER1_SCALER_8;
		CFG.Timer_Mode=TIMER1_NORMAL_MODE;
		
		Timer1_void_Init(&CFG);
	}
	
}
void Login_System_Using_UltraSonic_Runnable (void)
{
	static u8 i = NULL ;
	static u8 j = NULL ;
	u8 key      = NO_KEY ;
	static u8 ip[3]    = {NULL,NULL,NULL} ;
 	
	 
	 
	if( System_Status == SYSTEM_OFF )
	{
		
		if(j == MAX_ENTRY_ATTEMPTS )
		{
			H_LCD_void_SetCursor(0,0);
			H_LCD_void_SendString("System Locked");
			H_LCD_void_SetCursor(1,0);
			H_LCD_void_SendString("Wait 2 Mins");
			_delay_ms(5000);
			H_LCD_void_Clear_Display();
			j=NULL;
		}
		else
		{
			H_LCD_void_SetCursor(0,0);
			H_LCD_void_SendString("System OFF");
			
			
			Ultra_Sonic_GetRead(ULTRASONIC1,&Distance);
			
			if( Distance <= MIN_DETECTED_DISTANCE )
			{
				System_Status = SYSTEM_PASS_ENTRY ;
				
			}
	
			


		}
	}
	
	
	
	if( System_Status == SYSTEM_PASS_ENTRY )
	{
		if(flag == NULL)
		{
			H_LCD_void_SetCursor(1,0);
			H_LCD_void_SendString("Enter Password");
			H_LCD_void_SetCursor(2,0);
		}
		flag = 1 ;
		key = KEYPAD_u8Getkey();
		
		if ( key != NO_KEY)
		{
			
			if( key >='0' && key <='9')
			{
				ip [i] = key ;
				
				i++ ;
				H_LCD_void_SendChar(key);
				
				
			}
		}
		if( i == MAX_ENTRY_DIGITS )
		{ 
			if( ip [0] == '1' && ip[1] == '2' && ip[2] == '3' )
			{
				System_Status = SYSTEM_ON ;
				i=NULL;
				H_LCD_void_SetCursor(3,0);
				H_LCD_void_SendString("Right Pass");
				_delay_ms(1000);
				H_LCD_void_Clear_Display();
				flag = NULL;
			}
			else
			{
				System_Status = SYSTEM_OFF ;
				i=NULL;
				j++;
				H_LCD_void_SetCursor(3,0);
				H_LCD_void_SendString("Wrong Pass");
				_delay_ms(1000);
				H_LCD_void_Clear_Display();
				flag = NULL;
			}
		}
	}
	
	if( System_Status == SYSTEM_ON )
	{
		
		H_LCD_void_SetCursor(0,0);
		H_LCD_void_SendString("System is ON");
		H_LCD_void_SetCursor(1,0);
		H_LCD_void_SendString("Welcome Omar");
		
		DIO_voidWritePin(RELAY_PIN,HIGH);
	
	}
}