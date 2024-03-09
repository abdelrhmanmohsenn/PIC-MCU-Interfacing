/* 
 * File:   mcal_external_interrupt.h
 * Author: mohsen
 *
 * Created on February 11, 2023, 4:29 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/******* section : Includes *******/
#include "mcal_interrupt_config.h"

/******* section : macros Declarations *******/

/******* section : function-like macros Declarations *******/
#if INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine sets the interrupt enable for the external interrupt, INT0 */
#define EXT_INT0_InterruptEnable()           (INTCONbits.INT0IE=1)
/* This routine clears the interrupt enable for the external interrupt, INT0 */
#define EXT_INT0_InterruptDisable()          (INTCONbits.INT0IE=0)
/* This routine clears the interrupt Flag for the external interrupt, INT0 */
#define EXT_INT0_FlagClear()                 (INTCONbits.INT0IF=0)
/* This routine set the edge detect of the extern interrupt to negative edge */
#define EXT_INT0_RisingEdge()                (INTCON2bits.INTEDG0=1)
/* This routine set the edge detect of the extern interrupt to positive edge */
#define EXT_INT0_FallingEdge()               (INTCON2bits.INTEDG0=0)

/* This routine sets the interrupt enable for the external interrupt, INT1 */
#define EXT_INT1_InterruptEnable()           (INTCON3bits.INT1IE=1)
/* This routine clears the interrupt enable for the external interrupt, INT1 */
#define EXT_INT1_InterruptDisable()          (INTCON3bits.INT1IE=0)
/* This routine clears the interrupt Flag for the external interrupt, INT1 */
#define EXT_INT1_FlagClear()                 (INTCON3bits.INT1IF=0)
/* This routine set the edge detect of the extern interrupt to negative edge */
#define EXT_INT1_RisingEdge()                (INTCON2bits.INTEDG1=1)
/* This routine set the edge detect of the extern interrupt to positive edge */
#define EXT_INT1_FallingEdge()               (INTCON2bits.INTEDG1=0)

/* This routine sets the interrupt enable for the external interrupt, INT2 */
#define EXT_INT2_InterruptEnable()           (INTCON3bits.INT2IE=1)
/* This routine clears the interrupt enable for the external interrupt, INT2 */
#define EXT_INT2_InterruptDisable()          (INTCON3bits.INT2IE=0)
/* This routine clears the interrupt Flag for the external interrupt, INT2 */
#define EXT_INT2_FlagClear()                 (INTCON3bits.INT2IF=0)
/* This routine set the edge detect of the extern interrupt to negative edge */
#define EXT_INT2_RisingEdge()                (INTCON2bits.INTEDG2=1)
/* This routine set the edge detect of the extern interrupt to positive edge */
#define EXT_INT2_FallingEdge()               (INTCON2bits.INTEDG2=0)

#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the INT1 External Interrupt Priority to be High priority */
#define EXT_INT1_PriorityHigh()                 (INTCON3bits.INT1IP=1)
/* This routine set the INT1 External Interrupt Priority to be Low priority */
#define EXT_INT1_PriorityLow()                  (INTCON3bits.INT1IP=0)

/* This routine set the INT2 External Interrupt Priority to be High priority */
#define EXT_INT2_PriorityHigh()                 (INTCON3bits.INT2IP=1)
/* This routine set the INT2 External Interrupt Priority to be Low priority */
#define EXT_INT2_PriorityLow()                  (INTCON3bits.INT2IP=0)
#endif

#endif

#if INTERRUPT_ONCHANGE_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine sets the interrupt enable for the external interrupt, RBx */
#define EXT_RBx_InterruptEnable()            (INTCONbits.RBIE=1)
/* This routine clears the interrupt disable for the external interrupt, RBx */
#define EXT_RBx_InterruptDisable()           (INTCONbits.RBIE=0)
/* This routine clears the interrupt flag for the external interrupt, RBx */
#define EXT_RBx_FlagClear()                  (INTCONbits.RBIF=0)

#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the RBx External Interrupt Priority to be High priority */
#define EXT_RBx_PriorityHigh()               (INTCON2bits.RBIP=1)
/* This routine set the RBx External Interrupt Priority to be Low priority */
#define EXT_RBx_PriorityLow()                (INTCON2bits.RBIP=0)
#endif

#endif

/******* section : Data Types Declarations *******/
typedef enum{
    INTERRUPT_INT0=0,
    INTERRUPT_INT1,
    INTERRUPT_INT2        
}interrupt_src_t;

typedef enum{
    INTERRUPT_RISING_EGDE=0,
    INTERRUPT_FALLING__EGDE
}interrupt_edge_t;

typedef struct{
    void (* EXT_InterruptHandler)(void);
    interrupt_priorty_t priorty;
    interrupt_edge_t edge;
    interrupt_src_t src;
    pin_config_t pin;
}interrupt_INTx_t;

typedef struct{
    void (* EXT_InterruptHandlerHigh)(void);
    void (* EXT_InterruptHandlerLow)(void);
    interrupt_priorty_t priorty;
    pin_config_t mcu_pin;
}interrupt_RBx_t;

/******* section : Function Declarations *******/
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *_int_obj);
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *_int_obj);

Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *_int_obj);
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *_int_obj);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

