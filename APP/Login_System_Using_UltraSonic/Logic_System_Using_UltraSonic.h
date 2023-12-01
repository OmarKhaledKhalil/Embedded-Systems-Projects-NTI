#ifndef LOGIC_SYSTEM_USING_ULTRASONIC_H_
#define LOGIC_SYSTEM_USING_ULTRASONIC_H_

#define MAX_ENTRY_DIGITS         3 
#define MAX_ENTRY_ATTEMPTS       3
#define MIN_DETECTED_DISTANCE    15
#define RELAY_PIN                PINC1 

typedef enum
{
	
	SYSTEM_OFF=0,
	SYSTEM_PASS_ENTRY=1,
	SYSTEM_ON=2
	
}System_State_Type;

void Login_System_Using_UltraSonic_Init (void);
void Login_System_Using_UltraSonic_Runnable (void); 


#endif