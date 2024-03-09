/* 
 * File:   ecu_relay.h
 * Author: mohsen
 *
 * Created on February 2, 2023, 6:14 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/******* section : Includes *******/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_relay_cfg.h"

/******* section : macros Declarations *******/
#define RELAY_ON    0x01
#define RELAY_OFF   0x00


/******* section : function-like macros Declarations *******/

/******* section : Data Types Declarations *******/
typedef struct{
    uint8 port  :3;
    uint8 pin    :3;
    uint8 relay_status :1;
    uint8 reserved     :1;
}relay_t;


/******* section : Function Declarations *******/
Std_ReturnType relay_initialize(const relay_t *relay);
Std_ReturnType relay_turn_on(const relay_t *relay);
Std_ReturnType relay_turn_off(const relay_t *relay);
        
#endif	/* ECU_RELAY_H */

