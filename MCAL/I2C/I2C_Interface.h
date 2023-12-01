#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_


#define MT_START_CONDITION_TRANSMITTED                0x08
#define MT_REPEATED_START_CONDITION_TRANSMITTED       0x10
#define MT_SLA_W_TRANSMITTED_ACK_RECEIVED             0x18 
#define MT_SLA_W_TRANSMITTED_ACK_NOTRECEIVED          0x20 
#define MT_DATA_TRANSMITTED_ACK_RECEIVED              0x28
#define MT_DATA_TRANSMITTED_ACK_NOTRECEIVED           0x30
#define MT_ARBIRTRATION_LOST_IN_SLA_W_OR_DATA_BYTES   0x38

#define MR_START_CONDITION_TRANSMITTED                0x08
#define MR_REPEATED_START_CONDITION_TRANSMITTED       0x10
#define MR_ARBIRTRATION_LOST_IN_SLA_R_OR_NOACK        0x38
#define MR_SLA_R_TRANSMITTED_ACK_RECIEVED             0x40
#define MR_SLA_R_TRANSMITTED_ACK_NOTRECIEVED          0x48
#define MR_DATA_RECEIVED_ACK_RETURNED                 0x50
#define MR_DATA_RECEIVED_NOACK_RECIVED                0x58



typedef enum
{
	ONE_HUNDRED_KHZ,
	FOUR_HUNDRED_KHZ
	
}TWI_Prescaler;



void TWI_void_Init(TWI_Prescaler Prescaler);
void TWI_void_sendByte(u8 copy_u8data);
void TWI_void_sendStart(void);
void TWI_void_sendStop(void);
void TWI_void_receiveByte_ACK( u8*Recieved_Data_ptr );
void TWI_void_receiveByte_NoACK( u8*Recieved_Data_ptr );
void TWI_void_getStatus( u8* Recieved_Status_ptr );




#endif 