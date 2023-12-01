#ifndef RTC_INTERFACE_H_
#define RTC_INTERFACE_H_

#define RTC_WRITE_FIXED_ADDRESS   0xD0
#define RTC_READ_FIXED_ADDRESS    0xD1
#define RTC_SECONDS_ADDRESS       0X00
#define RTC_DAY_ADDRESS           0x03

typedef enum
{
	ERROR=0,
	SUCCESS
	
}RTC_OP_Status;

typedef enum 
{
	AM=0,
	PM=1
}Time_Format;

typedef struct	 
{
	u8 Second;  // from 0 to 59
	u8 Minute;  // from 0 to 59
	u8 Hour;    // from 0 to 24 or from  1 to 12 
	Time_Format AMPM;    // 0 or 1
}RTC_Time;
 
typedef struct
{
	u8 day;
	u8 date;
	u8 month;
	u8 year;
	
}RTC_Date; 

void RTC_void_Init(void);
RTC_OP_Status RTC_void_setTime(const RTC_Time* RTC_Time_obj);
RTC_OP_Status RTC_void_getTime(RTC_Time* RTC_Time_obj);
RTC_OP_Status RTC_void_setDate(const RTC_Date* RTC_Date_obj);
RTC_OP_Status RTC_void_getDate(RTC_Date* RTC_Date_obj);
#endif