/*
 * File:   hal_gpio.c
 * Author: Abdelrhman Mohsen
 *
 * Created on January 27, 2023, 8:22 PM
 */

#include "hal_gpio.h"

volatile uint8 *TRIS_register[] = {&TRISA ,&TRISB ,&TRISC ,&TRISD ,&TRISE};
volatile uint8 *PORT_register[] = {&PORTA ,&PORTB ,&PORTC ,&PORTD ,&PORTE};
volatile uint8 *LAT_register[]  = {&LATA  ,&LATB  ,&LATC  ,&LATD  ,&LATE};


/**
 * 
 * @param _pin_config
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
#if GPIO_PORT_PIN_CONFIGRATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_initialize(pin_config_t *_pin_config){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _pin_config || _pin_config->pin > PIN_MAX_NUMBER-1){
        ret=E_NOT_OK;
    }
    else{
        switch(_pin_config->direction){
            case PIN_DIRECTION_OUTPUT :
                CLEAR_BIT(TRIS_register[_pin_config->port],_pin_config->pin);
                gpio_pin_write(_pin_config,_pin_config->logic);
                ret=E_OK;
                break;
                
            case PIN_DIRECTION_INPUT :
                SET_BIT(TRIS_register[_pin_config->port],_pin_config->pin);
                ret=E_OK;
                break;
            
            default: ret=E_NOT_OK;
        }
    }
    
    return ret;
}
#endif

/**
 * 
 * @param _pin_config
 * @param direction_status
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
#if GPIO_PORT_PIN_CONFIGRATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_status(pin_config_t *_pin_config, direction_t *direction_status){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _pin_config || NULL == direction_status || _pin_config->pin > PIN_MAX_NUMBER-1){
        ret=E_NOT_OK;
    }
    else{
        *direction_status = READ_BIT(TRIS_register[_pin_config->port],_pin_config->pin);
    }
    
    return ret;
}
#endif

/**
 * 
 * @param _pin_config
 * @param logic
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
#if GPIO_PORT_PIN_CONFIGRATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_write(pin_config_t *_pin_config, logic_t logic){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _pin_config || _pin_config->pin > PIN_MAX_NUMBER-1){
        ret=E_NOT_OK;
    }
    else{
        switch(logic){
            case PIN_LOW :
                CLEAR_BIT(LAT_register[_pin_config->port],_pin_config->pin);
                ret=E_OK;
                break;
               
            case PIN_HIGH :
                SET_BIT(LAT_register[_pin_config->port],_pin_config->pin);
                ret=E_OK;
                break;
                
            default: ret=E_NOT_OK;
        }
    }
    
    return ret;
}
#endif

/**
 * 
 * @param _pin_config
 * @param logic
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
#if GPIO_PORT_PIN_CONFIGRATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_read(pin_config_t *_pin_config, logic_t *logic){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _pin_config || NULL == logic || _pin_config->pin > PIN_MAX_NUMBER-1){
        ret=E_NOT_OK;
    }
    else{
        *logic = READ_BIT(PORT_register[_pin_config->port],_pin_config->pin);
        ret=E_OK;
    }
    
    return ret;
}
#endif

/**
 * 
 * @param _pin_config
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
#if GPIO_PORT_PIN_CONFIGRATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle(pin_config_t *_pin_config){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _pin_config || _pin_config->pin > PIN_MAX_NUMBER-1){
        ret=E_NOT_OK;
    }
    else{
        TOGGLE_BIT(PORT_register[_pin_config->port],_pin_config->pin);
        ret=E_OK;
    }
    
    return ret;
}
#endif

/**
 * 
 * @param _port_config
 * @param direction
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
#if GPIO_PORT_PIN_CONFIGRATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_initialize(port_index_t _port_config, uint8 direction){
    Std_ReturnType ret=E_NOT_OK;
    
    if(_port_config > PORT_MAX_NUMBER-1){
        ret=E_NOT_OK;
    }
    else{
        REGHWR(TRIS_register[_port_config])=direction;
        REGHWR(LAT_register[_port_config])=PIN_LOW;
        ret=E_OK;      
    }
    
    return ret;
}
#endif

/**
 * 
 * @param _port_config
 * @param direction_status
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
#if GPIO_PORT_PIN_CONFIGRATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_direction_status(port_index_t _port_config, uint8 *direction_status){
    Std_ReturnType ret=E_NOT_OK;
    
    if(_port_config > PORT_MAX_NUMBER-1 || NULL == direction_status){
        ret=E_NOT_OK;
    }
    else{
        *direction_status = REGHWR(TRIS_register[_port_config]);
        ret=E_OK; 
    }
    
    return ret;
}
#endif

/**
 * 
 * @param _port_config
 * @param logic
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
#if GPIO_PORT_PIN_CONFIGRATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_write(port_index_t _port_config, uint8 logic){
    Std_ReturnType ret=E_NOT_OK;
    
    if(_port_config > PORT_MAX_NUMBER-1){
        ret=E_NOT_OK;
    }
    else{
        REGHWR(LAT_register[_port_config])=logic;
        ret=E_OK;  
    }
    
    return ret;
}
#endif

/**
 * 
 * @param  _port_config
 * @param  logic
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
#if GPIO_PORT_PIN_CONFIGRATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_read(port_index_t _port_config, uint8 *logic){
    Std_ReturnType ret=E_NOT_OK;
    
    if(_port_config > PORT_MAX_NUMBER-1 || NULL == logic){
        ret=E_NOT_OK;
    }
    else{
        *logic = REGHWR(PORT_register[_port_config]);
        ret=E_OK; 
    }
    
    return ret;
}
#endif

/**
 * 
 * @param _port_config
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
#if GPIO_PORT_PIN_CONFIGRATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_toggle(port_index_t _port_config){
    Std_ReturnType ret=E_NOT_OK;
    
    if(_port_config > PORT_MAX_NUMBER-1){
        ret=E_NOT_OK;
    }
    else{
        REGHWR(LAT_register[_port_config])^=0xff;
        ret=E_OK;
    }
    
    return ret;
}
#endif
