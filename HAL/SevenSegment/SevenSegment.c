#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "SevenSegment_Interface.h"

#include <util/delay.h>



void SeventSegment_Init(void)
{
	
}

void SeventSegment_void_BCD_Display(Segment_Type segment,u8 n)
{

u8 segmentARR[]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x10,0x11};
switch(segment)
{
	case L1:
	DIO_voidWritePin(SEGMENT1_POWER_PIN,LOW);
	DIO_voidWritePort(SEGMENT1_PORT,segmentARR[n]);
	
	break;
	case L2:
	DIO_voidWritePin(SEGMENT2_POWER_PIN,LOW);
	DIO_voidWritePort(SEGMENT2_PORT,segmentARR[n]);
	
	break;
	
	case L3:
	DIO_voidWritePin(SEGMENT3_POWER_PIN,LOW);
	DIO_voidWritePort(SEGMENT3_PORT,segmentARR[n]);
	
	break;
	
	case L4:
	DIO_voidWritePin(SEGMENT4_POWER_PIN,LOW);
	DIO_voidWritePort(SEGMENT4_PORT,segmentARR[n]);
	
	break;
	case TOTAL_SEGMENTS_NUMBER:
	break;
}
}


/*
void SeventSegment_void_NODecoder_Display(Segment_Type segment,u8 n)
{
	u8 segmentARR[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};
		// local array responsible for control LEDS to represent a certain number.
	
	switch(segment)
	{
		case L1:
		DIO_voidWritePin(SEGMENT1_POWER_PIN,LOW);
		SEGMENT1_PORT=segmentARR[n]<<1;
		
		break;
		case L2:
		DIO_voidWritePin(SEGMENT2_POWER_PIN,LOW);
		SEGMENT2_PORT=segmentARR[n]<<1;
		
		break;
		
		case L3:
		DIO_voidWritePin(SEGMENT3_POWER_PIN,LOW);
		SEGMENT2_PORT=segmentARR[n]<<1;
		
		break;
		
		case L4:
		DIO_voidWritePin(SEGMENT4_POWER_PIN,LOW);
		SEGMENT2_PORT=segmentARR[n]<<1;
		
		break;
		case TOTAL_SEGMENTS_NUMBER:
		break;
	}
}
*/

void SeventSegment_OFF(Segment_Type segment)
{
	switch(segment)
	{
		case L1:
		DIO_voidWritePin(SEGMENT1_POWER_PIN,HIGH);
	
		
		break;
		case L2:
		DIO_voidWritePin(SEGMENT2_POWER_PIN,HIGH);
		
		
		break;
		
		case L3:
		DIO_voidWritePin(SEGMENT3_POWER_PIN,HIGH);
		
		
		break;
		
		case L4:
		DIO_voidWritePin(SEGMENT4_POWER_PIN,HIGH);
		
		
		break;
		case TOTAL_SEGMENTS_NUMBER:
		break;
	}
}


/*
void SeventSegment_Display_MULX(Segment_Type segment_1,Segment_Type segment_2,u8 n)
{
		u8 d0 = n%10;
		u8 d1 = n/10;
	
	SeventSegment_Display(segment_1,d0);
	SeventSegment_OFF(segment_2);
	_delay_ms(1);
	SeventSegment_Display(segment_2,d1);
	SeventSegment_OFF(segment_1);
	_delay_ms(1);
	
}
*/