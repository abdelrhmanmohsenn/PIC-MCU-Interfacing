/* 
 * File:   hal_timer0.c
 * Author: mohsen
 *
 * Created on February 17, 2023, 8:36 PM
 */

#include "hal_timer0.h"

static void (* l_TMR0_interruptHandler)(void)=NULL;
static uint16 l_timer0_preload=0;

static inline void edge_select(timer0_t *_timer0);
static inline void prescaler_config(timer0_t *_timer0);
static inline void timer0_register_mode_select(timer0_t *_timer0);
static inline void timer0_mode_select(timer0_t *_timer0);

void TMR0_ISR(void){
    TMR0_FlagClear();
    TMR0H=(uint8)(l_timer0_preload >> 8);
    TMR0L=(uint8)(l_timer0_preload);
    if(l_TMR0_interruptHandler){ l_TMR0_interruptHandler(); }
    else{/* Nothing */}
}

/**
 * 
 * @param _timer0
 * @return 
 */
Std_ReturnType timer0_init(timer0_t *_timer0){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _timer0){
        ret=E_NOT_OK;
    }
    else{
        TMR0_DISABLE();
        TMR0_FlagClear();
        edge_select(_timer0);
        prescaler_config(_timer0);
        timer0_register_mode_select(_timer0);
        timer0_mode_select(_timer0);
        TMR0H=(uint8)(_timer0->preload_value >> 8);
         TMR0L=(uint8)(_timer0->preload_value);
        l_timer0_preload=_timer0->preload_value;
        T0CONbits.T0PS=_timer0->prescaler;
#if TMR0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TMR0_InterruptEnable();
        l_TMR0_interruptHandler=_timer0->interruptHandler;
#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE   
        INTERRUPT_PriortyLevelEnable();
        if(INTERRUPT_HIGH_PRIORTY == _timer0->priority){
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else if(INTERRUPT_LOW_PRIORTY == _timer0->priority){
            INTERRUPT_GlobalInterruptLowEnable();
        }
        else{/* Nothing */}
        
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        TMR0_ENABLE();
    }
    
    return ret;
}

/**
 * 
 * @param _timer0
 * @return 
 */
Std_ReturnType timer0_Deinit(timer0_t *_timer0){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _timer0){
        ret=E_NOT_OK;
    }
    else{
#if TMR0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TMR0_InterruptDisable();
#endif
        TMR0_DISABLE();
    }
    
    return ret;
}

/**
 * 
 * @param _timer0
 * @param value
 * @return 
 */
Std_ReturnType timer0_write_value(timer0_t *_timer0, uint16 value){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _timer0){
        ret=E_NOT_OK;
    }
    else{
        TMR0H=(uint8)(value >> 8);
        TMR0L=(uint8)(value);
    }
    
    return ret;
}

/**
 * 
 * @param _timer0
 * @param value
 * @return 
 */
Std_ReturnType timer0_read_value(timer0_t *_timer0, uint16 *value){
    Std_ReturnType ret=E_NOT_OK;
    uint8 l_TMR0L = 0, l_TMR0H = 0;
    if(NULL == _timer0 || NULL == value){
        ret=E_NOT_OK;
    }
    else{
        l_TMR0L = TMR0L;
        l_TMR0H = TMR0H;
        *value = (uint16)((l_TMR0H << 8) + l_TMR0L);
    }
    
    return ret;
}

/**
 * 
 * @param _timer0
 */
static inline void prescaler_config(timer0_t *_timer0){
    if(TMR0_PRESCALE_ENABLE == _timer0->prescaler_enable){
        TMR0_PRESCELER_ENABLE();
    }
    else if(TMR0_PRESCELE_DISABLE == _timer0->prescaler_enable){
        TMR0_PRESCELER_DISABLE();
    }
    else {/* Nothing */} 
}

/**
 * 
 * @param _timer0
 */
static inline void edge_select(timer0_t *_timer0){
    if(TMR0_EDGE_HIGH == _timer0->edge_source){
        TMR0_SOURCE_EDGE_HIGH();
    }
    else if(TMR0_EDGE_LOW == _timer0->edge_source){
        TMR0_SOURCE_EDGE_LOW();
    }
    else {/* Nothing */}
}

/**
 * 
 * @param _timer0
 */
static inline void timer0_register_mode_select(timer0_t *_timer0){
    if(TMR0_8_BIT_MODE_ENABLE == _timer0->bits_mode){
        TMR0_8_BIT_MODE();
    }
    else if(TMR0_16_BIT_MODE_ENABLE == _timer0->bits_mode){
        TMR0_16_BIT_MODE();
    }
    else {/* Nothing */}
}

/**
 * 
 * @param _timer0
 */
static inline void timer0_mode_select(timer0_t *_timer0){
    if(TMR0_TIMER_MODE_ENABLE == _timer0->timer_mode){
        TMR0_TIMER_MODE();
    }
    else if(TMR0_COUNTER_MODE_ENABLE == _timer0->timer_mode){
        TMR0_COUNTER_MODE();
    }
    else {/* Nothing */}
}