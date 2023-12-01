#ifndef SEVENSEGMENT_INTERFACE_H_
#define SEVENSEGMENT_INTERFACE_H_

#define SEGMENT1_PORT  PB
#define SEGMENT2_PORT  PB
#define SEGMENT3_PORT  PB
#define SEGMENT4_PORT  PB


#define SEGMENT1_POWER_PORT PC
#define SEGMENT2_POWER_PORT PC
#define SEGMENT3_POWER_PORT PC
#define SEGMENT4_POWER_PORT PC

#define SEGMENT1_POWER_PIN PINA3
#define SEGMENT2_POWER_PIN PINA2
#define SEGMENT3_POWER_PIN PINB5			
#define SEGMENT4_POWER_PIN PINB6

typedef enum
{
	L1,
	L2,
	L3,
	L4,
	TOTAL_SEGMENTS_NUMBER
}Segment_Type;



void SeventSegment_Init(void);
void SeventSegment_void_BCD_Display(Segment_Type segment,u8 n);
void SeventSegment_void_NoBCD_Display(Segment_Type segment,u8 n);
void SeventSegment_Display_MULX(Segment_Type segment_1,Segment_Type segment_2,u8 n);


#endif