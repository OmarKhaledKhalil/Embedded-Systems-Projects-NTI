#ifndef WATCHDOG_INTERFACE_H_
#define WATCHDOG_INTERFACE_H_

typedef enum 
{
	SIXTEEN_MS        =0,
	THIRTY_TWO_MS     =1,
	SIXTY_FIVE_MS     =2,
	THIRTEEN_S        =3,
	TWENTY_SIX_S      =4,
	FIFTY_TWO_S       =5,
	ONE_S             =6,
	TWO_S             =7
	
}WatchDog_SleepingTimes;


void WDT_void_Enable();

void WDT_Disable();

void WDT_void_sleep(WatchDog_SleepingTimes sleepTime);

void WDT_void_refresh();

u8 WDT_u8_DisableOperation_Indicator();



#endif 