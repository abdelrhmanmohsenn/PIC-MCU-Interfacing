/* 
 * File:   mcal_external_interrupt.h
 * Author: mohsen
 *
 * Created on February 11, 2023, 4:29 PM
 */

#include "mcal_external_interrupt.h"

static void (* INT0_InterruptHandler)(void)=NULL;
static void (* INT1_InterruptHandler)(void)=NULL;
static void (* INT2_InterruptHandler)(void)=NULL;

static void (* RB4_InterruptHandlerHigh)(void)=NULL;
static void (* RB4_InterruptHandlerLow)(void)=NULL;
static void (* RB5_InterruptHandlerHigh)(void)=NULL;
static void (* RB5_InterruptHandlerLow)(void)=NULL;
static void (* RB6_InterruptHandlerHigh)(void)=NULL;
static void (* RB6_InterruptHandlerLow)(void)=NULL;
static void (* RB7_InterruptHandlerHigh)(void)=NULL;
static void (* RB7_InterruptHandlerLow)(void)=NULL;

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *_int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *_int_obj);
static Std_ReturnType Interrupt_INTx_Edge(const interrupt_INTx_t *_int_obj);
static Std_ReturnType Interrupt_INTx_Priorty(const interrupt_INTx_t *_int_obj);
static Std_ReturnType Interrupt_INTx_ClearFlag(const interrupt_INTx_t *_int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *_int_obj);
static Std_ReturnType Interrupt_INTx_SetInterruptHandeler(const interrupt_INTx_t *_int_obj);

static Std_ReturnType Interrupt_RBx_SetInterruptHandeler(const interrupt_RBx_t *_int_obj);

void INT0_ISR(void){
    EXT_INT0_FlagClear();
    if(INT0_InterruptHandler){INT0_InterruptHandler(); };
}

void INT1_ISR(void){
    EXT_INT1_FlagClear();
    if(INT1_InterruptHandler){INT1_InterruptHandler(); };
}

void INT2_ISR(void){
    EXT_INT2_FlagClear();
    if(INT2_InterruptHandler){INT2_InterruptHandler(); };
}

void RB4_ISR(uint8 src){
    EXT_INT0_FlagClear();
    if(1 == src){
       if(RB4_InterruptHandlerHigh){RB4_InterruptHandlerHigh(); }; 
    }
    else if(0 == src){
       if(RB4_InterruptHandlerLow){RB4_InterruptHandlerLow(); }; 
    }
    
}

void RB5_ISR(uint8 src){
    EXT_RBx_FlagClear();
    if(1 == src){
       if(RB5_InterruptHandlerHigh){RB5_InterruptHandlerHigh(); }; 
    }
    else if(0 == src){
       if(RB5_InterruptHandlerLow){RB5_InterruptHandlerLow(); }; 
    }
    
}

void RB6_ISR(uint8 src){
    EXT_RBx_FlagClear();
    if(1 == src){
       if(RB6_InterruptHandlerHigh){RB6_InterruptHandlerHigh(); }; 
    }
    else if(0 == src){
       if(RB6_InterruptHandlerLow){RB6_InterruptHandlerLow(); }; 
    }
    
}

void RB7_ISR(uint8 src){
    EXT_RBx_FlagClear();
    if(1 == src){
       if(RB7_InterruptHandlerHigh){RB7_InterruptHandlerHigh(); }; 
    }
    else if(0 == src){
       if(RB7_InterruptHandlerLow){RB7_InterruptHandlerLow(); }; 
    }
    
}

/**
 * 
 * @param _int_obj
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *_int_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == _int_obj){
        ret=E_NOT_OK;
    }
    else{
        Interrupt_INTx_Disable(_int_obj);
        Interrupt_INTx_ClearFlag(_int_obj);
        Interrupt_INTx_Edge(_int_obj);
        Interrupt_INTx_Pin_Init(_int_obj);
#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        Interrupt_INTx_Priorty(_int_obj);
#endif
        Interrupt_INTx_SetInterruptHandeler(_int_obj);
        Interrupt_INTx_Enable(_int_obj);
    }
    
    return ret;
}

/**
 * 
 * @param _int_obj
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *_int_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == _int_obj){
        ret=E_NOT_OK;
    }
    else{
        Interrupt_INTx_Disable(_int_obj);
    }
    
    return ret;
}

/**
 * 
 * @param _int_obj
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *_int_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == _int_obj){
        ret=E_NOT_OK;
    }
    else{
        switch(_int_obj->src){
            case INTERRUPT_INT0: 
#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriortyLevelEnable();
                INTERRUPT_GlobalInterruptHighEnable();
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT0_InterruptEnable();
                break;
            case INTERRUPT_INT1: 
#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriortyLevelEnable();
                if(INTERRUPT_HIGH_PRIORTY == _int_obj->priorty){
                    INTERRUPT_GlobalInterruptHighEnable();
                }
                else if(INTERRUPT_LOW_PRIORTY == _int_obj->priorty){
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else{/* Do Nothing */}
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT1_InterruptEnable();
                break;
            case INTERRUPT_INT2: 
#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriortyLevelEnable();
                if(INTERRUPT_HIGH_PRIORTY == _int_obj->priorty){
                    INTERRUPT_GlobalInterruptHighEnable();
                }
                else if(INTERRUPT_LOW_PRIORTY == _int_obj->priorty){
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else{/* Do Nothing */}
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT2_InterruptEnable();
                break;
            default  :  ret=E_NOT_OK;
        }
    }
    
    return ret;
}

/**
 * 
 * @param _int_obj
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *_int_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == _int_obj){
        ret=E_NOT_OK;
    }
    else{
        switch(_int_obj->src){
            case INTERRUPT_INT0:
                EXT_INT0_InterruptDisable();
                break;
            case INTERRUPT_INT1:
                EXT_INT1_InterruptDisable();
                break;
            case INTERRUPT_INT2:
                EXT_INT2_InterruptDisable();
                break;
            default  :  ret=E_NOT_OK;
        }
    }
    
    return ret;
}

/**
 * 
 * @param _int_obj
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
static Std_ReturnType Interrupt_INTx_Edge(const interrupt_INTx_t *_int_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == _int_obj){
        ret=E_NOT_OK;
    }
    else{
        switch(_int_obj->src){
            case INTERRUPT_INT0: 
                if(INTERRUPT_RISING_EGDE == _int_obj->edge){
                    EXT_INT0_RisingEdge();
                }
                else if(INTERRUPT_FALLING__EGDE == _int_obj->edge){
                    EXT_INT0_FallingEdge();
                }
                else{/* Do Nothing */}
                break;
            case INTERRUPT_INT1: 
                if(INTERRUPT_RISING_EGDE == _int_obj->edge){
                    EXT_INT1_RisingEdge();
                }
                else if(INTERRUPT_FALLING__EGDE == _int_obj->edge){
                    EXT_INT1_FallingEdge();
                }
                else{/* Do Nothing */}
                break;
            case INTERRUPT_INT2: 
                if(INTERRUPT_RISING_EGDE == _int_obj->edge){
                    EXT_INT2_RisingEdge();
                }
                else if(INTERRUPT_FALLING__EGDE == _int_obj->edge){
                    EXT_INT2_FallingEdge();
                }
                else{/* Do Nothing */}
                break;
            default  :  ret=E_NOT_OK;
        }
    }
    
    return ret;
}

/**
 * 
 * @param _int_obj
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTx_Priorty(const interrupt_INTx_t *_int_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == _int_obj){
        ret=E_NOT_OK;
    }
    else{
        switch(_int_obj->src){
            case INTERRUPT_INT1: 
                 if(INTERRUPT_HIGH_PRIORTY == _int_obj->priorty){
                    EXT_INT1_PriorityHigh();
                }
                else if(INTERRUPT_LOW_PRIORTY == _int_obj->priorty){
                    EXT_INT1_PriorityLow();
                }
                else{/* Do Nothing */}
                break;
            case INTERRUPT_INT2: 
                 if(INTERRUPT_HIGH_PRIORTY == _int_obj->priorty){
                    EXT_INT2_PriorityHigh();
                }
                else if(INTERRUPT_LOW_PRIORTY == _int_obj->priorty){
                    EXT_INT2_PriorityLow();
                }
                else{/* Do Nothing */}
                break;
            default  :  ret=E_NOT_OK;
        }
    }
    
    return ret;
}
#endif

/**
 * 
 * @param _int_obj
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
static Std_ReturnType Interrupt_INTx_ClearFlag(const interrupt_INTx_t *_int_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == _int_obj){
        ret=E_NOT_OK;
    }
    else{
        switch(_int_obj->src){
            case INTERRUPT_INT0: 
                EXT_INT0_FlagClear();
                break;
            case INTERRUPT_INT1: 
                EXT_INT1_FlagClear();
                break;
            case INTERRUPT_INT2: 
                EXT_INT2_FlagClear();
                break;
            default  :  ret=E_NOT_OK;
        }
    }
    
    return ret;
}

/**
 * 
 * @param _int_obj
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *_int_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == _int_obj){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_initialize(&(_int_obj->pin));
    }
    
    return ret;
}

/**
 * 
 * @param _int_obj
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
static Std_ReturnType Interrupt_INTx_SetInterruptHandeler(const interrupt_INTx_t *_int_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == _int_obj){
        ret=E_NOT_OK;
    }
    else{
        switch(_int_obj->src){
            case INTERRUPT_INT0: 
                INT0_InterruptHandler = (_int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_INT1: 
                INT1_InterruptHandler = (_int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_INT2: 
                INT2_InterruptHandler = (_int_obj->EXT_InterruptHandler);
                break;
            default  :  ret=E_NOT_OK;
        }
    }  
    
    return ret;
}

/**
 * 
 * @param _int_obj
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *_int_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == _int_obj){
        ret=E_NOT_OK;
    }
    else{
        EXT_RBx_InterruptDisable();
        EXT_RBx_FlagClear();
        
#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriortyLevelEnable();
        if(INTERRUPT_HIGH_PRIORTY == _int_obj->priorty){
            INTERRUPT_GlobalInterruptHighEnable();
            EXT_RBx_PriorityHigh();
        }
        else if(INTERRUPT_LOW_PRIORTY == _int_obj->priorty){
            INTERRUPT_GlobalInterruptLowEnable();
            EXT_RBx_PriorityLow();
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        gpio_pin_initialize(&(_int_obj->mcu_pin));
        Interrupt_RBx_SetInterruptHandeler(_int_obj);
        EXT_RBx_InterruptEnable();
    }  
    
    return ret;
}

/**
 * 
 * @param _int_obj
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *_int_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == _int_obj){
        ret=E_NOT_OK;
    }
    else{
        EXT_RBx_InterruptDisable();
    }  
    
    return ret;
}

/**
 * 
 * @param _int_obj
 * @return Status Of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function had an issue in performing this action
 */
static Std_ReturnType Interrupt_RBx_SetInterruptHandeler(const interrupt_RBx_t *_int_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == _int_obj){
        ret=E_NOT_OK;
    }
    else{
        switch(_int_obj->mcu_pin.pin){
            case PIN4 : 
                RB4_InterruptHandlerHigh=_int_obj->EXT_InterruptHandlerHigh;
                RB4_InterruptHandlerLow=_int_obj->EXT_InterruptHandlerLow;
                break;
            case PIN5 : 
                RB5_InterruptHandlerHigh=_int_obj->EXT_InterruptHandlerHigh;
                RB5_InterruptHandlerLow=_int_obj->EXT_InterruptHandlerLow;
                break;
            case PIN6 : 
                RB6_InterruptHandlerHigh=_int_obj->EXT_InterruptHandlerHigh;
                RB6_InterruptHandlerLow=_int_obj->EXT_InterruptHandlerLow;
                break;
            case PIN7 : 
                RB7_InterruptHandlerHigh=_int_obj->EXT_InterruptHandlerHigh;
                RB7_InterruptHandlerLow=_int_obj->EXT_InterruptHandlerLow;
                break;
            default : ret=E_NOT_OK;
        }
    }  
    
    return ret;
}