/* 
 * File:   ecu_dc_motor.h
 * Author: mohsen
 *
 * Created on February 3, 2023, 4:51 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/******* section : Includes *******/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_dc_motor_cfg.h"

/******* section : macros Declarations *******/
#define DC_MOTOR_ON    0x01
#define DC_MOTOR_OFF   0x00

/******* section : function-like macros Declarations *******/

/******* section : Data Types Declarations *******/
typedef struct{
    pin_config_t motor_pin[2];
}dc_motor_t;

/******* section : Function Declarations *******/
Std_ReturnType dc_motor_initialize(const dc_motor_t *dc_motor);
Std_ReturnType dc_motor_move_left(const dc_motor_t *dc_motor);
Std_ReturnType dc_motor_move_right(const dc_motor_t *dc_motor);
Std_ReturnType dc_motor_stop(const dc_motor_t *dc_motor);

#endif	/* ECU_DC_MOTOR_H */

