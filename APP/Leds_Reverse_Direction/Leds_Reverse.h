#ifndef LEDS_REVERSE_H_
#define LEDS_REVERSE_H_

#define LEDS_PORT PA

#define FIRST_LAMP 1
#define LAST_LAMP 128 

#define FORWARD 1
#define BACKWARD 0

#define DELAY_VALUE_INMS 250

void LEDS_voidREVERSE_Init(void);

void LEDS_voidREVERSE_Run(void);


#endif 