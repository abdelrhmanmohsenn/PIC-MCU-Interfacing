/* 
 * File:   ecu_dc_motor.c
 * Author: mohsen
 *
 * Created on February 3, 2023, 4:51 PM
 */

#include "ecu_dc_motor.h"

/**
 * @ref    this function initialize the dc motor
 * @param  dc_motor
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType dc_motor_initialize(const dc_motor_t *dc_motor){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == dc_motor){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_initialize(&dc_motor->motor_pin[0]);
        gpio_pin_initialize(&dc_motor->motor_pin[1]);
        ret = E_OK;
    }
    
    return ret;
}

/**
 * @ref    this function move the dc motor left direction
 * @param  dc_motor
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType dc_motor_move_left(const dc_motor_t *dc_motor){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == dc_motor){ 
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_write(&dc_motor->motor_pin[0],DC_MOTOR_ON);
        gpio_pin_write(&dc_motor->motor_pin[1],DC_MOTOR_OFF);
        ret = E_OK;
    }
    
    return ret;
}

/**
 * @ref    this function move the dc motor right direction
 * @param  dc_motor
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType dc_motor_move_right(const dc_motor_t *dc_motor){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == dc_motor){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_write(&dc_motor->motor_pin[1],DC_MOTOR_ON);
        gpio_pin_write(&dc_motor->motor_pin[0],DC_MOTOR_OFF);
        ret = E_OK;
    }
    
    return ret;
}

/**
 * @ref    this function stops the dc motor
 * @param  dc_motor
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType dc_motor_stop(const dc_motor_t *dc_motor){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == dc_motor){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_write(&dc_motor->motor_pin[1],DC_MOTOR_OFF);
        gpio_pin_write(&dc_motor->motor_pin[0],DC_MOTOR_OFF);
        ret = E_OK;
    }
    
    return ret;
}
