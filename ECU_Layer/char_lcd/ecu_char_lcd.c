/* 
 * File:   ecu_char_lcd.c
 * Author: mohsen
 *
 * Created on February 6, 2023, 5:20 PM
 */

#include "ecu_char_lcd.h"

static Std_ReturnType lcd_4bit_send_data_command(char_lcd_4bit_t *lcd, uint8 _data_command);
static Std_ReturnType lcd_4bit_enable(char_lcd_4bit_t *lcd);
static Std_ReturnType lcd_4bit_set_cursor(char_lcd_4bit_t *lcd, uint8 row, uint8 column);

static Std_ReturnType lcd_8bit_enable(char_lcd_8bit_t *lcd);
static Std_ReturnType lcd_8bit_send_data_command(char_lcd_8bit_t *lcd, uint8 _data_command);
static Std_ReturnType lcd_8bit_set_cursor(char_lcd_8bit_t *lcd, uint8 row, uint8 column);

/**
 * 
 * @param lcd
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType lcd_4bit_initialize(char_lcd_4bit_t *lcd){
    Std_ReturnType ret=E_OK;
    
    if(NULL == lcd){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_initialize(&(lcd->lcd_rs));
        gpio_pin_initialize(&(lcd->lcd_en));
        for(unsigned int i=0 ; i<4 ; i++){
            gpio_pin_initialize(&(lcd->lcd_data[i]));
        }
        __delay_ms(20);
        lcd_4bit_send_command(lcd,LCD_8BIT_2LINES_MODE);
        __delay_ms(5);
        lcd_4bit_send_command(lcd,LCD_8BIT_2LINES_MODE);
        __delay_us(150);
        lcd_4bit_send_command(lcd,LCD_8BIT_2LINES_MODE);
        
        
        lcd_4bit_send_command(lcd,LCD_CLEAR);
        lcd_4bit_send_command(lcd,LCD_CURSOR_HOME);
        lcd_4bit_send_command(lcd,LCD_INCREMENT_WITHOUT_SHIFT);
        lcd_4bit_send_command(lcd,LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        lcd_4bit_send_command(lcd,LCD_4BIT_2LINES_MODE);
        lcd_4bit_send_command(lcd,LCD_DDRAM_START);      
    }
    
    return ret;
}

/**
 * 
 * @param lcd
 * @param command
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType lcd_4bit_send_command(char_lcd_4bit_t *lcd, uint8 command){
    Std_ReturnType ret=E_OK;
    
    if(NULL == lcd){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_write(&(lcd->lcd_rs),PIN_LOW);
        lcd_4bit_send_data_command(lcd,(command>>4));
        lcd_4bit_enable(lcd);
        lcd_4bit_send_data_command(lcd,command);
        lcd_4bit_enable(lcd);
    }
    
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType lcd_4bit_send_char(char_lcd_4bit_t *lcd, uint8 data){
    Std_ReturnType ret=E_OK;
    
    if(NULL == lcd){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_write(&(lcd->lcd_rs),PIN_HIGH);
        lcd_4bit_send_data_command(lcd,(data>>4));
        lcd_4bit_enable(lcd);
        lcd_4bit_send_data_command(lcd,data);
        lcd_4bit_enable(lcd);
    }
    
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType lcd_4bit_send_char_pos(char_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data){
    Std_ReturnType ret=E_OK;
    
    if(NULL == lcd){
        ret=E_NOT_OK;
    }
    else{
        lcd_4bit_set_cursor(lcd,row,column);
        lcd_4bit_send_char(lcd,data);
    }
    
    return ret;
}

/**
 * 
 * @param lcd
 * @param str
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType lcd_4bit_send_string(char_lcd_4bit_t *lcd, uint8 *str){
    Std_ReturnType ret=E_OK;
    
    if(NULL == lcd || NULL == str){
        ret=E_NOT_OK;
    }
    else{
        while(*str){
            lcd_4bit_send_char(lcd,*str++);
        }
    }
    
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType lcd_4bit_send_string_pos(char_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str){
    Std_ReturnType ret=E_OK;
    
    if(NULL == lcd || NULL == str){
        ret=E_NOT_OK;
    }
    else{
        lcd_4bit_set_cursor(lcd,row,column);
        lcd_4bit_send_string(lcd,str);
    }
    
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param chr
 * @param mem_pos
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType lcd_4bit_send_custom_char(char_lcd_4bit_t *lcd, uint8 row, uint8 column,
                                         uint8 chr[], uint8 mem_pos){
    Std_ReturnType ret=E_OK;
    
    if(NULL == lcd){
        ret=E_NOT_OK;
    }
    else{
        lcd_4bit_send_command(lcd,LCD_CGRAM_START +(mem_pos*8));
        for(unsigned int i=0 ; i<8 ; i++){
            lcd_4bit_send_char(lcd,chr[i]);
        }
        lcd_4bit_send_char_pos(lcd,row,column,mem_pos);
    }
    
    return ret;
}

/**
 * 
 * @param lcd
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType lcd_8bit_initialize(char_lcd_8bit_t *lcd){
    Std_ReturnType ret=E_OK;
    
    if(NULL == lcd){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_initialize(&(lcd->lcd_rs));
        gpio_pin_initialize(&(lcd->lcd_en));
        for(unsigned int i=0 ; i<8 ; i++){
            gpio_pin_initialize(&(lcd->lcd_data[i]));
        }
        __delay_ms(20);
        lcd_8bit_send_command(lcd,LCD_8BIT_2LINES_MODE);
        __delay_ms(5);
        lcd_8bit_send_command(lcd,LCD_8BIT_2LINES_MODE);
        __delay_us(150);
        lcd_8bit_send_command(lcd,LCD_8BIT_2LINES_MODE);
        
        lcd_8bit_send_command(lcd,LCD_CLEAR);
        lcd_8bit_send_command(lcd,LCD_8BIT_2LINES_MODE);
        lcd_8bit_send_command(lcd,LCD_CURSOR_HOME);
        lcd_8bit_send_command(lcd,LCD_INCREMENT_WITHOUT_SHIFT);
        lcd_8bit_send_command(lcd,LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        lcd_8bit_send_command(lcd,LCD_DDRAM_START);
    }
    
    return ret;
}

/**
 * 
 * @param lcd
 * @param command
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType lcd_8bit_send_command(char_lcd_8bit_t *lcd, uint8 command){
    Std_ReturnType ret=E_OK;
    
    if(NULL == lcd){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_write(&(lcd->lcd_rs),PIN_LOW);
        lcd_8bit_send_data_command(lcd,command);
        lcd_8bit_enable(lcd);
    }
    
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType lcd_8bit_send_char(char_lcd_8bit_t *lcd, uint8 data){
    Std_ReturnType ret=E_OK;
    
    if(NULL == lcd){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_write(&(lcd->lcd_rs),PIN_HIGH);
        lcd_8bit_send_data_command(lcd,data);
        lcd_8bit_enable(lcd);
    }
    
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType lcd_8bit_send_char_pos(char_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data){
    Std_ReturnType ret=E_OK;
    
    if(NULL == lcd){
        ret=E_NOT_OK;
    }
    else{
        lcd_8bit_set_cursor(lcd,row,column);
        lcd_8bit_send_char(lcd,data);
    }
    
    return ret;
}

/**
 * 
 * @param lcd
 * @param str
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType lcd_8bit_send_string(char_lcd_8bit_t *lcd, uint8 *str){
    Std_ReturnType ret=E_OK;
    
    if(NULL == lcd || NULL == str){
        ret=E_NOT_OK;
    }
    else{
        while(*str){
            lcd_8bit_send_char(lcd,*str++);
        }
    }
    
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType lcd_8bit_send_string_pos(char_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str){
    Std_ReturnType ret=E_OK;
    
    if(NULL == lcd || NULL == str){
        ret=E_NOT_OK;
    }
    else{
        lcd_8bit_set_cursor(lcd,row,column);
        lcd_8bit_send_string(lcd,str);
    }
    
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param chr
 * @param mem_pos
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType lcd_8bit_send_custom_char(char_lcd_8bit_t *lcd, uint8 row, uint8 column,
                                         uint8 chr[], uint8 mem_pos){
    Std_ReturnType ret=E_OK;
    
    if(NULL == lcd){
        ret=E_NOT_OK;
    }
    else{
        lcd_8bit_send_command(lcd,LCD_CGRAM_START +(mem_pos*8));
        for(unsigned int i=0 ; i<8 ; i++){
            lcd_8bit_send_char(lcd,chr[i]);
        }
        lcd_8bit_send_char_pos(lcd,row,column,mem_pos);
    }
    
    return ret;
}

/**
 * 
 * @param value
 * @param str
 */
Std_ReturnType convert_byte_to_string(uint8 value , uint8 *str){
    Std_ReturnType ret=E_OK;
    
    if(NULL == str){
        ret=E_NOT_OK;
    }
    else{
        memset(str,'\0',4);
        sprintf(str,"%i",value);
    }
    
    return ret;
}

/**
 * 
 * @param value
 * @param str
 */
Std_ReturnType convert_short_to_string(uint16 value , uint8 *str){
    Std_ReturnType ret=E_OK;
    
    if(NULL == str){
        ret=E_NOT_OK;
    }
    else{
        memset(str,'\0',6);
        sprintf(str,"%i",value);
    }
    
    return ret;
}

/**
 * 
 * @param value
 * @param str
 */
Std_ReturnType convert_int_to_string(uint32 value , uint8 *str){
    Std_ReturnType ret=E_OK;
    
    if(NULL == str){
        ret=E_NOT_OK;
    }
    else{
        memset(str,'\0',11);
        sprintf(str,"%i",value);
    }
    
    return ret;
}

static Std_ReturnType lcd_4bit_send_data_command(char_lcd_4bit_t *lcd, uint8 _data_command){
    Std_ReturnType ret=E_OK;
    
    if(NULL == lcd){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_write(&(lcd->lcd_data[0]),(_data_command >> 0) & (uint8)0x01);
        gpio_pin_write(&(lcd->lcd_data[1]),(_data_command >> 1) & (uint8)0x01);
        gpio_pin_write(&(lcd->lcd_data[2]),(_data_command >> 2) & (uint8)0x01);
        gpio_pin_write(&(lcd->lcd_data[3]),(_data_command >> 3) & (uint8)0x01);
    }
    
    return ret;
}

static Std_ReturnType lcd_4bit_enable(char_lcd_4bit_t *lcd){
    Std_ReturnType ret=E_OK;
    
    if(NULL == lcd){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_write(&(lcd->lcd_en),PIN_HIGH);
        __delay_us(5);
        gpio_pin_write(&(lcd->lcd_en),PIN_LOW);
    }
    
    return ret;
}

static Std_ReturnType lcd_4bit_set_cursor(char_lcd_4bit_t *lcd, uint8 row, uint8 column){
    Std_ReturnType ret=E_OK;
    column--;
    if(NULL == lcd){
        ret=E_NOT_OK;
    }
    else{
        switch(row){
            case ROW1 : lcd_4bit_send_command(lcd, (0x80 + column)); break;
            case ROW2 : lcd_4bit_send_command(lcd, (0xc0 + column)); break;
            case ROW3 : lcd_4bit_send_command(lcd, (0x94 + column)); break;
            case ROW4 : lcd_4bit_send_command(lcd, (0xd4 + column)); break;
        } 
    }
    
    return ret;
}

static Std_ReturnType lcd_8bit_send_data_command(char_lcd_8bit_t *lcd, uint8 _data_command){
    Std_ReturnType ret=E_OK;
    
    if(NULL == lcd){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_write(&(lcd->lcd_data[0]),(_data_command >> 0) & (uint8)0x01);
        gpio_pin_write(&(lcd->lcd_data[1]),(_data_command >> 1) & (uint8)0x01);
        gpio_pin_write(&(lcd->lcd_data[2]),(_data_command >> 2) & (uint8)0x01);
        gpio_pin_write(&(lcd->lcd_data[3]),(_data_command >> 3) & (uint8)0x01);
        gpio_pin_write(&(lcd->lcd_data[4]),(_data_command >> 4) & (uint8)0x01);
        gpio_pin_write(&(lcd->lcd_data[5]),(_data_command >> 5) & (uint8)0x01);
        gpio_pin_write(&(lcd->lcd_data[6]),(_data_command >> 6) & (uint8)0x01);
        gpio_pin_write(&(lcd->lcd_data[7]),(_data_command >> 7) & (uint8)0x01);
    }
    
    return ret;
}

static Std_ReturnType lcd_8bit_enable(char_lcd_8bit_t *lcd){
    Std_ReturnType ret=E_OK;
    
    if(NULL == lcd){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_write(&(lcd->lcd_en),PIN_HIGH);
        __delay_us(5);
        gpio_pin_write(&(lcd->lcd_en),PIN_LOW);
    }
    
    return ret;
}

static Std_ReturnType lcd_8bit_set_cursor(char_lcd_8bit_t *lcd, uint8 row, uint8 column){
    Std_ReturnType ret=E_OK;
    column--;
    if(NULL == lcd){
        ret=E_NOT_OK;
    }
    else{
        switch(row){
            case ROW1 : lcd_8bit_send_command(lcd, (0x80 + column)); break;
            case ROW2 : lcd_8bit_send_command(lcd, (0xc0 + column)); break;
            case ROW3 : lcd_8bit_send_command(lcd, (0x94 + column)); break;
            case ROW4 : lcd_8bit_send_command(lcd, (0xd4 + column)); break;
        } 
    }
    
    return ret;
}