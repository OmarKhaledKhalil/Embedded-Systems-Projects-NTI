#include "StdTypes.h"
#include "Utils.h"
#include "MCU_HW.h"

#include "WatchDog_Interface.h"


static u8 Disable_Flag = 0;

void WDT_void_Enable()
{
	/* Write logical one to WDE to Enable WatchDog Timer */
	WDTCR = (1<<WDE);
	Disable_Flag =0 ;
}

void WDT_void_Disable()
{
	/* Write logical one to WDTOE and WDE */
	WDTCR |= (1<<WDTOE) | (1<<WDE);
	/* Turn off WDT */
	WDTCR = 0x00;
	if ( READ_BIT(WDTCR,WDE) == NULL )
	{
		Disable_Flag = 1;
	}

}

u8 WDT_u8_DisableOperation_Indicator()
{
	return Disable_Flag;
}

void WDT_void_sleep(WatchDog_SleepingTimes sleepTime)
{
	WDT_void_Disable();
	WDTCR=sleepTime;
	WDT_void_Enable();
}

void WDT_void_refresh()
{
	WDR();
}