

#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_


#define CLEAR_SCREEN_INS             0x01
#define CURSOR_TYPE_INS              0x0C
#define INCREMENT_DDRAM_INS_FROMLEFT 0x06
#define LINES_FONT_INS               0x28
#define RETURN_HOME                  0x02


#define DDRAM_FIRST_ROW        0x80
#define DDRAM_SECOND_ROW       0xC0
#define DDRAM_THIRD_ROW        0x94
#define DDRAM_FOURTH_ROW       0xD4

#define CGRAM_STARTING_LOC   0x40
#define DDRAM_STARTING_LOC   0x80

#define FIRST_ROW           0
#define SECOND_ROW          1
#define THIRD_ROW           2
#define FOURTH_ROW          3


#define CUSTOM_ARRAY_SIZE   8

//LacthByte Function 
static void H_LCD_void_latchByte(u8 copy_u8Byte);


//Helper Functions
static u32 string_len(u8*str);
static void int_to_string (s32 n, u8 *str);
static  void string_reverse(u8*str);
static void int_to_Binary (u8 n, u8 *str);
static void int_to_Hex_to_string (u8 n, u8 *str);






#endif 