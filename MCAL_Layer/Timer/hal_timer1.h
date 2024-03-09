/* 
 * File:   hal_timer1.h
 * Author: mohsen
 *
 * Created on February 18, 2023, 11:05 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/******* section : Includes *******/
#include "../mcal_std_types.h"
#include "../compiler.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/******* section : macros Declarations *******/
#define TMR1_TIMER_MODE_ENABLE              0
#define TMR1_COUNTER_MODE_ENABLE            1

#define TMR1_SYNC_COUNTER                   0
#define TMR1_ASYNC_COUNTER                  1

#define TMR1_OSC_ENABLE_CONFG               1
#define TMR1_OSC_DISABLE_CONFG              0

#define TMR1_PRESCALER_DIV_BY_1             0
#define TMR1_PRESCALER_DIV_BY_2             1
#define TMR1_PRESCALER_DIV_BY_4             2
#define TMR1_PRESCALER_DIV_BY_8             3

#define TMR1_8BIT_MODE_ENABLE               0
#define TMR1_16BIT_MODE_ENABLE              1

/******* section : function-like macros Declarations *******/
#define TMR1_ENABLE()                       (T1CONbits.TMR1ON=1)
#define TMR1_DISABLE()                      (T1CONbits.TMR1ON=0)

#define TMR1_TIMER_MODE()                   (T1CONbits.TMR1CS=0)
#define TMR1_COUNTER_MODE()                 (T1CONbits.TMR1CS=1)

#define TMR1_SYNC_COUNTER_MODE()            (T1CONbits.T1SYNC=0)
#define TMR1_ASYNC_COUNTER_MODE()           (T1CONbits.T1SYNC=1)

#define TMR1_OSC_ENABLE()                   (T1CONbits.T1OSCEN=1)
#define TMR1_OSC_DISABLE()                  (T1CONbits.T1OSCEN=0)

#define TMR1_PRESCELER_CONFG(_X)            (T1CONbits.T1CKPS=_X)

#define TMR1_GET_OSC_STATUS()               (T1CONbits.T1RUN)

#define TMR1_RIGESTER_MODE(_X)              (T1CONbits.RD16=_X)

/******* section : Data Types Declarations *******/
typedef struct{
#if TMR0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* interruptHandler)(void);
 #if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE   
    interrupt_priorty_t priority;
#endif
#endif
    uint16 preload_value;
    uint8  prescaler         :2;
    uint8  working_mode      :1;
    uint8  counter_sync      :1;
    uint8  timer1_osc        :1;
    uint8  register_mode     :1;
    uint8  reserved          :2;
}timer1_t;

/******* section : Function Declarations *******/
Std_ReturnType timer1_init(const timer1_t *_timer1);
Std_ReturnType timer1_Deinit(const timer1_t *_timer1);
Std_ReturnType timer1_write_value(const timer1_t *_timer1, uint16 value);
Std_ReturnType timer1_read_value(const timer1_t *_timer1, uint16 *value);

#endif	/* HAL_TIMER1_H */

