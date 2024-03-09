/* 
 * File:   application.h
 * Author: mohsen
 *
 * Created on January 28, 2023, 12:17 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/******* section : Includes *******/
#include "ECU_Layer/LED/ecu_led.h"
#include "ECU_Layer/push_button/ecu_button.h"
#include "ECU_Layer/Relay/ecu_relay.h"
#include "ECU_Layer/dc_motor/ecu_dc_motor.h"
#include "ECU_Layer/7_segment/ecu_7_segment.h"
#include "ECU_Layer/keypad/keypad.h"
#include "ECU_Layer/char_lcd/ecu_char_lcd.h"
#include "MCAL_Layer/Interrupt/mcal_interrupt_manager.h"
#include "MCAL_Layer/ADC/hal_adc.h"
#include "MCAL_Layer/Timer/hal_timer0.h"
#include "MCAL_Layer/Timer/hal_timer1.h"
#include "MCAL_Layer/Timer/hal_timer2.h"
#include "MCAL_Layer/Timer/hal_timer3.h"
#include "MCAL_Layer/ccp/hal_ccp.h"
#include "MCAL_Layer/USART/hal_usart.h"
#include "MCAL_Layer/SPI/hal_spi.h"
#include "MCAL_Layer/I2C/hal_i2c.h"

/******* section : macros Declarations *******/

/******* section : function-like macros Declarations *******/

/******* section : Data Types Declarations *******/

/******* section : Function Declarations *******/
void application_initialize(void);


#endif	/* APPLICATION_H */

