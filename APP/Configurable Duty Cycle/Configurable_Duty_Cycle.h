#ifndef CONFIGURABLE_DUTY_CYCLE_H_
#define CONFIGURABLE_DUTY_CYCLE_H_


#define  MAX_POSSIBLE_DIGITS     3 

#define LEAST_DUTY_CYCLE         0
#define MAX_DUTY_CYCLE          100

typedef enum 
{
	PHASE_ONE,
	PHASE_TWO,
	PHASE_THREE
}Operation_Phase_Type;

void Configurable_Duty_Cycle_void_Init(void);
void Configurable_Duty_Cycle_void_Operation(void);



#endif