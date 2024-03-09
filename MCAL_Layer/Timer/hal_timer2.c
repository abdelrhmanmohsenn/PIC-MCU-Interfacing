/* 
 * File:   hal_timer2.c
 * Author: mohsen
 *
 * Created on February 19, 2023, 8:42 PM
 */

#include "hal_timer2.h"

static uint8 l_preload_value=0;
void (* l_TMR2_interruptHandler)(void)=NULL;

void TMR2_ISR(void){
    TMR2_FlagClear();
    TMR2=l_preload_value;
    if(l_TMR2_interruptHandler){ l_TMR2_interruptHandler(); }
    else{/* Nothing */}
}

/**
 * 
 * @param _timer2
 * @return 
 */
Std_ReturnType timer2_init(const timer2_t *_timer2){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _timer2){
        ret=E_NOT_OK;
    }
    else{
        TMR2_DISABLE();
        TMR2_FlagClear();
        TMR2_PRESCELER_CONFG(_timer2->prescaler);
        TMR2_POSTSCELER_CONFG(_timer2->postscaler);
        l_preload_value=_timer2->preload_value;
        timer2_write_value(_timer2,_timer2->preload_value);
#if TMR2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TMR2_InterruptEnable();
        l_TMR2_interruptHandler=_timer2->interruptHandler;
#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE   
        INTERRUPT_PriortyLevelEnable();
        if(INTERRUPT_HIGH_PRIORTY == _timer2->priority){
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else if(INTERRUPT_LOW_PRIORTY == _timer2->priority){
            INTERRUPT_GlobalInterruptLowEnable();
        }
        else{/* Nothing */}
        
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        TMR2_ENABLE();
    }
    
    return ret;
}

/**
 * 
 * @param _timer2
 * @return 
 */
Std_ReturnType timer2_Deinit(const timer2_t *_timer2){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _timer2){
        ret=E_NOT_OK;
    }
    else{
        TMR2_DISABLE();
#if TMR2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TMR2_InterruptDisable();
#endif
    }
    
    return ret;
}

/**
 * 
 * @param _timer2
 * @param value
 * @return 
 */
Std_ReturnType timer2_write_value(const timer2_t *_timer2, uint8 value){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _timer2){
        ret=E_NOT_OK;
    }
    else{
        TMR2=value;
    }
    
    return ret;
}

/**
 * 
 * @param _timer2
 * @param value
 * @return 
 */
Std_ReturnType timer2_read_value(const timer2_t *_timer2, uint8 *value){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _timer2){
        ret=E_NOT_OK;
    }
    else{
        *value=TMR2;
    }
    
    return ret;
}

