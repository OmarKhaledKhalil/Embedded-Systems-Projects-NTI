/*
#include "StdTypes.h"
#include "Utils.h"
#include "USART_Interface.h"

#include "FingerPrint_Interface.h"

void FingerPS_LoadCharFile()
{
		
			u8 store[13]={0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x04, 0x02, 0x01, 0x00, 0x08};
			
			for (u8 i = 0; i < 13; i++)
			{
				USART_void_SendBlock( store[i] ); // Send byte by byte with BLock
			}
			
			UART_receiveByteAsynchCallBack(receiveCallback);
			//_delay_ms(5);
			while(byte_no != 12);
			
			// Check Sum()
			//Check ACK ()
			//clearBuffer()
	
		

	

}


u16 FingerPS_calcCheckSum(char*arr , u8 length)
{
	u16 sum = 0 ;
	
	for(int i = 6 ; i<length-2 ; i++)
	{
		sum = sum + arr[i];
	}
	return sum ;
}


void FingerPS_match()
{
	u8 store[12]={0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x03, 0x00, 0x07};
	
	for (u8 i = 0; i < 12; i++)
	{
		USART_void_SendBlock( store[i] ); // Send byte by byte with BLock
	}
	
	UART_receiveByteAsynchCallBack(receiveCallback);
	//_delay_ms(5);
	while(byte_no != 14);
	
	// Check Sum()
	//Check ACK ()
	//clearBuffer()
}
*/