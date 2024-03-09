/* 
 * File:   hal_timer3.c
 * Author: mohsen
 *
 * Created on February 19, 2023, 10:23 PM
 */

#include "hal_timer3.h"

static uint16 l_preload_value=0;
static void (* l_TMR3_interruptHandler)(void)=NULL;

static inline void timer3_prescaler_config(timer3_t *_timer3);
static inline void timer3_register_mode_select(timer3_t *_timer3);
static inline void timer3_mode_select(timer3_t *_timer3);

void TMR3_ISR(void){
    TMR3_FlagClear();
    TMR3H=(uint8)(l_preload_value >> 8);
    TMR3L=(uint8)(l_preload_value);
    if(l_TMR3_interruptHandler){ l_TMR3_interruptHandler(); }
    else{/* Nothing */}
}

Std_ReturnType timer3_init(const timer3_t *_timer3){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _timer3){
        ret=E_NOT_OK;
    }
    else{
        TMR3_DISABLE();
        TMR3_FlagClear();
        timer3_prescaler_config(_timer3);
        timer3_mode_select(_timer3);
        timer3_register_mode_select(_timer3); 
        timer3_write_value(_timer3,_timer3->preload_value);
        l_preload_value=_timer3->preload_value;
#if TMR3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TMR3_InterruptEnable();
        l_TMR3_interruptHandler=_timer3->interruptHandler;
#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE   
        INTERRUPT_PriortyLevelEnable();
        if(INTERRUPT_HIGH_PRIORTY == _timer1->priority){
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else if(INTERRUPT_LOW_PRIORTY == _timer1->priority){
            INTERRUPT_GlobalInterruptLowEnable();
        }
        else{/* Nothing */}
        
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        TMR3_ENABLE();
    }
    
    return ret;
}

Std_ReturnType timer3_Deinit(const timer3_t *_timer3){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _timer3){
        ret=E_NOT_OK;
    }
    else{
        TMR3_DISABLE();
#if TMR3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TMR3_InterruptDisable();
#endif
    }
    
    return ret;
}

Std_ReturnType timer3_write_value(const timer3_t *_timer3, uint16 value){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _timer3){
        ret=E_NOT_OK;
    }
    else{
        TMR3H=(uint8)(value >> 8);
        TMR3L=(uint8)(value);
    }
    
    return ret;
}

Std_ReturnType timer3_read_value(const timer3_t *_timer3, uint16 *value){
    Std_ReturnType ret=E_NOT_OK;
    uint8 l_TMR3L = 0, l_TMR3H = 0; 
    if(NULL == _timer3 || NULL == value){
        ret=E_NOT_OK;
    }
    else{
        l_TMR3L = TMR1L;
        l_TMR3H = TMR1H;
        *value = (uint16)((l_TMR3H << 8) + l_TMR3L);
    }
    
    return ret;
}

/**
 * 
 * @param _timer1
 */
static inline void timer3_prescaler_config(timer3_t *_timer3){
    TMR3_PRESCELER_CONFG(_timer3->prescaler);
}

/**
 * 
 * @param _timer1
 */
static inline void timer3_register_mode_select(timer3_t *_timer3){
    TMR3_RIGESTER_MODE(_timer3->register_mode);
}

/**
 * 
 * @param _timer1
 */
static inline void timer3_mode_select(timer3_t *_timer3){
    if(TMR3_TIMER_MODE_ENABLE == _timer3->working_mode){
        TMR3_TIMER_MODE();
    }
    else if(TMR3_COUNTER_MODE_ENABLE == _timer3->working_mode){
        pin_config_t pin_t1={.port=PORTC_INDEX,.pin=PIN0,.direction=PIN_DIRECTION_INPUT,.logic=PIN_LOW};
        gpio_pin_initialize(&pin_t1);
        TMR3_COUNTER_MODE();
        if(TMR3_SYNC_COUNTER == _timer3->counter_sync){
            TMR3_SYNC_COUNTER_MODE();
        }
        else if(TMR3_ASYNC_COUNTER == _timer3->counter_sync){
            TMR3_ASYNC_COUNTER_MODE();
        }
        else {/* Nothing */}
        }
    else {/* Nothing */}
}

