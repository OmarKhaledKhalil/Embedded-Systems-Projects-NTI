#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#define ULTRA_SONIC1_TRIG  PINC0
#define ULTRA_SONIC2_TRIG  PINC1
#define ULTRA_SONIC3_TRIG  PINC2
#define ULTRA_SONIC4_TRIG  PINC3


#define MIN_PULSE_TIME_INMICRO         10
#define TIME_BETWEEN_READINGS_INMILI   10
#define TIME_OUT_INMICRO               6000
#define TIME_TOGET_ONE_CM              58



//This Enum for Choosing Which UltraSonic To work at.
typedef enum
{
	ULTRASONIC1=0,
	ULTRASONIC2=1,
	ULTRASONIC3=2,
	ULTRASONIC4=3,
	TOTAL_ULTRA_SONIC
	
}Ultra_Sonic_Type;


//This Enum for Reading Exists or Not Checking.
typedef enum
{
	NO_READ=0,
	READ_EXIST=1
	
}Read_Status;


Read_Status UltraSonic_ReadStatusENUM_GetRead(Ultra_Sonic_Type Ultra_Sonic,u16*distance);




#endif