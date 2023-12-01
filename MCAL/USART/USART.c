#include "StdTypes.h"
#include "Utils.h"
#include "MCU_HW.h"


#include "USART_Interface.h"

static void(*USART_RX_Fptr)(void)=NULLPTR;
static void(*USART_TX_Fptr)(void)=NULLPTR;



void USART_void_Init(void)
{
	/* set baud rate 9600*/
	UBRRL=51;
	/* NORMAL SPEED*/
	CLR_BIT(UCSRA,U2X);
	/*frame  no parity 1 stop bit  8 data*/
	
	/* enable*/
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
}

void USART_void_SendNoBlock(u8 data)
{
	UDR=data;
}

u8 USART_void_ReceiveNoBlock(void)
{
	return UDR;
}


void USART_void_SendBlock(u8 data)
{
	while(!READ_BIT(UCSRA,UDRE));
	UDR=data;
	
}

u8 USART_u8_ReceiveBlock(void)
{
	while(!READ_BIT(UCSRA,RXC));
	return UDR;
}

UART_Recieve_Status USART_ReceivePerodic(u8*pdata)
{
	if (READ_BIT(UCSRA,RXC))
	{
		*pdata=UDR;
		return RECIEVE_DONE;
	}
	return RECIEVE_UNDONE;
}


void USART_void_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
}

void USART_void_RX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,RXCIE);
}

void USART_void_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);
}

void USART_void_TX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,TXCIE);
}

void USART_void_RX_SetCallBack(void (*LocalFptr)(void))
{
	USART_RX_Fptr = LocalFptr;
}

void USART_void_TX_SetCallBack(void (*LocalFptr)(void))
{
	USART_TX_Fptr = LocalFptr;
}

void USART_void_SendStringBlock(u8*str)
{
	u8 i;
	for (i=0;str[i];i++)
	{
		USART_void_SendBlock(str[i]);
	}
	
}


void USART_void_ReceiveStringBlock(u8*str)
{
	u8 i=0;
	str[i]=USART_u8_ReceiveBlock();
	for(;str[i]!=13;)
	{
		i++;
		str[i]=USART_u8_ReceiveBlock();
	}
	str[i]=0;
	
}

void USART_void_SendNumberBlock(u32 num)
{
	USART_void_SendBlock((u8)num);
	USART_void_SendBlock((u8)(num>>8));
	USART_void_SendBlock((u8)(num>>16));
	USART_void_SendBlock((u8)(num>>24));
	/*u8*p=&num;
	UART_Send(p[0]);
	UART_Send(p[1]);
	UART_Send(p[2]);
	UART_Send(p[3]);*/
	
}

u32 USART_u32_RecieveNumberBlock(void)
{
	u32 num;
	
	u8 b0=USART_u8_ReceiveBlock();
	u8 b1=USART_u8_ReceiveBlock();
	u8 b2=USART_u8_ReceiveBlock();
	u8 b3=USART_u8_ReceiveBlock();
	
	num=(u32)b0|((u32)b1<<8)|((u32)b2<<16)|((u32)b3<<24);
	
	u8*p=&num;
	p[0]=USART_u8_ReceiveBlock();
	p[1]=USART_u8_ReceiveBlock();
	p[2]=USART_u8_ReceiveBlock();
	p[3]=USART_u8_ReceiveBlock();
	
	return num;
	
}

void USART_void_SendStringCheckSum(u8*str)
{
	u8 i;
	u16 sum=0;
	u8 len;
	for (i=0;str[i];i++)
	{
		sum=sum+str[i];
	}
	len=i;
	USART_void_SendBlock(len);
	for (i=0;str[i];i++)
	{
		USART_void_SendBlock(str[i]);
	}
	USART_void_SendBlock((u8)sum);
	USART_void_SendBlock((u8)(sum>>8));
}

UART_Recieve_Check USART_ReceiveStringCheckSum(u8*str)
{
	u8 len,i,b1,b0;
	u16 sumCalc=0,sumRec;
	len=USART_u8_ReceiveBlock();
	for (i=0;i<len;i++)
	{
		str[i]=USART_u8_ReceiveBlock();
		sumCalc+=str[i];
	}
	b0=USART_u8_ReceiveBlock();
	b1=USART_u8_ReceiveBlock();
	sumRec=(u16)b0|((u16)b1<<8);
	if (sumRec==sumCalc)
	{
		return DATA_OKAY;
	}
	else
	{
		return DATA_NOT_OKAY;
	}
	
	
}


static void TX_Func(void);

static u8*TXStr;

void USART_void_SendStringNoBlock(u8*str)
{
	USART_void_SendNoBlock(str[0]);
	USART_void_TX_InterruptEnable();
	USART_void_TX_SetCallBack(TX_Func);
	TXStr=str;
	
	
}

static void TX_Func(void)
{
	static  u8 i=1;
	
	if (TXStr[i]!=0)
	{
		USART_void_SendNoBlock(TXStr[i]);
		i++;
	}
	else
	{
		i=1;
		
	}
	
	
}


u8*RXStr;
static void RX_Func(void);
void USART_void_ReceiveStringAsynch(u8*str)
{
	USART_void_RX_InterruptEnable();
	USART_void_RX_SetCallBack(RX_Func);
	RXStr=str;
}


static void RX_Func(void)
{
	static u8 i=0;
	USART_ReceivePerodic(RXStr[i]);
	i++;
}



ISR(UART_RX_vect)
{
	if (USART_RX_Fptr!=NULLPTR)
	{
		USART_RX_Fptr();
	}
}

ISR(UART_TX_vect)
{
	if (USART_TX_Fptr!=NULLPTR)
	{
		USART_TX_Fptr();
	}
}
