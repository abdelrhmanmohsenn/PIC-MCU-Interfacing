/* 
 * File:   ecu_button.c
 * Author: mohsen
 *
 * Created on February 2, 2023, 12:01 PM
 */


#include "ecu_button.h"

/**
 * @ref   this function initialize the pin the button is connected to
 * @param btn
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType button_initialize(const button_t *btn){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == btn){
        ret=E_NOT_OK;
    }
    else{
       ret = gpio_pin_initialize((btn->button_pin));
       
    }
    
    return ret;
}

/**
 * @ref   this function read the state of the button
 * @param btn
 * @param btn_state
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType button_read_state(const button_t *btn ,button_state_t *btn_state){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == btn || NULL == btn_state){
        ret=E_NOT_OK;
    }
    else{
        logic_t state;
        switch(btn->button_connection){
            case BUTTON_ACTIVE_HIGH :
                ret = gpio_pin_read((btn->button_pin), &state);
                if(PIN_HIGH == state){
                    *btn_state=BUTTON_PRESSED;
                }
                else{
                    *btn_state=BUTTON_RELEASED;
                } 
                break;
                
            case BUTTON_ACTIVE_LOW :
                ret = gpio_pin_read((btn->button_pin), &state);
                if(PIN_LOW == state){
                    *btn_state=BUTTON_PRESSED;
                }
                else{
                    *btn_state=BUTTON_RELEASED;
                }     
                break;
        }
        ret = E_OK;
    }
    
    return ret;
}
