#ifndef SPI_H_
#define SPI_H_

#define TIMEOUT_VALUE 10

typedef enum
{
	SLAVE=0,
	MASTER
}SPI_Mode_type;

typedef enum
{
	MSB=0,
	LSB=1
	
}Data_Order_type;

typedef enum
{
	RISING_EDGE_IDLE=0,
	FAILING_EDGE_IDLE=1
	
}SPI_Clock_Polarity;

typedef enum
{
	SAMPLE=0,
	SETUP=1
	
}SPI_Clock_Phase;

typedef enum
{
	NORMAL=0,
	DOUBLE
	
}SPI_SPEED_TYPE;
typedef enum
{
	FCPU_OV_FOUR=0,
	FCPU_OV_SIXTEEN=1,
	FCPU_OV_SIXTYFOUR=2,
	FCPU_OV_ONEHUND_TWENTYEIGHT=3,
	FCPU_OV_TWO_DOUBLESPEED=0,
	FCPU_OV_EIGHT_DOUBLESPEED=1,
	FCPU_OV_THIRTYTWO_DOUBLESPEED=2,
	FCPU_OV_SIXTYFOUR_DOUBLESPEED=3
}SPI_Pre_Scaler;

typedef struct  
{
	SPI_Mode_type      Mode;
	Data_Order_type    Data_Order;
	SPI_Clock_Polarity Clock_Polarity;
	SPI_Clock_Phase    Clock_Phase;
	SPI_SPEED_TYPE     Speed_Type;
	SPI_Pre_Scaler     Pre_Scaler;
	
	
}SPI_CNFG;

typedef enum
{
	NOT_OKAY=0,
	OKAY=1

}SPIdata_Status_type;



void SPI_void_Init(SPI_CNFG * CFG);
void SPI_void_SendReceive( u8 data_sent , u8* data_recieved );

void SPI_void_SendNoBlock(u8 data);
u8 SPI_u8_Receive_NoBlock(void);

SPIdata_Status_type SPI_ReceivePerodic(u8*pdata);
SPIdata_Status_type SPI_SendReceive_withTimeout(u8 data_send,u8 *data_receive);

void SPI_void_Interrupt_Enable(void);
void SPI_void_SetCallBack(void(*LocalPtr)(void));


#endif