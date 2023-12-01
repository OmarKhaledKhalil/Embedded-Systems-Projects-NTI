#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

typedef enum
{
	RECIEVE_UNDONE=0,
	RECIEVE_DONE=1
}UART_Recieve_Status;

typedef enum
{
	DATA_NOT_OKAY=0,
	DATA_OKAY=1
}UART_Recieve_Check;
void USART_void_Init(void);

void USART_void_SendBlock(u8 data);
u8 USART_u8_ReceiveBlock(void);
UART_Recieve_Status USART_ReceivePerodic(u8*pdata);

void USART_void_RX_InterruptEnable(void);
void USART_void_RX_InterruptDisable(void);

void USART_void_TX_InterruptEnable(void);
void USART_void_TX_InterruptDisable(void);

void USART_void_RX_SetCallBack(void (*LocalFptr)(void));
void USART_void_TX_SetCallBack(void (*LocalFptr)(void));

void USART_void_SendNoBlock(u8 data);
UART_Recieve_Status USART_ReceivePerodic(u8*pdata);
u8 USART_void_ReceiveNoBlock(void);


void USART_void_SendStringBlock(u8*str);
void USART_void_ReceiveStringBlock(u8*str);
void USART_void_SendNumberBlock(u32 num);
u32 USART_u32_RecieveNumberBlock(void);
void USART_void_SendStringCheckSum(u8*str);
UART_Recieve_Check USART_ReceiveStringCheckSum(u8*str);
void USART_void_SendStringNoBlock(u8*str);
void USART_void_ReceiveStringAsynch(u8*str);

#endif 