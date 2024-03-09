/* 
 * File:   hal_gpio.h
 * Author: mohsen
 *
 * Created on January 27, 2023, 11:23 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

 /******* section : Includes *******/
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "gpio_config.h"

/******* section : macros Declarations *******/
#define BIT_MASK     0x01
#define GPIO_PORT_PIN_CONFIGRATIONS   CONFIG_ENABLE

/******* section : function-like macros Declarations *******/
#define REGHWR(_x)                  (*((volatile uint8 *)(_x)))

#define SET_BIT(REG,PIN_POSN)       (REGHWR(REG) |= (BIT_MASK << PIN_POSN))
#define CLEAR_BIT(REG,PIN_POSN)     (REGHWR(REG) &=~(BIT_MASK << PIN_POSN))
#define TOGGLE_BIT(REG,PIN_POSN)    (REGHWR(REG) ^= (BIT_MASK << PIN_POSN))
#define READ_BIT(REG,PIN_POSN)      ((REGHWR(REG) >> PIN_POSN) & BIT_MASK)

/******* section : Data Types Declarations *******/
typedef enum{
    PIN_DIRECTION_OUTPUT,
    PIN_DIRECTION_INPUT        
}direction_t;

typedef enum{
    PIN_LOW,
    PIN_HIGH
}logic_t;

typedef enum{
    PORTA_INDEX,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
}port_index_t;

typedef enum{
    PIN0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7        
}pin_index_t;

typedef struct{
    uint8 port       :3;
    uint8 pin        :3;
    uint8 direction  :1;
    uint8 logic      :1;
}pin_config_t;


/******* section : Function Declarations *******/
Std_ReturnType gpio_pin_initialize(pin_config_t *_pin_config);
Std_ReturnType gpio_pin_write(pin_config_t *_pin_config, logic_t logic);
Std_ReturnType gpio_pin_direction_status(pin_config_t *_pin_config, direction_t *direction_status);
Std_ReturnType gpio_pin_read(pin_config_t *_pin_config, logic_t *logic);
Std_ReturnType gpio_pin_toggle(pin_config_t *_pin_config);

Std_ReturnType gpio_port_initialize(port_index_t _port_config, uint8 direction);
Std_ReturnType gpio_port_direction_status(port_index_t _port_config, uint8 *direction_status);
Std_ReturnType gpio_port_write(port_index_t _port_config, uint8 logic);
Std_ReturnType gpio_port_read(port_index_t _port_config, uint8 *logic);
Std_ReturnType gpio_port_toggle(port_index_t _port_config);

#endif	/* HAL_GPIO_H */

