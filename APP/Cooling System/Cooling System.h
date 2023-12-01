
#ifndef COOLING SYSTEM_H_
#define COOLING SYSTEM_H_

#define RELAY1_PIN PINC0
#define RELAY2_PIN PINC1

#define FIRST_TEMP_BOUNDARY 20

#define SECOND_TEMP_BOUNDARY 25

#define THIRD_TEMP_BOUNDARY 35

void CoolingSystem_void_Init(void);
void CoolingSystem_Void_Operation(void);

#endif 