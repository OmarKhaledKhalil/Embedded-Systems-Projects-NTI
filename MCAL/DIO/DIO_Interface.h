
#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#define BYTE_SIZE 8
#define TWO_BYTE_SIZE 16
#define THREE_BYTE_SIZE 24

typedef enum{
	PA=0,
	PB,
	PC,
	PD	
	}DIO_Port_type;

typedef enum{
	OUTPUT,
	INFREE,
	INPULL
	}DIO_PinStatus_type;

typedef enum{
	LOW=0,
	HIGH=1,
	}DIO_PinVoltage_type;

typedef enum{
	PINA0=0,
	PINA1=1,
	PINA2,
	PINA3,
	PINA4,
	PINA5,
	PINA6,
	PINA7,
	PINB0,
	PINB1,
	PINB2,
	PINB3,
	PINB4,
	PINB5,
	PINB6,
	PINB7,
	PINC0,
	PINC1,
	PINC2,
	PINC3,
	PINC4,
	PINC5,
	PINC6,
	PINC7,
	PIND0,
	PIND1,
	PIND2,
	PIND3,
	PIND4,
	PIND5,
	PIND6,
	PIND7,
	TOTAL_PINS
}DIO_Pin_type;


void DIO_voidInit(void);

void DIO_voidWritePin(DIO_Pin_type pin,DIO_PinVoltage_type volt);

DIO_PinVoltage_type DIO_ReadPin(DIO_Pin_type pin);

void DIO_voidTogglePin(DIO_Pin_type pin);

void DIO_voidWritePort(DIO_Port_type port,u8 value);

 u8 DIO_u8ReadPort(DIO_Port_type port);


#endif /* DIO_INTERFACE_H_ */