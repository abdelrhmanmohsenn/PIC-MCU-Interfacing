/* 
 * File:   ecu_led.c
 * Author: mohsen
 *
 * Created on January 28, 2023, 12:09 AM
 */

#include "ecu_led.h"

/**
 * 
 * @param led_config
 * @return 
 */
Std_ReturnType led_initialize(const led_t *led_config){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == led_config){
        ret=E_NOT_OK;
    }
    else{
       pin_config_t _led={.port=led_config->port,.pin=led_config->pin,
                          .direction=PIN_DIRECTION_OUTPUT,.logic=led_config->led_status};
       gpio_pin_initialize(&_led);
       ret=E_OK;
    }
    
    return ret;
}

/**
 * 
 * @param led_config
 * @return 
 */
Std_ReturnType led_turn_on(const led_t *led_config){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == led_config){
        ret=E_NOT_OK;
    }
    else{
       pin_config_t _led={.port=led_config->port,.pin=led_config->pin,
                          .direction=PIN_DIRECTION_OUTPUT,.logic=led_config->led_status};
       gpio_pin_write(&_led,PIN_HIGH);
       ret=E_OK;
    }
    
    return ret;
}

/**
 * 
 * @param led_config
 * @return 
 */
Std_ReturnType led_turn_off(const led_t *led_config){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == led_config){
        ret=E_NOT_OK;
    }
    else{
       pin_config_t _led={.port=led_config->port,.pin=led_config->pin,
                          .direction=PIN_DIRECTION_OUTPUT,.logic=led_config->led_status};
       gpio_pin_write(&_led,PIN_LOW);
       ret=E_OK;
    }
    
    return ret;
}

/**
 * 
 * @param led_config
 * @return 
 */
Std_ReturnType led_toggle(const led_t *led_config){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == led_config){
        ret=E_NOT_OK;
    }
    else{
       pin_config_t _led={.port=led_config->port,.pin=led_config->pin,
                          .direction=PIN_DIRECTION_OUTPUT,.logic=led_config->led_status};
       gpio_pin_toggle(&_led);
       ret=E_OK;
    }
    
    return ret;
}
/***
Std_ReturnType led_run_initialize(port_index_t port_index){
    Std_ReturnType ret=E_NOT_OK;
    
    if(7 < port_index){
        ret=E_NOT_OK;
    }
    else{
        gpio_port_initialize(port_index ,PIN_DIRECTION_OUTPUT);
        ret=E_OK;
        
    }
    
    return ret;
}

Std_ReturnType led_run(port_index_t port_index){
    Std_ReturnType ret=E_NOT_OK;
    
    if(7 < port_index){
        ret=E_NOT_OK;
    }
    else{
        for(unsigned int i=0 ; i<8 ; i++){
            led_t led1={.port=PORTC_INDEX,.pin=i,.led_status=PIN_LOW};
            led_turn_on(&led1);
            __delay_ms(100);
            led_turn_off(&led1);
        } 
    }
    
    return ret;
}*/