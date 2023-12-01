#include "StdTypes.h"
#include "Utils.h"

#include <util/delay.h>


#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "LCD_Cfg.h"
#include "LCD_Private.h"

#define FIRST_ROW 0
#define SECOND_ROW 1

#if LCD_MODE==_8_BIT
static void H_LCD_void_SendCommand(u8 ins)
{
	
	DIO_voidWritePin(RS,LOW);
	DIO_voidWritePort(LCD_PORT,ins);
	DIO_voidWritePin(EN,HIGH);
	_delay_ms(1);
	DIO_voidWritePin(EN,LOW);
	_delay_ms(1);
	
}

static void H_LCD_void_SendData(u8 data)
{
	DIO_voidWritePin(RS,HIGH);
	DIO_voidWritePort(LCD_PORT,data);
	DIO_voidWritePin(EN,HIGH);
	_delay_ms(1);
	DIO_voidWritePin(EN,LOW);
	_delay_ms(1);
}



void H_LCD_void_Init(void)
{
	_delay_ms(50);
	
	H_LCD_void_SendCommand(LINES_FONT_INS);//5*7 2 lines
	H_LCD_void_SendCommand(CURSOR_TYPE_INS);//0x0c,0x0e,0x0f cursor
	H_LCD_void_SendCommand(CLEAR_SCREEN_INS);//clear screen
	_delay_ms(1);
	H_LCD_void_SendCommand(INCREMENT_DDRAM_INS_FROMLEFT);// increment DDRAM address, no shift
	
}

#elif LCD_MODE ==_4_BIT
 void H_LCD_void_SendCommand(u8 ins)
{
	
	
	DIO_voidWritePin(RS,LOW);
	DIO_voidWritePin(D7,READ_BIT(ins,7));
	DIO_voidWritePin(D6,READ_BIT(ins,6));
	DIO_voidWritePin(D5,READ_BIT(ins,5));
	DIO_voidWritePin(D4,READ_BIT(ins,4));
	
	DIO_voidWritePin(EN,HIGH);
	_delay_ms(1);
	DIO_voidWritePin(EN,LOW);
	_delay_ms(1);
	DIO_voidWritePin(D7,READ_BIT(ins,3));
	DIO_voidWritePin(D6,READ_BIT(ins,2));
	DIO_voidWritePin(D5,READ_BIT(ins,1));
	DIO_voidWritePin(D4,READ_BIT(ins,0));
	DIO_voidWritePin(EN,HIGH);
	_delay_ms(1);
	DIO_voidWritePin(EN,LOW);
	_delay_ms(1);
}

 void H_LCD_void_SendData(u8 data)
{
	DIO_voidWritePin(RS,HIGH);
	DIO_voidWritePin(D7,READ_BIT(data,7));
	DIO_voidWritePin(D6,READ_BIT(data,6));
	DIO_voidWritePin(D5,READ_BIT(data,5));
	DIO_voidWritePin(D4,READ_BIT(data,4));

	DIO_voidWritePin(EN,HIGH);
	_delay_ms(1);
	DIO_voidWritePin(EN,LOW);
	_delay_ms(1);
	DIO_voidWritePin(D7,READ_BIT(data,3));
	DIO_voidWritePin(D6,READ_BIT(data,2));
	DIO_voidWritePin(D5,READ_BIT(data,1));
	DIO_voidWritePin(D4,READ_BIT(data,0));
	DIO_voidWritePin(EN,HIGH);
	_delay_ms(1);
	DIO_voidWritePin(EN,LOW);
	_delay_ms(1);
}



void H_LCD_void_Init(void)
{
	_delay_ms(50);
	H_LCD_void_SendCommand(RETURN_HOME);
	H_LCD_void_SendCommand(LINES_FONT_INS);//5*7 2 lines
	H_LCD_void_SendCommand(CURSOR_TYPE_INS);//0x0c,0x0e,0x0f cursor
	H_LCD_void_SendCommand(CLEAR_SCREEN_INS);//clear screen
	_delay_ms(1);
	H_LCD_void_SendCommand(INCREMENT_DDRAM_INS_FROMLEFT);// increment DDRAM address, no shift
	
}

#endif

void H_LCD_void_SendChar(u8 ch)
{
	H_LCD_void_SendData(ch);
}


void H_LCD_void_SendString(u8*str)
{
	u8 i;
	for (i=0;str[i];i++)
	{
		H_LCD_void_SendChar(str[i]);
	}
	
}


void H_LCD_void_SetCursor(u8 line,u8 cell)
{
	if (line==FIRST_ROW)
	{
		H_LCD_void_SendCommand(DDRAM_FIRST_ROW|cell);
	}
	else if (line ==SECOND_ROW)
	{
		H_LCD_void_SendCommand(DDRAM_SECOND_ROW+cell);
	}
	else if (line ==THIRD_ROW)
	{
		H_LCD_void_SendCommand(DDRAM_THIRD_ROW+cell);
	}
	else if (line ==FOURTH_ROW)
	{
		H_LCD_void_SendCommand(DDRAM_FOURTH_ROW+cell);
	}
	
}

void H_LCD_void_Clear_Display(void)
{
	H_LCD_void_SendCommand(CLEAR_SCREEN_INS);
	_delay_ms(1);
}


void H_LCD_void_SendIntNumber(s32 num)
{
u8 str[32]={0};

int_to_string(num,str);

H_LCD_void_SendString(str);
	
}
void H_LCD_void_SendBinary(u8 num)
{
	u8 str[9]={0};
	int_to_Binary (num, str);
	H_LCD_void_SendString(str);
		
}
void H_LCD_void_SendHex(u8 num)
{
	u8 str[3]={0};
	 int_to_Hex_to_string (num,str);
	H_LCD_void_SendString(str);
	
}
 
void H_LCD_void_CustomChar(u8 location,const u8*pattern)
{

	H_LCD_void_SendCommand(CGRAM_STARTING_LOC+(location*CUSTOM_ARRAY_SIZE));  // to ensure storing in CGRAM
	u8 i;
	
	for(i=0;i<CUSTOM_ARRAY_SIZE;i++)
	{
		H_LCD_void_SendData(pattern[i]);
	}
	
	H_LCD_void_SendCommand(DDRAM_STARTING_LOC);    // to ensure dealing with DDRAM Again after creating the Custom Character.
	 
}
 
 static void int_to_Binary (u8 n, u8 *str)
 {
	 s8 i,j;
	 for(i=7,j=0;i>=0;i--,j++)
	 {
		 str[j]=READ_BIT(n,i)+'0';
	 }
 }
 
 static void int_to_Hex_to_string (u8 n, u8 *str)
 {
	 u8 s1,s2;
	 s1=n&(0x0f);
	 s2=n>>4;
	  
	  if(s1<=9)
	  {
		  str[1]=s1+'0';
	  }
	  else if(s1>9)
	  {
		  str[1]=(s1-10)+'A';
	  }
	  if(s2<=9)
	  {
		  str[0]=s2+'0';
	  }
	  else if (s2>9)
	  {
		  str[0]=(s2-10)+'A';
	  }
 }

 static void int_to_string (s32 n, u8 *str)
{
	u8 i=0,flag=0;
	
	s32 rem;

	if(n==0)
	{
		str[0]='0';
		str[1]=0;
		return;
	}
	if(n<0)
	{
		n=n*(-1);
		flag=1;
	}

	while(n)
	{
		rem=n%10;
		rem=rem+'0';
		str[i]=rem;
		i++;
		n=n/10;
	}

	if (flag==1)
	{
		str[i]='-';
		i++;
	}
	str[i]=0;
	string_reverse(str);

}

 static void string_reverse(u8*str)
{
	s32 j,i,len=string_len(str);
	j=len-1;
	u8 temp;
	for(i=0;i<=j;i++,j--)
	{
		temp=str[i];
		str[i]=str[j];
		str[j]=temp;
	}

}

 static u32 string_len(u8*str)
{
	u32 i;
	for(i=0;str[i];i++);
	return i;

}
