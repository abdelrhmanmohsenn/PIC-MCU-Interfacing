/* 
 * File:   hal_ccp1.c
 * Author: mohsen
 *
 * Created on February 26, 2023, 6:53 PM
 */

#include "hal_ccp.h"

void (* l_CCP1_interruptHandler)(void)=NULL;
void (* l_CCP2_interruptHandler)(void)=NULL;

static Std_ReturnType interrupt_config(ccp_t *ccp_obj);
static Std_ReturnType timer_mode_select(ccp_t *ccp_obj);
#if CCP1_MODE_SELECT == CCP_CFG_COMPARE_MODE_SELECTED || CCP2_MODE_SELECT == CCP_CFG_COMPARE_MODE_SELECTED
static Std_ReturnType CCP_compare_mode_config(ccp_t *ccp_obj);
#endif
#if CCP1_MODE_SELECT == CCP_CFG_CAPTURE_MODE_SELECTED || CCP2_MODE_SELECT == CCP_CFG_CAPTURE_MODE_SELECTED
static Std_ReturnType CCP_Capture_Mode_Config(ccp_t *ccp_obj);
#endif

#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void CCP1_ISR(void){
    CCP1_FlagClear();
    if(l_CCP1_interruptHandler){ l_CCP1_interruptHandler(); }
    else{/* Nothing */}
}
#endif

#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void CCP2_ISR(void){
    CCP2_FlagClear();
    if(l_CCP2_interruptHandler){ l_CCP2_interruptHandler(); }
    else{/* Nothing */}
}
#endif

/**
 * 
 * @param ccp_obj
 * @return 
 */
Std_ReturnType ccp_init(ccp_t *ccp_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == ccp_obj){
        ret=E_NOT_OK;
    }
    else{
/******************************* CCP1_config *******************************************/
        if(CCP1_INST == ccp_obj->ccp_inst){
            pin_config_t ccp1_pin={.port=PORTC_INDEX,.pin=PIN2,.logic=PIN_LOW};
            ccp1_mode_config(CCP_MODULE_DISABLE);
#if CCP1_MODE_SELECT == CCP_CFG_PWM_MODE_SELECTED || CCP1_MODE_SELECT == CCP_CFG_PWM_MODE_SELECTED
            /**************************PWM_MODE*********************************/
            if(CCP_PWM_MODE_SELECTED == ccp_obj->ccp_mode){
                PR2=((_XTAL_FREQ/(ccp_obj->pwm_frequency*4*ccp_obj->timer2_postscaler_value
                        *ccp_obj->timer2_prescaler_value))-1);
                ccp1_pin.direction=PIN_DIRECTION_OUTPUT;
                gpio_pin_initialize(&ccp1_pin);               
            }
#endif
#if CCP1_MODE_SELECT == CCP_CFG_COMPARE_MODE_SELECTED || CCP2_MODE_SELECT == CCP_CFG_COMPARE_MODE_SELECTED
            /**************************COMPARE_MODE*****************************/
            else if(CCP_COMPARE_MODE_SELECTED == ccp_obj->ccp_mode){
                ccp1_pin.direction=PIN_DIRECTION_OUTPUT;
                CCP_Compare_Mode_Set_Value(ccp_obj,ccp_obj->compare_value);
                CCP_compare_mode_config(ccp_obj);
                timer_mode_select(ccp_obj);
            }
#endif
#if CCP1_MODE_SELECT == CCP_CFG_CAPTURE_MODE_SELECTED || CCP2_MODE_SELECT == CCP_CFG_CAPTURE_MODE_SELECTED
              /**************************CAPTURE_MODE*****************************/
            else if(CCP_CAPTURE_MODE_SELECTED == ccp_obj->ccp_mode){
                ccp1_pin.direction=PIN_DIRECTION_INPUT;
                gpio_pin_initialize(&ccp1_pin);
                CCP_Capture_Mode_Config(ccp_obj);
            }
            else {/* Nothing */}
#endif
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                interrupt_config(ccp_obj);
#endif
/******************************* CCP2_config *******************************************/
        }
        else if(CCP2_INST == ccp_obj->ccp_inst){
            pin_config_t ccp2_pin={.port=PORTC_INDEX,.pin=PIN1,.logic=PIN_LOW}; 
            ccp2_mode_config(CCP_MODULE_DISABLE);
#if CCP1_MODE_SELECT == CCP_CFG_PWM_MODE_SELECTED || CCP1_MODE_SELECT == CCP_CFG_PWM_MODE_SELECTED
            /**************************PWM_MODE*********************************/
            if(CCP_PWM_MODE_SELECTED == ccp_obj->ccp_mode){
                PR2=(_XTAL_FREQ/(ccp_obj->pwm_frequency*4*ccp_obj->timer2_postscaler_value
                        *ccp_obj->timer2_prescaler_value)-1);
                ccp2_pin.direction=PIN_DIRECTION_OUTPUT;    
            }
#endif
#if CCP1_MODE_SELECT == CCP_CFG_COMPARE_MODE_SELECTED || CCP2_MODE_SELECT == CCP_CFG_COMPARE_MODE_SELECTED
            /**************************COMPARE_MODE*****************************/
            else if(CCP_COMPARE_MODE_SELECTED == ccp_obj->ccp_mode){
                ccp2_pin.direction=PIN_DIRECTION_OUTPUT;
                gpio_pin_initialize(&ccp2_pin);
                CCP_Compare_Mode_Set_Value(ccp_obj,ccp_obj->compare_value);
                CCP_compare_mode_config(ccp_obj);
                timer_mode_select(ccp_obj); 
            }
#endif
#if CCP1_MODE_SELECT == CCP_CFG_CAPTURE_MODE_SELECTED || CCP2_MODE_SELECT == CCP_CFG_CAPTURE_MODE_SELECTED
            /**************************CAPTURE_MODE*****************************/
            else if(CCP_CAPTURE_MODE_SELECTED == ccp_obj->ccp_mode){
                ccp2_pin.direction=PIN_DIRECTION_INPUT;
                gpio_pin_initialize(&ccp2_pin);
                CCP_Capture_Mode_Config(ccp_obj);
            }
            else {/* Nothing */}
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                interrupt_config(ccp_obj);
#endif               
        }
        else {/* Nothing */}
    }
    
    return ret;
}

/**
 * 
 * @param ccp_obj
 * @return 
 */
Std_ReturnType ccp_DeInit(ccp_t *ccp_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == ccp_obj){
        ret=E_NOT_OK;
    }
    else{ 
       if(CCP1_INST == ccp_obj->ccp_inst){
        ccp1_mode_config(CCP_MODULE_DISABLE);
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        CCP1_InterruptDisable();
#endif
    }
        else if(CCP2_INST == ccp_obj->ccp_inst){
            ccp2_mode_config(CCP_MODULE_DISABLE);
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            CCP2_InterruptDisable();
#endif
        }
       else {/* Nothing */}
    }
    
    return ret;
}

/**
 * 
 * @param ccp_obj
 * @param dutyValue
 * @return 
 */
Std_ReturnType set_dutyCycle(ccp_t *ccp_obj, uint8 dutyValue){
    Std_ReturnType ret=E_OK;
    uint16 l_dutycycle=0;
    if(NULL == ccp_obj){
        ret=E_NOT_OK;
    }
    else{
        if(CCP1_INST == ccp_obj->ccp_inst){
            l_dutycycle=(PR2+1)*(dutyValue/100.0)*4;
            CCP1CONbits.DC1B=(uint8)(l_dutycycle&0x05);
            CCPR1L=(uint8)(l_dutycycle>>2);
        }
        else if(CCP2_INST == ccp_obj->ccp_inst){
           l_dutycycle=(PR2+1)*(dutyValue/100.0)*4;
            CCP2CONbits.DC2B=(uint8)(l_dutycycle&0x05);
            CCPR2L=(uint8)(l_dutycycle>>2); 
        }
       else {/* Nothing */}
        
    }
    
    return ret;
}

/**
 * 
 * @param ccp_obj
 * @return 
 */
Std_ReturnType pwm_start(ccp_t *ccp_obj){
    Std_ReturnType ret=E_OK;
    if(NULL == ccp_obj){
        ret=E_NOT_OK;
    }
    else{
        if(CCP1_INST == ccp_obj->ccp_inst){
            ccp1_mode_config(CCP_PWM_MODE);
        }
        else if(CCP2_INST == ccp_obj->ccp_inst){
            ccp2_mode_config(CCP_PWM_MODE);
        }
       else {/* Nothing */}
        
    }
    
    return ret;
}

/**
 * 
 * @param ccp_obj
 * @return 
 */
Std_ReturnType pwm_stop(ccp_t *ccp_obj){
    Std_ReturnType ret=E_OK;
    if(NULL == ccp_obj){
        ret=E_NOT_OK;
    }
    else{
        if(CCP1_INST == ccp_obj->ccp_inst){
            ccp1_mode_config(CCP_MODULE_DISABLE);
        }
        else if(CCP2_INST == ccp_obj->ccp_inst){
            ccp2_mode_config(CCP_MODULE_DISABLE);
        }
       else {/* Nothing */}
        
    }
    
    return ret;
}

/**
 * 
 * @param ccp_obj
 * @return 
 */
static Std_ReturnType interrupt_config(ccp_t *ccp_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == ccp_obj){
        ret=E_NOT_OK;
    }
    else{
        if(CCP1_INST == ccp_obj->ccp_inst){

            CCP1_InterruptEnable();
            l_CCP1_interruptHandler=ccp_obj->CCP1_interruptHandler;
#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE   
            INTERRUPT_PriortyLevelEnable();
            if(INTERRUPT_HIGH_PRIORTY == ccp_obj->priority){
                INTERRUPT_GlobalInterruptHighEnable();
            }
            else if(INTERRUPT_LOW_PRIORTY == ccp_obj->priority){
                INTERRUPT_GlobalInterruptLowEnable();
            }
            else{/* Nothing */}
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif 
        }
        else if(CCP2_INST == ccp_obj->ccp_inst){
            CCP2_InterruptEnable();
            l_CCP2_interruptHandler=ccp_obj->CCP1_interruptHandler;
#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE   
            INTERRUPT_PriortyLevelEnable();
            if(INTERRUPT_HIGH_PRIORTY == ccp_obj->priority){
                INTERRUPT_GlobalInterruptHighEnable();
            }
            else if(INTERRUPT_LOW_PRIORTY == ccp_obj->priority){
                INTERRUPT_GlobalInterruptLowEnable();
            }
            else{/* Nothing */}
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif         
        } 
       
    }
    
    return ret;
}

/**
 * 
 * @param _compare_status
 * @return 
 */
Std_ReturnType CCP_IsCompareComplete(ccp_t *ccp_obj, uint8 *_compare_status){
    Std_ReturnType ret=E_OK;
    if(NULL == _compare_status || NULL == ccp_obj){
        ret=E_NOT_OK;
    }
    else{
        if(CCP1_INST == ccp_obj->ccp_inst){
            if(CCP_COMPARE_READY == PIR1bits.CCP1IF){
            *_compare_status=CCP_COMPARE_READY;
            }
            else if(CCP_COMPARE_NOT_READY == PIR1bits.CCP1IF){
                *_compare_status=CCP_COMPARE_NOT_READY;
            }
            else {/* Nothing */}
        }
        else if(CCP2_INST == ccp_obj->ccp_inst){
            if(CCP_COMPARE_READY == PIR2bits.CCP2IF){
            *_compare_status=CCP_COMPARE_READY;
            }
            else if(CCP_COMPARE_NOT_READY == PIR2bits.CCP2IF){
                *_compare_status=CCP_COMPARE_NOT_READY;
            }
            else {/* Nothing */}
        }
       else {/* Nothing */}
        
    }
    
    return ret;
}

/**
 * 
 * @param _ccp_obj
 * @param compare_value
 * @return 
 */
Std_ReturnType CCP_Compare_Mode_Set_Value(ccp_t *ccp_obj, uint16 compare_value){
    Std_ReturnType ret=E_OK;
    if(NULL == ccp_obj){
        ret=E_NOT_OK;
    }
    else{
        ccp_reg_t ccpr;
        if(CCP1_INST == ccp_obj->ccp_inst){
            ccpr.ccp_16Bit=compare_value;
            CCPR1L=ccpr.ccpL;
            CCPR1H=ccpr.ccpH;
        }
        else if(CCP2_INST == ccp_obj->ccp_inst){
            ccpr.ccp_16Bit=compare_value;
            CCPR2L=ccpr.ccpL;
            CCPR2H=ccpr.ccpH;
        }
       else {/* Nothing */}
        
    }
    
    return ret;
}

/**
 * 
 * @param _capture_status
 * @return 
 */
Std_ReturnType CCP_IsCapturedDataReady(ccp_t *ccp_obj, uint8 *_capture_status){
    Std_ReturnType ret=E_OK;
    if(NULL == _capture_status || NULL == ccp_obj){
        ret=E_NOT_OK;
    }
    else{
        if(CCP1_INST == ccp_obj->ccp_inst){
            if(CCP_CAPTURE_READY == PIR1bits.CCP1IF){
            *_capture_status=CCP_CAPTURE_READY;
            }
            else if(CCP_CAPTURE_NOT_READY == PIR1bits.CCP1IF){
                *_capture_status=CCP_CAPTURE_NOT_READY;
            }
            else {/* Nothing */}
        }
        else if(CCP2_INST == ccp_obj->ccp_inst){
            if(CCP_CAPTURE_READY == PIR2bits.CCP2IF){
            *_capture_status=CCP_CAPTURE_READY;
            }
            else if(CCP_CAPTURE_NOT_READY == PIR2bits.CCP2IF){
                *_capture_status=CCP_CAPTURE_NOT_READY;
            }
            else {/* Nothing */}
        }
       else {/* Nothing */}
        
    }
    
    return ret;
}

/**
 * 
 * @param capture_value
 * @return 
 */
Std_ReturnType CCP_Capture_Mode_Read_Value(ccp_t *ccp_obj, uint16 *capture_value){
    Std_ReturnType ret=E_OK;
    if(NULL == ccp_obj){
        ret=E_NOT_OK;
    }
    else{
        ccp_reg_t ccpr;
        if(CCP1_INST == ccp_obj->ccp_inst){
            ccpr.ccpL=CCPR1L;
            ccpr.ccpH=CCPR1H;
            *capture_value=ccpr.ccp_16Bit;
        }
        else if(CCP2_INST == ccp_obj->ccp_inst){
            ccpr.ccpL=CCPR2L;
            ccpr.ccpH=CCPR2H;
            *capture_value=ccpr.ccp_16Bit;
        }
       else {/* Nothing */}
        
    }
    
    return ret;
}

/**
 * 
 * @param ccp_obj
 * @return 
 */
static Std_ReturnType CCP_compare_mode_config(ccp_t *ccp_obj){
    Std_ReturnType ret=E_OK;
    if(NULL == ccp_obj){
        ret=E_NOT_OK;
    }
    else{
        if(CCP1_INST == ccp_obj->ccp_inst){
            switch(ccp_obj->ccp_mode_variant){
            case CCP_COMPARE_MODE_SET_PIN_LOW      : ccp1_mode_config(CCP_COMPARE_MODE_SET_PIN_LOW); break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH     : ccp1_mode_config(CCP_COMPARE_MODE_SET_PIN_HIGH); break;
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH  : ccp1_mode_config(CCP_COMPARE_MODE_TOGGLE_ON_MATCH); break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT : ccp1_mode_config(CCP_COMPARE_MODE_GEN_SW_INTERRUPT); break;
            case CCP_COMPARE_MODE_GEN_EVENT        : ccp1_mode_config(CCP_COMPARE_MODE_GEN_EVENT); break;
            }
        }
        else if(CCP2_INST == ccp_obj->ccp_inst){
            switch(ccp_obj->ccp_mode_variant){
            case CCP_COMPARE_MODE_SET_PIN_LOW      : ccp2_mode_config(CCP_COMPARE_MODE_SET_PIN_LOW); break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH     : ccp2_mode_config(CCP_COMPARE_MODE_SET_PIN_HIGH); break;
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH  : ccp2_mode_config(CCP_COMPARE_MODE_TOGGLE_ON_MATCH); break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT : ccp2_mode_config(CCP_COMPARE_MODE_GEN_SW_INTERRUPT); break;
            case CCP_COMPARE_MODE_GEN_EVENT        : ccp2_mode_config(CCP_COMPARE_MODE_GEN_EVENT); break;
            }
        }
       else {/* Nothing */}
        
    }
    
    return ret;
}

static Std_ReturnType timer_mode_select(ccp_t *ccp_obj){
    Std_ReturnType ret=E_OK;
    if(NULL == ccp_obj){
        ret=E_NOT_OK;
    }
    else{
        if(ccp1_ccp2_timer3 == ccp_obj->ccp_timer){
            T3CONbits.T3CCP1=0;
            T3CONbits.T3CCP2=1;
        }
        else if(ccp1_timer1_ccp2_timer3 == ccp_obj->ccp_timer){
            T3CONbits.T3CCP1=1;
            T3CONbits.T3CCP2=0;
        }
        else if(ccp1_ccp2_timer1 == ccp_obj->ccp_timer){
            T3CONbits.T3CCP1=0;
            T3CONbits.T3CCP2=0;
        }
        else {/* Nothing */} 
    }
    
    return ret;
}

static Std_ReturnType CCP_Capture_Mode_Config(ccp_t *ccp_obj){
    Std_ReturnType ret = E_OK;
    
    if(CCP1_INST == ccp_obj->ccp_inst){
        /* CCP1 Module Capture variants Mode Initialization */
        switch(ccp_obj->ccp_mode_variant){
            case CCP_CAPTURE_MODE_1_FALLING_EDGE : ccp1_mode_config(CCP_CAPTURE_MODE_1_FALLING_EDGE); break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE  : ccp1_mode_config(CCP_CAPTURE_MODE_1_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE  : ccp1_mode_config(CCP_CAPTURE_MODE_4_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE : ccp1_mode_config(CCP_CAPTURE_MODE_16_RISING_EDGE); break;
            default : ret = E_NOT_OK; /* Not supported variant */
        }
    }
    else if(CCP2_INST == ccp_obj->ccp_inst){
        /* CCP2 Module Capture variants Mode Initialization */
        switch(ccp_obj->ccp_mode_variant){
            case CCP_CAPTURE_MODE_1_FALLING_EDGE : ccp2_mode_config(CCP_CAPTURE_MODE_1_FALLING_EDGE); break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE  : ccp2_mode_config(CCP_CAPTURE_MODE_1_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE  : ccp2_mode_config(CCP_CAPTURE_MODE_4_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE : ccp2_mode_config(CCP_CAPTURE_MODE_16_RISING_EDGE); break;
            default : ret = E_NOT_OK; /* Not supported variant */
        }
    }
    else{ /* Nothing */ }
    
    return ret;
}