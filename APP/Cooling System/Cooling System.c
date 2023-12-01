#include "StdTypes.h"
#include "DIO_Interface.h"
#include "ADC_Interface.h"
#include "Sensors.h"
#include "LCD_Interface.h"

#include "Cooling System.h"

#include <util/delay.h>

static u8 Temp;




void CoolingSystem_void_Init(void)
{
	DIO_voidInit();
	LM35_void_Init();
	H_LCD_void_Init();
	
}

void CoolingSystem_Void_Operation(void)
{
	if( LM35_u16_ReadTemp( LM35_CHANNEL , &Temp ) )
	{
		
		
		if ( Temp < FIRST_TEMP_BOUNDARY )
		{
			DIO_voidWritePin( RELAY1_PIN , LOW ) ;
			DIO_voidWritePin( RELAY2_PIN , LOW ) ;
		}
		if( Temp >= SECOND_TEMP_BOUNDARY && Temp < THIRD_TEMP_BOUNDARY )
		{
			DIO_voidWritePin( RELAY1_PIN , HIGH );
			DIO_voidWritePin( RELAY2_PIN , LOW ) ;
		}
		if( Temp > THIRD_TEMP_BOUNDARY)
		{
			DIO_voidWritePin( RELAY1_PIN , LOW ) ;
			DIO_voidWritePin( RELAY2_PIN , HIGH );
		}
		
	}
	

	    H_LCD_void_SendString("Temp is : ");
		H_LCD_void_SendIntNumber(Temp);
		H_LCD_void_SendString(" .C");
		H_LCD_void_SendString("                           ");
		H_LCD_void_SetCursor(0,0);
	
}