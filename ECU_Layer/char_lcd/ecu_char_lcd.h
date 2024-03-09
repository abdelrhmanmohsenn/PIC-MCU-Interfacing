/* 
 * File:   ecu_char_lcd.h
 * Author: mohsen
 *
 * Created on February 6, 2023, 5:20 PM
 */

#ifndef ECU_CHAR_LCD_H
#define	ECU_CHAR_LCD_H

/******* section : Includes *******/
#include "ecu_char_lcd_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/******* section : macros Declarations *******/
#define LCD_CLEAR                                        0x01
#define LCD_CURSOR_HOME                                  0x02
#define LCD_DECREMENT_WITHOUT_SHIFT                      0x04
#define LCD_DECREMENT_WITH_SHIFT                         0x05
#define LCD_INCREMENT_WITHOUT_SHIFT                      0x06
#define LCD_INCREMENT_WITH_SHIFT                         0x07
#define LCD_DISPLAY_OFF_UNDERLINE_OFF_CURSOR_OFF         0x08
#define LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF          0x0C
#define LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON           0x0D
#define LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF           0x0E
#define LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON            0x0F
#define LCD_DISPLAY_SHIFT_RIGHT                          0x1C
#define LCD_DISPLAY_SHIFT_LEFT                           0x18
#define LCD_8BIT_2LINES_MODE                             0x38
#define LCD_4BIT_2LINES_MODE                             0x28
#define LCD_CGRAM_START                                  0x40
#define LCD_DDRAM_START                                  0x80

#define ROW1    1
#define ROW2    2
#define ROW3    3
#define ROW4    4

/******* section : function-like macros Declarations *******/

/******* section : Data Types Declarations *******/
typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
}char_lcd_4bit_t;

typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
}char_lcd_8bit_t;
/******* section : Function Declarations *******/
Std_ReturnType lcd_4bit_initialize(char_lcd_4bit_t *lcd);
Std_ReturnType lcd_4bit_send_command(char_lcd_4bit_t *lcd, uint8 command);
Std_ReturnType lcd_4bit_send_char(char_lcd_4bit_t *lcd, uint8 data);
Std_ReturnType lcd_4bit_send_char_pos(char_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data);
Std_ReturnType lcd_4bit_send_string(char_lcd_4bit_t *lcd, uint8 *str);
Std_ReturnType lcd_4bit_send_string_pos(char_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str);
Std_ReturnType lcd_4bit_send_custom_char(char_lcd_4bit_t *lcd, uint8 row, uint8 column,
                                         uint8 chr[], uint8 mem_pos);

Std_ReturnType lcd_8bit_initialize(char_lcd_8bit_t *lcd);
Std_ReturnType lcd_8bit_send_command(char_lcd_8bit_t *lcd, uint8 command);
Std_ReturnType lcd_8bit_send_char(char_lcd_8bit_t *lcd, uint8 data);
Std_ReturnType lcd_8bit_send_char_pos(char_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data);
Std_ReturnType lcd_8bit_send_string(char_lcd_8bit_t *lcd, uint8 *str);
Std_ReturnType lcd_8bit_send_string_pos(char_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str);
Std_ReturnType lcd_8bit_send_custom_char(char_lcd_8bit_t *lcd, uint8 row, uint8 column,
                                         uint8 chr[], uint8 mem_pos);

Std_ReturnType convert_byte_to_string(uint8 value , uint8 *str);
Std_ReturnType convert_short_to_string(uint16 value , uint8 *str);
Std_ReturnType convert_int_to_string(uint32 value , uint8 *str);

#endif	/* ECU_CHAR_LCD_H */

