/* 
 * File:   ecu_7_segment.h
 * Author: mohsen
 *
 * Created on February 5, 2023, 12:38 PM
 */

#ifndef ECU_7_SEGMENT_H
#define	ECU_7_SEGMENT_H

/******* section : Includes *******/
#include "ecu_7_segment_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/******* section : macros Declarations *******/
#define SEGMENT_PIN0     0
#define SEGMENT_PIN1     1
#define SEGMENT_PIN2     2
#define SEGMENT_PIN3     3

/******* section : function-like macros Declarations *******/

/******* section : Data Types Declarations *******/
typedef enum{
    SEGMENT_COMMON_ANAODE,
    SEGMENT_COMMON_CATHODE        
}segment_type_t;

typedef struct{
    pin_config_t    segment_pin[4];
    segment_type_t  segment_type;
}segment_t;

/******* section : Function Declarations *******/
Std_ReturnType segment_initialize(const segment_t *segment);
Std_ReturnType segment_write_number(const segment_t *segment, uint8 number);

#endif	/* ECU_7_SEGMENT_H */

