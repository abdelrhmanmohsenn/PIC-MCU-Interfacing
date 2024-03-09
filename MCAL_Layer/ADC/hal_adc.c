/* 
 * File:   hal_adc.c
 * Author: mohsen
 *
 * Created on February 15, 2023, 12:07 AM
 */

#include "hal_adc.h"

static void (* adc_interrupthandeler)(void)=NULL;

static inline void adc_input_channel_port_configure(adc_channel_select_t channel);

void ADC_ISR(void){
    ADC_FlagClear();
    if(adc_interrupthandeler) { adc_interrupthandeler(); }
    else{/* Nothing */}
}

/**
 * @Summary Initializes the ADC
 * @Description This routine initializes the ADC.
 *              This routine must be called before any other ADC routine is called.
 *              This routine should only be called once during system initialization.
 * @Preconditions None
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_Init(const adc_conf_t *_adc){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _adc){
        ret=E_NOT_OK;
    }
    else{
        /*Disable pin output driver & Configure pin as analog*/
        adc_input_channel_port_configure(_adc->channel);
        /*Select ADC conversion clock*/
        ADCON2bits.ADCS=_adc->adc_clock;
        /*Configure voltage reference*/
        if(EXTERNAL_VOLTAGE_REFERENCE == _adc->voltage_refernce){
            ADC_ENABLE_VOLTAGE_REFERENCE();
        }
        else if(INTERNAL_VOLTAGE_REFERENCE == _adc->voltage_refernce){
            ADC_DISABLE_VOLTAGE_REFERENCE();
        }
        /*Select ADC input channel*/
        ADC_SelectChannel(_adc,_adc->channel);
        /*Select result format*/
        if(RIGHT_FORMAT == _adc->result_format){
            ADC_CONVERSION_FORMAT_RIGHT();
        }
        else if(LEFT_FORMAT == _adc->result_format){
            ADC_CONVERSION_FORMAT_LEFT();
        }
        /*Select acquisition delay*/
        ADCON2bits.ACQT=_adc->adc_aquaisition;
        /*enable interrupt feature*/
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriortyLevelEnable();
        if(INTERRUPT_HIGH_PRIORTY == _adc->priority){
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else if(INTERRUPT_LOW_PRIORTY == _adc->priority){
            INTERRUPT_GlobalInterruptLowEnable();
        }
        else{/* Nothing */}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        ADC_FlagClear();
        ADC_InterruptEnable();
        adc_interrupthandeler=_adc->adc_interrupthandler;
#endif        
        /*Turn on ADC module*/
        ADC_CONVERTER_ENABLE();
    }
    
    return ret;
}

/**
 * @Summary De-Initializes the ADC
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_DeInit(const adc_conf_t *_adc){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _adc){
        ret=E_NOT_OK;
    }
    else{
        ADC_CONVERTER_DISABLE();
    }
    
    return ret;
}

/**
 * @Summary Allows selection of a channel for conversion
 * @Description This routine is used to select desired channel for conversion.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param channel Defines the channel available for conversion.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_SelectChannel(const adc_conf_t *_adc, adc_channel_select_t channel){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _adc){
        ret=E_NOT_OK;
    }
    else{
        ADCON0bits.CHS=channel;
    }
    
    return ret;
}

/**
 * @Summary Starts conversion
 * @Description This routine is used to start conversion of desired channel.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_StartConversion(const adc_conf_t *_adc){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _adc){
        ret=E_NOT_OK;
    }
    else{
        ADC_CONVERSION_START();
    }
    
    return ret;
}

/**
 * @Summary Returns true when the conversion is completed otherwise false.
 * @Description This routine is used to determine if conversion is completed.
 *              When conversion is complete routine returns true. It returns false otherwise.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 *                ADC_StartConversion() should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param conversion_status The conversion status
 *          true  - If conversion is complete
 *          false - If conversion is not completed
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_IsConversionDone(const adc_conf_t *_adc, uint8 *conversion_status){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _adc){
        ret=E_NOT_OK;
    }
    else{
        *conversion_status=(uint8)(!ADC_CONVERSION_DONE());
    }
    
    return ret;
}

/**
 * @Summary Returns the ADC conversion value.
 * @Description This routine is used to get the analog to digital converted value.
 *              This routine gets converted values from the channel specified.
 * @Preconditions   This routine returns the conversion value only after the conversion is complete.
 *                  Completion status can be checked using ADC_IsConversionDone() routine.
 * @param _adc Pointer to the ADC configurations
 * @param conversion_result The converted value.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_GetConversionResult(const adc_conf_t *_adc, adc_result_t *conversion_result){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _adc){
        ret=E_NOT_OK;
    }
    else{
        if(RIGHT_FORMAT == _adc->result_format){
            *conversion_result=(adc_result_t)((ADRESH << 8) + ADRESL);
        }
        else if(LEFT_FORMAT == _adc->result_format){
            *conversion_result=(adc_result_t)((ADRESH + ADRESL) >> 6);
        }
    }
    
    return ret;
}

/**
 * @Summary Returns the ADC conversion value, also allows selection of a channel for conversion.
 * @Description This routine is used to select desired channel for conversion.
 *              This routine is get the analog to digital converted value.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param channel Defines the channel available for conversion.
 * @param conversion_result The converted value.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_GetConversion_Blocking(const adc_conf_t *_adc, adc_channel_select_t channel, 
                                 adc_result_t *conversion_result){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _adc){
        ret=E_NOT_OK;
    }
    else{
        ret = ADC_SelectChannel(_adc,channel);
        ret = ADC_StartConversion(_adc);
        while(ADC_CONVERSION_DONE());
        ret = ADC_GetConversionResult(_adc,conversion_result);
    }
    
    return ret;
}

/**
 * 
 * @param _adc
 * @param channel
 * @return 
 */
Std_ReturnType ADC_StartConversion_Interrupt(const adc_conf_t *_adc, adc_channel_select_t channel){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _adc){
        ret=E_NOT_OK;
    }
    else{
        ADC_SelectChannel(_adc,channel);
        ADC_StartConversion(_adc);
    }
    
    return ret;
}
 
static inline void adc_input_channel_port_configure(adc_channel_select_t channel){
    switch(channel){
        case ADC_CHANNEL_AN0 : TRISAbits.RA0=1; ANSELbits.ANS0=1; break;
        case ADC_CHANNEL_AN1 : TRISAbits.RA1=1; ANSELbits.ANS1=1; break;
        case ADC_CHANNEL_AN2 : TRISAbits.RA2=1; ANSELbits.ANS2=1; break;
        case ADC_CHANNEL_AN3 : TRISAbits.RA3=1; ANSELbits.ANS3=1; break;
        case ADC_CHANNEL_AN4 : TRISAbits.RA5=1; ANSELbits.ANS4=1; break;
        case ADC_CHANNEL_AN5 : TRISEbits.RE0=1; ANSELbits.ANS5=1; break;
        case ADC_CHANNEL_AN6 : TRISEbits.RE1=1; ANSELbits.ANS6=1; break;
        case ADC_CHANNEL_AN7 : TRISEbits.RE2=1; ANSELbits.ANS7=1; break;
        case ADC_CHANNEL_AN8 : TRISBbits.RB2=1; ANSELHbits.ANS8=1; break;
        case ADC_CHANNEL_AN9 : TRISBbits.RB3=1; ANSELHbits.ANS9=1; break;
        case ADC_CHANNEL_AN10: TRISBbits.RB1=1; ANSELHbits.ANS10=1; break;
        case ADC_CHANNEL_AN11: TRISBbits.RB4=1; ANSELHbits.ANS11=1; break;
        case ADC_CHANNEL_AN12: TRISBbits.RB0=1; ANSELHbits.ANS12=1; break;
    }
}

