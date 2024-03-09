/* 
 * File:   hal_timer1.c
 * Author: mohsen
 *
 * Created on February 18, 2023, 11:05 PM
 */

#include "hal_timer1.h"

static uint16 l_preload_value=0;
void (* l_TMR1_interruptHandler)(void)=NULL;

static inline void timer1_prescaler_config(timer1_t *_timer1);
static inline void timer1_register_mode_select(timer1_t *_timer1);
static inline void timer1_mode_select(timer1_t *_timer1);
static inline void timer1_osc_config(timer1_t *_timer1);

void TMR1_ISR(void){
    TMR1_FlagClear();
    TMR1H=(uint8)(l_preload_value >> 8);
    TMR1L=(uint8)(l_preload_value);
    if(l_TMR1_interruptHandler){ l_TMR1_interruptHandler(); }
    else{/* Nothing */}
}

/**
 * 
 * @param _timer1
 * @return 
 */
Std_ReturnType timer1_init(const timer1_t *_timer1){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _timer1){
        ret=E_NOT_OK;
    }
    else{
        TMR1_DISABLE();
        TMR1_FlagClear();
        timer1_prescaler_config(_timer1);
        timer1_mode_select(_timer1);
        timer1_register_mode_select(_timer1); 
        timer1_osc_config(_timer1);
        timer1_write_value(_timer1,_timer1->preload_value);
        l_preload_value=_timer1->preload_value;
#if TMR1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TMR1_InterruptEnable();
        l_TMR1_interruptHandler=_timer1->interruptHandler;
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
        TMR1_ENABLE();
    }
    
    return ret;
}

/**
 * 
 * @param _timer1
 * @return 
 */
Std_ReturnType timer1_Deinit(const timer1_t *_timer1){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _timer1){
        ret=E_NOT_OK;
    }
    else{
        TMR1_DISABLE();
#if TMR1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TMR1_InterruptDisable();
#endif
    }
    
    return ret;
}

/**
 * 
 * @param _timer1
 * @param value
 * @return 
 */
Std_ReturnType timer1_write_value(const timer1_t *_timer1, uint16 value){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _timer1){
        ret=E_NOT_OK;
    }
    else{
        TMR1H=(uint8)(value >> 8);
        TMR1L=(uint8)(value);
    }
    
    return ret;
}

/**
 * 
 * @param _timer1
 * @param value
 * @return 
 */
Std_ReturnType timer1_read_value(const timer1_t *_timer1, uint16 *value){
    Std_ReturnType ret=E_NOT_OK;
    uint8 l_TMR1L = 0, l_TMR1H = 0; 
    if(NULL == _timer1 || NULL == value){
        ret=E_NOT_OK;
    }
    else{
        l_TMR1L = TMR1L;
        l_TMR1H = TMR1H;
        *value = (uint16)((l_TMR1H << 8) + l_TMR1L);
    }
    
    return ret;
}

/**
 * 
 * @param _timer1
 */
static inline void timer1_prescaler_config(timer1_t *_timer1){
    TMR1_PRESCELER_CONFG(_timer1->prescaler);
}

/**
 * 
 * @param _timer1
 */
static inline void timer1_register_mode_select(timer1_t *_timer1){
    TMR1_RIGESTER_MODE(_timer1->register_mode);
}

/**
 * 
 * @param _timer1
 */
static inline void timer1_mode_select(timer1_t *_timer1){
    if(TMR1_TIMER_MODE_ENABLE == _timer1->working_mode){
        TMR1_TIMER_MODE();
    }
    else if(TMR1_COUNTER_MODE_ENABLE == _timer1->working_mode){
        pin_config_t pin_t1={.port=PORTC_INDEX,.pin=PIN0,.direction=PIN_DIRECTION_INPUT,.logic=PIN_LOW};
        gpio_pin_initialize(&pin_t1);
        TMR1_COUNTER_MODE();
        if(TMR1_SYNC_COUNTER == _timer1->counter_sync){
            TMR1_SYNC_COUNTER_MODE();
        }
        else if(TMR1_ASYNC_COUNTER == _timer1->counter_sync){
            TMR1_ASYNC_COUNTER_MODE();
        }
        else {/* Nothing */}
        }
    else {/* Nothing */}
}

/**
 * 
 * @param _timer1
 */
static inline void timer1_osc_config(timer1_t *_timer1){
    if(TMR1_OSC_ENABLE_CONFG == _timer1->timer1_osc){
        TMR1_OSC_ENABLE();
    }
    else if(TMR1_OSC_DISABLE_CONFG == _timer1->timer1_osc){
        TMR1_OSC_DISABLE();
    }
    else {/* Nothing */}
}