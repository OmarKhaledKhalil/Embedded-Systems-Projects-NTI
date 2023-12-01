#include "StdTypes.h"
#include "DIO_Interface.h"
#include "Timer1.h"

#include "UltraSonic.h"

#include <util/delay.h>


static void UltraSonic_void_Init(Ultra_Sonic_Type Ultra_Sonic)
{
	//This Function Just for Initiate the Trigger 
	
	
	//The Trigger is High pusle , 10 ms delay  , then Low Pulse to the Trigger Pin in UltraSonic from our MC.
	
	switch(Ultra_Sonic)
	{
		case ULTRASONIC1:
		DIO_voidWritePin(ULTRA_SONIC1_TRIG,HIGH);
		_delay_us(MIN_PULSE_TIME_INMICRO);
		DIO_voidWritePin(ULTRA_SONIC1_TRIG,LOW);
		break;
		
		case ULTRASONIC2:
		DIO_voidWritePin(ULTRA_SONIC2_TRIG,HIGH);
		_delay_us(MIN_PULSE_TIME_INMICRO);
		DIO_voidWritePin(ULTRA_SONIC2_TRIG,LOW);
		break;
		
		case ULTRASONIC3:
		DIO_voidWritePin(ULTRA_SONIC3_TRIG,HIGH);
		_delay_us(MIN_PULSE_TIME_INMICRO);
		DIO_voidWritePin(ULTRA_SONIC3_TRIG,LOW);
		break;
		
		case ULTRASONIC4:
		DIO_voidWritePin(ULTRA_SONIC4_TRIG,HIGH);
		_delay_us(MIN_PULSE_TIME_INMICRO);
		DIO_voidWritePin(ULTRA_SONIC4_TRIG,LOW);
		break;
	}
	
}

Read_Status UltraSonic_ReadStatusENUM_GetRead( Ultra_Sonic_Type Ultra_Sonic , u16 * distance )
{
	
		
		//Creating ENUM Obj 3lshan nshuf fe READ gat wla la2.
		Read_Status status = NO_READ ;
		
		
		//Creating u16 Variable 3lshan n5zn feh el time eli rg3 beh el ecko bta3 el ultrasonic.
		//To Calculate the Distance .
		u32 time_calculated ;
		
		
		//3aml Enum 3lshan low 3andy aktr mn UltraSonic Wa7da we a22dr aswitch ana hshtghl 3al eh ka INPUT lel Function.
		//Ultra_Sonic_Type Enum in H file .
		
		
		switch( Ultra_Sonic )
		{
			case ULTRASONIC1:
			
			//This Function Just for Initiate the Trigger 

			UltraSonic_void_Init(ULTRASONIC1);
			
			//This Function is to Count the Time Between Rising and Failling Edges in 1 Cycle using ICU.
			
			if( Timer1_u16_Count_Pulse( &time_calculated , RISING ) == COUNTING_EVENT_DONE )
			{
			   *distance= time_calculated/TIME_TOGET_ONE_CM;
				status = READ_EXIST;
			}
			
			break;
			
			case ULTRASONIC2:
			
			//This Function Just for Initiate the Trigger 

			UltraSonic_void_Init(ULTRASONIC2);
			
			//This Function is to Count the Time Between Rising and Failling Edges in 1 Cycle using ICU.
			
			if( Timer1_u16_Count_Pulse( &time_calculated , RISING ) == COUNTING_EVENT_DONE )
			{
			   *distance=time_calculated/TIME_TOGET_ONE_CM;
				status = READ_EXIST;
			}
			
			break;
			
			case ULTRASONIC3:
			
			//This Function Just for Initiate the Trigger 
			
			UltraSonic_void_Init(ULTRASONIC3);
			
			//This Function is to Count the Time Between Rising and Failling Edges in 1 Cycle using ICU.
			
			if(Timer1_u16_Count_Pulse( &time_calculated,RISING) == COUNTING_EVENT_DONE )
			{
			   *distance=time_calculated/TIME_TOGET_ONE_CM;
				status = READ_EXIST;
			}
			
			break;
			
			case ULTRASONIC4:
			
			//This Function Just for Initiate the Trigger 

			UltraSonic_void_Init( ULTRASONIC4 );
			
			//This Function is to Count the Time Between Rising and Failling Edges in 1 Cycle using ICU.
			
			if( Timer1_u16_Count_Pulse( &time_calculated , RISING ) == COUNTING_EVENT_DONE )
			{
			   *distance=time_calculated/TIME_TOGET_ONE_CM;
				status = READ_EXIST;
			}
			break;
		}
		
		//Time Between Taking 2 Readings Wra Ba3d.
		_delay_ms( TIME_BETWEEN_READINGS_INMILI );
		
		return status;
	

}