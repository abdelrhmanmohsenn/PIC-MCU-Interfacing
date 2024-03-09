/* 
 * File:   ecu_relay.h
 * Author: mohsen
 *
 * Created on February 2, 2023, 6:14 PM
 */

#include "ecu_relay.h"

/**
 * 
 * @param relay
 * @return 
 */
Std_ReturnType relay_initialize(const relay_t *relay){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == relay){
        ret=E_NOT_OK;
    }
    else{
        pin_config_t relay_pin={.port=relay->port ,.pin=relay->pin ,.direction=PIN_DIRECTION_OUTPUT ,.logic=PIN_LOW};
        gpio_pin_initialize(&relay_pin);
        ret=E_OK;
    }
    
    return ret;
}

/**
 * 
 * @param relay
 * @return 
 */
Std_ReturnType relay_turn_on(const relay_t *relay){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == relay){
        ret=E_NOT_OK;
    }
    else{
        pin_config_t relay_pin={.port=relay->port ,.pin=relay->pin ,.direction=PIN_DIRECTION_OUTPUT ,.logic=PIN_LOW};
        gpio_pin_write(&relay_pin, PIN_HIGH);
        ret=E_OK;
    }
    
    return ret;
}

/**
 * 
 * @param relay
 * @return 
 */
Std_ReturnType relay_turn_off(const relay_t *relay){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == relay){
        ret=E_NOT_OK;
    }
    else{
        pin_config_t relay_pin={.port=relay->port ,.pin=relay->pin ,.direction=PIN_DIRECTION_OUTPUT ,.logic=PIN_LOW};
        gpio_pin_write(&relay_pin, RELAY_OFF);
        ret=E_OK;
    }
    
    return ret;
}
