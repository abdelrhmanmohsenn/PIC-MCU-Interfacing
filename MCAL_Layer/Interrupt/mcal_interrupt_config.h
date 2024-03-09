/* 
 * File:   mcal_interrupt_config.h
 * Author: mohsen
 *
 * Created on February 11, 2023, 3:55 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/******* section : Includes *******/
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../GPIO/hal_gpio.h"

/******* section : macros Declarations *******/

/******* section : function-like macros Declarations *******/
#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro will enable priority levels on interrupts. */
#define INTERRUPT_PriortyLevelEnable()           (RCONbits.IPEN=1)
/* This macro will disable  priority levels on interrupts. */
#define INTERRUPT_PriortyLevelDisable()          (RCONbits.IPEN=0)

/* This macro will enable high priority global interrupts. */
#define INTERRUPT_GlobalInterruptHighEnable()    (INTCONbits.GIEH=1)
/* This macro will disable high priority global interrupts. */
#define INTERRUPT_GlobalInterruptHighDisable()   (INTCONbits.GIEH=0)

/* This macro will enable low priority global interrupts. */
#define INTERRUPT_GlobalInterruptLowEnable()     (INTCONbits.GIEL=1)
/* This macro will disable low priority global interrupts. */
#define INTERRUPT_GlobalInterruptLowDisable()    (INTCONbits.GIEL=0)
#else
/* This macro will enable global interrupts. */
#define INTERRUPT_GlobalInterruptEnable()        (INTCONbits.GIE=1)
/* This macro will disable global interrupts. */
#define INTERRUPT_GlobalInterruptDisable()       (INTCONbits.GIE=0)

/* This macro will enable peripheral interrupts. */
#define INTERRUPT_PeripheralInterruptEnable()    (INTCONbits.PEIE=1)
/* This macro will disable peripheral interrupts. */
#define INTERRUPT_PeripheralInterruptDisable()   (INTCONbits.PEIE=0)
#endif

/******* section : Data Types Declarations *******/
typedef enum{
    INTERRUPT_LOW_PRIORTY=0,
    INTERRUPT_HIGH_PRIORTY
}interrupt_priorty_t;

/******* section : Function Declarations *******/

#endif	/* MCAL_INTERRUPT_CONFIG_H */

