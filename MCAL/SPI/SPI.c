#include "StdTypes.h"
#include "Utils.h"
#include "MCU_HW.h"


#include "SPI.h"

#include <util/delay.h>

static void (*SPI_Fptr)(void)=NULLPTR;


void SPI_void_Init(SPI_CNFG * CFG)
{
	u8 copy_reg=0;
	
	//Choosing Mode Master or Slave
	if (CFG->Mode==MASTER)
	{
		SET_BIT(copy_reg,MSTR);
	}
	else if (CFG->Mode==SLAVE)
	{
		CLR_BIT(copy_reg,MSTR);
	}
	
	//Choosing Data Order LSB or MSB
	if (CFG->Data_Order==MSB)
	{
		CLR_BIT(copy_reg,DORD);
	}
	else if (CFG->Data_Order==LSB)
	{
		SET_BIT(copy_reg,DORD);
	}
	
	
	//Choosing Clock IDLE Polarity Rising or Failing
	if (CFG->Clock_Polarity==RISING_EDGE_IDLE)
	{
		CLR_BIT(copy_reg,CPOL);
	}
	else if (CFG->Clock_Polarity==FAILING_EDGE_IDLE)
	{
		SET_BIT(copy_reg,CPOL);
	}
	
	//Choosing Clock Phase SAMPLE OR SETUP first
	if (CFG->Clock_Phase==SAMPLE)
	{
		CLR_BIT(copy_reg,CPHA);
	}
	else if (CFG->Clock_Phase==SETUP)
	{
		SET_BIT(copy_reg,CPHA);
	}
	
	
	//Choosing Speed Mode Normal or Double
	if(CFG->Speed_Type==NORMAL)
	{
		CLR_BIT(SPCR,SPI2X);
	}
	else if(CFG->Speed_Type==DOUBLE)
	{
		SET_BIT(SPCR,SPI2X);
	}
	
	//Assigning Pre_Scaler Choice 
	CFG->Pre_Scaler=CFG->Pre_Scaler&(0b00000111);
	copy_reg=copy_reg|CFG->Pre_Scaler;
	
	//Enable SPE
	SET_BIT(copy_reg,SPE);
	
	//Copying the local shift register (helper) to the Main register SPCR to Init SPI
	SPCR = copy_reg;
	
	
}



void SPI_void_SendReceive( u8 data_sent , u8* data_recieved )
{
	SPDR=data_sent;
	while(!READ_BIT(SPSR,SPIF));
	*data_recieved = SPDR;
}


void SPI_void_SendNoBlock(u8 data)
{
	SPDR=data;
}

u8 SPI_u8_Receive_NoBlock(void)
{
	return SPDR;
}

SPIdata_Status_type SPI_ReceivePerodic(u8*pdata)
{
	if (READ_BIT(SPSR,SPIF))
	{
		*pdata=SPDR;
		return OKAY;
	}
	return NOT_OKAY;
}


void SPI_void_Interrupt_Enable(void)
{
	SET_BIT(SPCR,SPIE);
}

void SPI_void_SetCallBack(void(*LocalPtr)(void))
{
	SPI_Fptr=LocalPtr;
}


SPIdata_Status_type SPI_SendReceive_withTimeout(u8 data_send,u8 *data_receive)
{
	SPIdata_Status_type status;
	u8 i=0;
	
	SPDR=data_send;
	
	
	while(!READ_BIT(SPSR,SPIF)&&i<TIMEOUT_VALUE)
	{
		_delay_us(1);
		i++;
	}
	
	if(i==TIMEOUT_VALUE)
	{
		status=NOT_OKAY;
	}
	else
	{
		*data_receive=SPDR;
		status=OKAY;
	}
	
	return status;
}


ISR(SPI_STC_vect)
{
	if(SPI_Fptr!=NULLPTR)
	{
		SPI_Fptr();
	}
}