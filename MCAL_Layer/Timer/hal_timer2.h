/* 
 * File:   hal_timer2.h
 * Author: mohsen
 *
 * Created on February 19, 2023, 8:42 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/******* section : Includes *******/
#include "../mcal_std_types.h"
#include "../compiler.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/******* section : macros Declarations *******/
#define TMR2_PRESCALER_DIV_BY_1             0
#define TMR2_PRESCALER_DIV_BY_4             1
#define TMR2_PRESCALER_DIV_BY_16            2

#define TMR2_POSTSCELER_DIV_BY_1            0
#define TMR2_POSTSCELER_DIV_BY_2            1
#define TMR2_POSTSCELER_DIV_BY_3            2
#define TMR2_POSTSCELER_DIV_BY_4            3
#define TMR2_POSTSCELER_DIV_BY_5            4
#define TMR2_POSTSCELER_DIV_BY_6            5
#define TMR2_POSTSCELER_DIV_BY_7            6
#define TMR2_POSTSCELER_DIV_BY_8            7
#define TMR2_POSTSCELER_DIV_BY_9            8
#define TMR2_POSTSCELER_DIV_BY_10           9
#define TMR2_POSTSCELER_DIV_BY_11           10
#define TMR2_POSTSCELER_DIV_BY_12           11
#define TMR2_POSTSCELER_DIV_BY_13           12
#define TMR2_POSTSCELER_DIV_BY_14           13
#define TMR2_POSTSCELER_DIV_BY_15           14
#define TMR2_POSTSCELER_DIV_BY_16           15

/******* section : function-like macros Declarations *******/
#define TMR2_ENABLE()                       (T2CONbits.TMR2ON=1)
#define TMR2_DISABLE()                      (T2CONbits.TMR2ON=0)

#define TMR2_PRESCELER_CONFG(_X)            (T2CONbits.T2CKPS=_X)

#define TMR2_POSTSCELER_CONFG(_X)           (T2CONbits.T2OUTPS=_X)

/******* section : Data Types Declarations *******/
typedef struct{
#if TMR0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* interruptHandler)(void);
 #if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE   
    interrupt_priorty_t priority;
#endif
#endif
    uint8 preload_value;
    uint8 postscaler   :4;
    uint8 prescaler    :2;
    uint8 reserved     :2;
}timer2_t;

/******* section : Function Declarations *******/
Std_ReturnType timer2_init(const timer2_t *_timer2);
Std_ReturnType timer2_Deinit(const timer2_t *_timer2);
Std_ReturnType timer2_write_value(const timer2_t *_timer2, uint8 value);
Std_ReturnType timer2_read_value(const timer2_t *_timer2, uint8 *value);
#endif	/* HAL_TIMER2_H */

