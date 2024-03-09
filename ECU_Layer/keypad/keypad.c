/* 
 * File:   keypad.c
 * Author: mohsen
 *
 * Created on February 5, 2023, 7:52 PM
 */

#include "keypad.h"

static const uint8 keys_array[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'E','0','=','+'}};

/**
 * 
 * @param keypad
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType keypad_initialize(keypad_t *keypad){
    Std_ReturnType ret=E_OK;
    
    if(NULL == keypad){
        ret=E_NOT_OK;
    }
    else{
        for(int i=0 ; i<4 ; i++){
            gpio_pin_initialize(&(keypad->keypad_rows_pins[i]));
            gpio_pin_initialize(&(keypad->keypad_columns_pins[i]));
        }
    }
    
    return ret;
}

/**
 * 
 * @param keypad
 * @param scanned_value
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType keypad_scan(keypad_t *keypad, uint8 *scanned_value){
    Std_ReturnType ret=E_OK;
    logic_t read_value=0;
    uint8 rows=0 , columns=0 ,rows1=0;
    
    if(NULL == keypad){
        ret=E_NOT_OK;
    }
    else{
        for(rows=0 ; rows<4 ; rows++){
            for(rows1=0 ; rows1<4 ; rows1++){
                gpio_pin_write(&(keypad->keypad_rows_pins[rows1]),PIN_LOW);
            }
            gpio_pin_write(&(keypad->keypad_rows_pins[rows]),PIN_HIGH);
            __delay_ms(10);
            for(columns=0 ; columns<4 ; columns++){
                gpio_pin_read(&(keypad->keypad_columns_pins[columns]),&read_value);
                if(read_value == 1){
                    *scanned_value=keys_array[rows][columns];
                }
            }
        } 
    }
    
    return ret;
}