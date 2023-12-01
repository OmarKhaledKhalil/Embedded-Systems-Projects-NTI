#ifndef EXTERNAL EEPROM_INTERFACE_H_
#define EXTERNAL EEPROM_INTERFACE_H_

#define External_EEPROM_FIXED_ADDRESS  0b10100000

typedef enum 
{
	ERROR=0,
	
	SUCCESS
	
}External_EEPROM_OP_Status;

void External_EEPROM_void_Init( void );
External_EEPROM_OP_Status External_EEPROM_void_WriteByte( u16 location , u8 data );
External_EEPROM_OP_Status External_EEPROM_void_ReadByte(  u16 location , u8*data );


#endif 