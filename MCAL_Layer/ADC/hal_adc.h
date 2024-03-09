/* 
 * File:   hal_adc.h
 * Author: mohsen
 *
 * Created on February 15, 2023, 12:07 AM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/******* section : Includes *******/
#include "hal_adc_cfg.h"
#include "../mcal_std_types.h"
#include "../compiler.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/******* section : macros Declarations *******/
#define RIGHT_FORMAT     1
#define LEFT_FORMAT      0

#define EXTERNAL_VOLTAGE_REFERENCE    1
#define INTERNAL_VOLTAGE_REFERENCE    0

/******* section : function-like macros Declarations *******/

/**
 * @brief Select the channel for conversion
 */
#define ADC_CHANNEL_SELECT(_X)          (ADCON0bits.CHS=X)

/**
 * @brief Start the Analog-To-Digital Conversion
 */
#define ADC_CONVERSION_START()          (ADCON0bits.GO=1)

/**
 * @brief  Analog-To-Digital Control
 * @note   ADC_CONVERTER_ENABLE()  : Enable the Analog-To-Digital
 *         ADC_CONVERTER_DISABLE() : Disable the Analog-To-Digital
 */
#define ADC_CONVERTER_ENABLE()          (ADCON0bits.ADON=1)
#define ADC_CONVERTER_DISABLE()         (ADCON0bits.ADON=0)

/* A/D Conversion Status : A/D conversion in progress / A/D Idle */
#define ADC_CONVERSION_DONE()           (ADCON0bits.DONE)

/**
 * @brief  Voltage Reference Configuration
 * @note   ADC_ENABLE_VOLTAGE_REFERENCE()  : Voltage Reference is VREF- & VREF+
 *         ADC_DISABLE_VOLTAGE_REFERENCE() : Voltage Reference is VSS & VDD
 */
#define ADC_ENABLE_VOLTAGE_REFERENCE()  do{ADCON1bits.VCFG1 = 1;\
                                           ADCON1bits.VCFG0 = 1;\
                                        }while(0)
#define ADC_DISABLE_VOLTAGE_REFERENCE() do{ADCON1bits.VCFG1 = 0;\
                                           ADCON1bits.VCFG0 = 0;\
                                        }while(0)

/**
 * @brief  A/D Result Format Select
 */
#define ADC_CONVERSION_FORMAT_RIGHT()     (ADCON2bits.ADFM=1)
#define ADC_CONVERSION_FORMAT_LEFT()      (ADCON2bits.ADFM=0)



/******* section : Data Types Declarations *******/
typedef enum{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12
}adc_channel_select_t;

typedef enum{
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD        
}adc_aquaisition_time_t;

typedef enum{
  ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64
}adc_conversion_clock_t;

typedef struct{
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* adc_interrupthandler)(void);
#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    uint8 priority  : 1;
#endif
#endif
    adc_aquaisition_time_t adc_aquaisition;
    adc_conversion_clock_t adc_clock;
    adc_channel_select_t channel ;
    uint8 result_format    :1;
    uint8 voltage_refernce :1;
    uint8 reserved         :5;
}adc_conf_t;

typedef uint16 adc_result_t;

/******* section : Function Declarations *******/
Std_ReturnType ADC_Init(const adc_conf_t *_adc);
Std_ReturnType ADC_DeInit(const adc_conf_t *_adc);
Std_ReturnType ADC_SelectChannel(const adc_conf_t *_adc, adc_channel_select_t channel);
Std_ReturnType ADC_StartConversion(const adc_conf_t *_adc);
Std_ReturnType ADC_IsConversionDone(const adc_conf_t *_adc, uint8 *conversion_status);
Std_ReturnType ADC_GetConversionResult(const adc_conf_t *_adc, adc_result_t *conversion_result);
Std_ReturnType ADC_GetConversion_Blocking(const adc_conf_t *_adc, adc_channel_select_t channel, 
                                 adc_result_t *conversion_result);
Std_ReturnType ADC_StartConversion_Interrupt(const adc_conf_t *_adc, adc_channel_select_t channel); 


#endif	/* HAL_ADC_H */

