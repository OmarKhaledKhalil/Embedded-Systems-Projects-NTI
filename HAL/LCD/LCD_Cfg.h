#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#define _4_BIT   0
#define _8_BIT   1

/* _4_BIT OR _8_BIT*/
#define  LCD_MODE  _4_BIT



#define  RS   PINA3
#define  EN   PINA2

#define  D7   PINB4
#define  D6   PINB2
#define  D5   PINB1
#define  D4   PINB0

#define  D7_8BIT   PINB7
#define  D6_8BIT   PINB6
#define  D5_8BIT   PINB5
#define  D4_8BIT   PINB4
#define  D3_8BIT   PINB3
#define  D2_8BIT   PINB2
#define  D1_8BIT   PINB1
#define  D0_8BIT   PINB0

#define LCD_PORT  PB



#endif