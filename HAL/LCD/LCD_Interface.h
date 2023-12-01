 #ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void H_LCD_void_Init(void);
void H_LCD_void_SendCommand(u8 ins);
void H_LCD_void_SendData(u8 data);
void H_LCD_void_SendChar(u8 ch);
void H_LCD_void_SendString(u8*str);
void H_LCD_void_SendIntNumber(s32 num);
void H_LCD_void_SendBinary(u8 num);
void H_LCD_void_SendHex(u8 num);
void H_LCD_void_SetCursor(u8 line,u8 cell);
void H_LCD_void_Clear_Display(void);
void H_LCD_void_CustomChar(u8 location,const u8*pattern);

#endif 