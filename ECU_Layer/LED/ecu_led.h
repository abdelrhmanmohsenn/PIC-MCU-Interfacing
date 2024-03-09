/* 
 * File:   ecu_led.h
 * Author: mohsen
 *
 * Created on January 28, 2023, 12:09 AM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/******* section : Includes *******/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"

/******* section : macros Declarations *******/

/******* section : function-like macros Declarations *******/

/******* section : Data Types Declarations *******/
typedef enum{
    LED_OFF,
    LED_ON
}led_status_t;

typedef struct{
    uint8 port       :3;
    uint8 pin        :3;
    uint8 led_status :1;
    uint8 reserved   :1;
}led_t;

/******* section : Function Declarations *******/
Std_ReturnType led_initialize(const led_t *led_config);
Std_ReturnType led_turn_on(const led_t *led_config);
Std_ReturnType led_turn_off(const led_t *led_config);
Std_ReturnType led_toggle(const led_t *led_config);
Std_ReturnType led_run(port_index_t port_index);
Std_ReturnType led_run_initialize(port_index_t port_index);

#endif	/* ECU_LED_H */

