#include "StdTypes.h"
#include "Utils.h"
#include "MCU_HW.h"

#include "I2C_Interface.h"

#include "I2C_Private.h"


void TWI_void_Init(TWI_Prescaler Prescaler)
{
	switch(Prescaler)
	{
		case ONE_HUNDRED_KHZ:
		   
		   TWBR=TWBR_VALUE_FOR_ONEHUND_KHZ;
		   
		break;
		
		case FOUR_HUNDRED_KHZ:
		
		TWBR=TWBR_VALUE_FOR_FOURHUND_KHZ;
		
		break;
	}
	
	//Enable TWI.
	
	SET_BIT(TWCR,TWEN);
}


void TWI_void_sendByte(u8 copy_u8data)
{
	//Sending Data to Data Register.
	TWDR = copy_u8data;
	
	//Clearing Flag and Enable TWI.
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	//Waiting Till Flag Raised as Data is sent.
	while (!(TWCR & (1<<TWINT)));
}


void TWI_void_sendStart(void)
{
	//Sending Start Condition to the Bus.
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	
	//Ensuring that the Start Condition has been sent.
	while (!(TWCR & (1<<TWINT)));
}


void TWI_void_sendStop(void)
{
	//Sends Stop Condition to the Bus.
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}


void TWI_void_receiveByte_ACK( u8 *Recieved_Data_ptr )
{
	//Enabling Receiving with ACK.
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	
	//Wait Till Flag is Raised.
	while (!(TWCR & (1<<TWINT)));
	
	//Receiving the Data.
	*Recieved_Data_ptr=TWDR;
	
}


void TWI_void_receiveByte_NoACK( u8 *Recieved_Data_ptr )
{
	//Enabling Receiving with no ACK.
	TWCR = (1<<TWINT)|(1<<TWEN);
	
	//Wait Till Flag is Raised.
	while (!(TWCR & (1<<TWINT)));
	
	//Receiving the Data.
	*Recieved_Data_ptr=TWDR;
}


void TWI_void_getStatus( u8* Recieved_Status_ptr )
{
	// Return Status Value from Status bits.
	
	*Recieved_Status_ptr=TWSR&TWSR_MASKING_VALUE;
	
}