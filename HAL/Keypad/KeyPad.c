#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "KeyPad_Cfg.h"
#include "KeyPad_Interface.h"


void KEYPAD_voidInit(void)
{
	DIO_voidWritePin(FIRST_OUPUT,HIGH);
	DIO_voidWritePin(FIRST_OUPUT+1,HIGH);
	DIO_voidWritePin(FIRST_OUPUT+2,HIGH);
	DIO_voidWritePin(FIRST_OUPUT+3,HIGH);
}

u8 KEYPAD_u8Getkey (void)
{
	u8 r,c,key=NO_KEY,k;
	
	for(r=0;r<ROWS;r++)
	{
		DIO_voidWritePin(FIRST_OUPUT+r,LOW);
		for(c=0,k=0;c<COLS;c++,k++)
		{
			if(k==1)
			{
				k=2;
			}
			if(DIO_ReadPin(FIRST_INPUT+k)==LOW)
			{
				key=KeysArray[r][c];
				while(DIO_ReadPin(FIRST_INPUT+k)==LOW);
			}	
		}
		DIO_voidWritePin(FIRST_OUPUT+r,HIGH);
	}
	return key;
}
