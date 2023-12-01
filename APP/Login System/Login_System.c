#include "StdTypes.h"
#include "Utils.h"

#include "DIO_Interface.h"
#include "Timer1.h"
#include "UltraSonic.h"
#include "LCD_Interface.h"
#include "KeyPad_Interface.h"



void Login_System_void_Init(void)
{
	DIO_voidInit();
	H_LCD_void_Init();
	
	{
		Timer1_CFG CFG;
		CFG.Scaler=TIMER1_SCALER_8;
		CFG.Timer_Mode=TIMER1_NORMAL_MODE;
	}
}


void Login_System_void_Operation(void)
{
	
}