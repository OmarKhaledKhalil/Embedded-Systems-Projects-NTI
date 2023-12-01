#include "StdTypes.h"
#include "Utils.h"

#include "I2C_Interface.h"

#include "RTC_Interface.h"



void RTC_void_Init(void)
{
	TWI_void_Init(ONE_HUNDRED_KHZ);
}

RTC_OP_Status RTC_void_setTime( const RTC_Time* RTC_Time_obj)
{
	u8 status;
	
	TWI_void_sendStart();
	
	
	TWI_void_getStatus(&status);
	if(status==MT_START_CONDITION_TRANSMITTED)
	{
		 /* Start I2C communication with RTC and Write address to read */
		TWI_void_sendByte(RTC_WRITE_FIXED_ADDRESS);
	}
	else
	{
		return ERROR ;
	}
	
	
	TWI_void_getStatus(&status);
	if(status==MT_SLA_W_TRANSMITTED_ACK_RECEIVED)
	{
		/* Write address for second */
		TWI_void_sendByte(RTC_SECONDS_ADDRESS);
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MT_DATA_TRANSMITTED_ACK_RECEIVED)
	{
		/* Write data for second */
		TWI_void_sendByte(RTC_Time_obj->Second);
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MT_DATA_TRANSMITTED_ACK_RECEIVED)
	{
		/* Write data for minute */
		TWI_void_sendByte(RTC_Time_obj->Minute);
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MT_DATA_TRANSMITTED_ACK_RECEIVED)
	{
		/* Write data for hour with choice AM or PM */
		TWI_void_sendByte(RTC_Time_obj->Hour|RTC_Time_obj->AMPM);
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MT_DATA_TRANSMITTED_ACK_RECEIVED)
	{
		/*End Communication with RTC*/
		TWI_void_sendStop();
	}
	else
	{
		return ERROR ;
	}
	
	return SUCCESS;	
}

RTC_OP_Status RTC_void_getTime(RTC_Time* RTC_Time_obj)
{
	u8 status;
	
	
	TWI_void_sendStart();
	
	TWI_void_getStatus(&status);
	if(status==MT_START_CONDITION_TRANSMITTED)
	{
		/* Start I2C communication with RTC */
		TWI_void_sendByte(RTC_WRITE_FIXED_ADDRESS);
		
	}
	else
	{
		return ERROR ;
	}
	
	
	TWI_void_getStatus(&status);
	if(status==MT_SLA_W_TRANSMITTED_ACK_RECEIVED)
	{
		/* Start from Reading Address */
		TWI_void_sendByte(RTC_SECONDS_ADDRESS);
		
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MT_DATA_TRANSMITTED_ACK_RECEIVED)
	{
		/* Repeated start with device*/
		TWI_void_sendStart();
		
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MR_REPEATED_START_CONDITION_TRANSMITTED)
	{
		/* Send Fixed address with read option not write*/
		TWI_void_sendByte(RTC_READ_FIXED_ADDRESS);
		
	}
	else
	{
		return ERROR ;
	}
	
	
	TWI_void_getStatus(&status);
	if(status==MR_SLA_R_TRANSMITTED_ACK_RECIEVED)
	{
		/* Receive Seconds */
		TWI_void_receiveByte_ACK(&RTC_Time_obj->Second);
		
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MR_DATA_RECEIVED_ACK_RETURNED)
	{
		/* Receive Minutes */
		TWI_void_receiveByte_ACK(&RTC_Time_obj->Minute);
		
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MR_DATA_RECEIVED_ACK_RETURNED)
	{
		/* Receive Hours */
		TWI_void_receiveByte_NoACK(&RTC_Time_obj->Hour);
		
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MR_DATA_RECEIVED_NOACK_RECIVED)
	{
		/* End Communication */
		TWI_void_sendStop();
		
	}
	else
	{
		return ERROR ;
	}
	
	return SUCCESS;
}





RTC_OP_Status RTC_void_setDate(const RTC_Date* RTC_Date_obj)
{
	u8 status;
	
	TWI_void_sendStart();
	
	TWI_void_getStatus(&status);
	if(status==MT_START_CONDITION_TRANSMITTED)
	{
		/* Start I2C communication with RTC */
		TWI_void_sendByte(RTC_WRITE_FIXED_ADDRESS);
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MT_SLA_W_TRANSMITTED_ACK_RECEIVED)
	{
		/* Send Address to start write on it */
		TWI_void_sendByte(RTC_DAY_ADDRESS);
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MT_DATA_TRANSMITTED_ACK_RECEIVED)
	{
		/* Send day value */
		TWI_void_sendByte(RTC_Date_obj->day);
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MT_DATA_TRANSMITTED_ACK_RECEIVED)
	{
		/* Send date value */
		TWI_void_sendByte(RTC_Date_obj->date);
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MT_DATA_TRANSMITTED_ACK_RECEIVED)
	{
		/* Send month value */
		TWI_void_sendByte(RTC_Date_obj->month);
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MT_DATA_TRANSMITTED_ACK_RECEIVED)
	{
		/* Send year value */
		TWI_void_sendByte(RTC_Date_obj->year);
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MT_DATA_TRANSMITTED_ACK_RECEIVED)
	{
		/* End Communication */
		TWI_void_sendStop();
	}
	else
	{
		return ERROR ;
	}
	
	return SUCCESS;
}





RTC_OP_Status RTC_void_getDate( RTC_Date* RTC_Date_obj )
{
	u8 status;
	
	
	TWI_void_sendStart();
	
	TWI_void_getStatus(&status);
	if(status==MT_START_CONDITION_TRANSMITTED)
	{
		/* Start I2C communication with RTC */
		TWI_void_sendByte(RTC_WRITE_FIXED_ADDRESS);
		
	}
	else
	{
		return ERROR ;
	}
	
	
	TWI_void_getStatus(&status);
	if(status==MT_SLA_W_TRANSMITTED_ACK_RECEIVED)
	{
		/* Start from Reading Address */
		TWI_void_sendByte(RTC_DAY_ADDRESS);
		
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MT_DATA_TRANSMITTED_ACK_RECEIVED)
	{
		/* Repeated start with device*/
		TWI_void_sendStart();
		
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MR_REPEATED_START_CONDITION_TRANSMITTED)
	{
		/* Send Fixed address with read option not write*/
		TWI_void_sendByte(RTC_READ_FIXED_ADDRESS);
		
	}
	else
	{
		return ERROR ;
	}
	
	
	TWI_void_getStatus(&status);
	if(status==MR_SLA_R_TRANSMITTED_ACK_RECIEVED)
	{
		/* Receive Seconds */
		TWI_void_receiveByte_ACK(&RTC_Date_obj->day);
		
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MR_DATA_RECEIVED_ACK_RETURNED)
	{
		/* Receive Minutes */
		TWI_void_receiveByte_ACK(&RTC_Date_obj->date);
		
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MR_DATA_RECEIVED_ACK_RETURNED)
	{
		/* Receive Minutes */
		TWI_void_receiveByte_ACK(&RTC_Date_obj->month);
		
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MR_DATA_RECEIVED_ACK_RETURNED)
	{
		/* Receive Hours */
		TWI_void_receiveByte_NoACK(&RTC_Date_obj->year);
		
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MR_DATA_RECEIVED_NOACK_RECIVED)
	{
		/* End Communication */
		TWI_void_sendStop();
		
	}
	else
	{
		return ERROR ;
	}
	
	return SUCCESS;
}