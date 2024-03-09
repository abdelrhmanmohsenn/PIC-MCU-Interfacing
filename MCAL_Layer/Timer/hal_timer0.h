/* 
 * File:   hal_timer0.h
 * Author: mohsen
 *
 * Created on February 17, 2023, 8:36 PM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/******* section : Includes *******/
#include "../mcal_std_types.h"
#include "../compiler.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/******* section : macros Declarations *******/

#define TMR0_PRESCALE_ENABLE                1
#define TMR0_PRESCELE_DISABLE               0

#define TMR0_EDGE_HIGH                      1
#define TMR0_EDGE_LOW                       0

#define TMR0_8_BIT_MODE_ENABLE              1
#define TMR0_16_BIT_MODE_ENABLE             0

#define TMR0_TIMER_MODE_ENABLE              1
#define TMR0_COUNTER_MODE_ENABLE            0

/******* section : function-like macros Declarations *******/

#define TMR0_PRESCELER_ENABLE()             (T0CONbits.PSA=0)
#define TMR0_PRESCELER_DISABLE()            (T0CONbits.PSA=1)

#define TMR0_SOURCE_EDGE_HIGH()             (T0CONbits.T0SE=1)
#define TMR0_SOURCE_EDGE_LOW()              (T0CONbits.T0SE=0)

#define TMR0_TIMER_MODE()                   (T0CONbits.T0CS=0)
#define TMR0_COUNTER_MODE()                 (T0CONbits.T0CS=1)

#define TMR0_8_BIT_MODE()                   (T0CONbits.T08BIT=1)
#define TMR0_16_BIT_MODE()                  (T0CONbits.T08BIT=0)

#define TMR0_ENABLE()                       (T0CONbits.TMR0ON=1)
#define TMR0_DISABLE()                      (T0CONbits.TMR0ON=0)

/******* section : Data Types Declarations *******/
typedef enum{
    TIMER0_PRESCALER_DIV_BY_2= 0,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256
}timer0_prescaler_select_t;

typedef struct{
#if TMR0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* interruptHandler)(void);
 #if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE   
    interrupt_priorty_t priority;
#endif
#endif
    timer0_prescaler_select_t prescaler;
    uint16 preload_value;
    uint8 edge_source        :1;
    uint8 timer_mode         :1;
    uint8 bits_mode          :1;
    uint8 prescaler_enable   :1;
    uint8 reserved           :4;
}timer0_t;

/******* section : Function Declarations *******/
Std_ReturnType timer0_init(timer0_t *_timer0);
Std_ReturnType timer0_Deinit(timer0_t *_timer0);
Std_ReturnType timer0_write_value(timer0_t *_timer0, uint16 value);
Std_ReturnType timer0_read_value(timer0_t *_timer0, uint16 *value);

#endif	/* HAL_TIMER0_H */

