/* 
 * File:   keypad.h
 * Author: mohsen
 *
 * Created on February 5, 2023, 7:52 PM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

/******* section : Includes *******/
#include "keypad_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/******* section : macros Declarations *******/


/******* section : function-like macros Declarations *******/

/******* section : Data Types Declarations *******/
typedef struct{
    pin_config_t keypad_rows_pins[4];
    pin_config_t keypad_columns_pins[4];
}keypad_t;

/******* section : Function Declarations *******/
Std_ReturnType keypad_initialize(keypad_t *keypad);
Std_ReturnType keypad_scan(keypad_t *keypad, uint8 *scanned_value);

#endif	/* KEYPAD_H */

