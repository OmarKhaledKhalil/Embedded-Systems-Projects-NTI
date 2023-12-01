#include "StdTypes.h"
#include "Utils.h"
#include "I2C_Interface.h"

#include "External EEPROM_Interface.h"


void External_EEPROM_void_Init(void)
{
	TWI_void_Init(ONE_HUNDRED_KHZ);
}

External_EEPROM_OP_Status External_EEPROM_void_WriteByte( u16 location , u8 data )
{
	u8 status;
	u8*p=&location;
	p++;
	
	
	
	TWI_void_sendStart();
	
	TWI_void_getStatus(&status);
	if(status==MT_START_CONDITION_TRANSMITTED)
	{
		TWI_void_sendByte(External_EEPROM_FIXED_ADDRESS|(*p<<1));
	}
	else
	{
		return ERROR ;
	}
	p--;
	
	TWI_void_getStatus(&status);
	if(status==MT_SLA_W_TRANSMITTED_ACK_RECEIVED)
	{
		TWI_void_sendByte(*p);
	}
	else
	{
		return ERROR ;
	}
	
	
	TWI_void_getStatus(&status);
	if(status==MT_DATA_TRANSMITTED_ACK_RECEIVED)
	{
		TWI_void_sendByte(data);
	}
	else
	{
		return ERROR ;
	}
	
	
	TWI_void_getStatus(&status);
	if(status==MT_DATA_TRANSMITTED_ACK_RECEIVED)
	{
		TWI_void_sendStop();
	}
	else
	{
		return ERROR ;
	}
	
	return SUCCESS;
}


External_EEPROM_OP_Status External_EEPROM_void_ReadByte( u16 location , u8*data )
{
	u8 status;
	u8*p=&location;
	p++;
	
	TWI_void_sendStart();
	
	TWI_void_getStatus(&status);
	if(status==MT_START_CONDITION_TRANSMITTED)
	{
		TWI_void_sendByte(External_EEPROM_FIXED_ADDRESS|*p);
	}
	else
	{
			return ERROR ;
	}
	
	p--;
	
	TWI_void_getStatus(&status);
	if(status==MT_SLA_W_TRANSMITTED_ACK_RECEIVED)
	{
		TWI_void_sendByte(*p);
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);
	if(status==MT_DATA_TRANSMITTED_ACK_RECEIVED)
	{
			TWI_void_sendStart();
	}
	else
	{
		return ERROR ;
	}
		
	TWI_void_getStatus(&status);	
	if(status==MT_START_CONDITION_TRANSMITTED)
	{
		TWI_void_receiveByte_ACK(data);
	}
	else
	{
		return ERROR ;
	}
	
	TWI_void_getStatus(&status);	
	if(status==MR_DATA_RECEIVED_ACK_RETURNED)	
	{
			TWI_void_sendStop();
	}
	else
	{
		return ERROR ;
	}
	
	return SUCCESS;
	
}