/* 
 * File:   hal_timer3.h
 * Author: mohsen
 *
 * Created on February 19, 2023, 10:23 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/******* section : Includes *******/
#include "../mcal_std_types.h"
#include "../compiler.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/******* section : macros Declarations *******/
#define TMR3_TIMER_MODE_ENABLE              0
#define TMR3_COUNTER_MODE_ENABLE            1

#define TMR3_SYNC_COUNTER                   0
#define TMR3_ASYNC_COUNTER                  1

#define TMR3_PRESCALER_DIV_BY_1             0
#define TMR3_PRESCALER_DIV_BY_2             1
#define TMR3_PRESCALER_DIV_BY_4             2
#define TMR3_PRESCALER_DIV_BY_8             3

#define TMR3_8BIT_MODE_ENABLE               0
#define TMR3_16BIT_MODE_ENABLE              1

/******* section : function-like macros Declarations *******/
#define TMR3_ENABLE()                       (T3CONbits.TMR3ON=1)
#define TMR3_DISABLE()                      (T3CONbits.TMR3ON=0)

#define TMR3_TIMER_MODE()                   (T3CONbits.TMR3CS=0)
#define TMR3_COUNTER_MODE()                 (T3CONbits.TMR3CS=1)

#define TMR3_SYNC_COUNTER_MODE()            (T3CONbits.T3SYNC=0)
#define TMR3_ASYNC_COUNTER_MODE()           (T3CONbits.T3SYNC=1)

#define TMR3_PRESCELER_CONFG(_X)            (T3CONbits.T3CKPS=_X)

#define TMR3_RIGESTER_MODE(_X)              (T3CONbits.RD16=_X)

/******* section : Data Types Declarations *******/
typedef struct{
#if TMR3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* interruptHandler)(void);
 #if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE   
    interrupt_priorty_t priority;
#endif
#endif
    uint16 preload_value;
    uint8  prescaler         :2;
    uint8  working_mode      :1;
    uint8  counter_sync      :1;
    uint8  register_mode     :1;
    uint8  reserved          :3;
}timer3_t;

/******* section : Function Declarations *******/
Std_ReturnType timer3_init(const timer3_t *_timer3);
Std_ReturnType timer3_Deinit(const timer3_t *_timer3);
Std_ReturnType timer3_write_value(const timer3_t *_timer3, uint16 value);
Std_ReturnType timer3_read_value(const timer3_t *_timer3, uint16 *value);

#endif	/* HAL_TIMER3_H */

