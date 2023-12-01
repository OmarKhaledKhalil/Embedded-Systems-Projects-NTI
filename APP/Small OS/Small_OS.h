#ifndef SMALL_OS_H_
#define SMALL_OS_H_

#define TIMER_STARTING_VALUE  5

#define REQUIRED_OVF_FOR_HALF_SECOND      2000
#define REQUIRED_OVF_FOR_ONE_SECOND       4000
#define REQUIRED_OVF_FOR_THREE_SECOND     12000

#define BUTTON_PIN     PINC0
#define BLUE_LED_PIN   PINC1
#define RED_LED_PIN    PINC2
#define GREEN_LED_PIN  PINC3



typedef enum 
{
	OP_OFF = 0 ,
	OP_ON  = 1
	
}Operation_Status_Type;

void Small_OS_void_Init(void);
void Small_OS_void_Operation(void);


#endif