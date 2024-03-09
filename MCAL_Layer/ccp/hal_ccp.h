/* 
 * File:   hal_ccp1.h
 * Author: mohsen
 *
 * Created on February 26, 2023, 6:53 PM
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/******* section : Includes *******/
#include "ccp_cfg.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../compiler.h"
#include "../mcal_std_types.h"
#include "../std_libraries.h"

/******* section : macros Declarations *******/
/* CCP1 Module Mode Select  */
#define CCP_MODULE_DISABLE                 ((uint8)0x00)
#define CCP_CAPTURE_MODE_1_FALLING_EDGE    ((uint8)0x04)
#define CCP_CAPTURE_MODE_1_RISING_EDGE     ((uint8)0x05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE     ((uint8)0x06)
#define CCP_CAPTURE_MODE_16_RISING_EDGE    ((uint8)0x07)
#define CCP_COMPARE_MODE_SET_PIN_LOW       ((uint8)0x08)
#define CCP_COMPARE_MODE_SET_PIN_HIGH      ((uint8)0x09)
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH   ((uint8)0x02)
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT  ((uint8)0x0A)
#define CCP_COMPARE_MODE_GEN_EVENT         ((uint8)0x0B)
#define CCP_PWM_MODE                       ((uint8)0x0C)

/* Timer2 Input Clock Post-scaler */
#define CCP_TIMER2_POSTSCALER_DIV_BY_1       1
#define CCP_TIMER2_POSTSCALER_DIV_BY_2       2
#define CCP_TIMER2_POSTSCALER_DIV_BY_3       3
#define CCP_TIMER2_POSTSCALER_DIV_BY_4       4
#define CCP_TIMER2_POSTSCALER_DIV_BY_5       5
#define CCP_TIMER2_POSTSCALER_DIV_BY_6       6
#define CCP_TIMER2_POSTSCALER_DIV_BY_7       7
#define CCP_TIMER2_POSTSCALER_DIV_BY_8       8
#define CCP_TIMER2_POSTSCALER_DIV_BY_9       9
#define CCP_TIMER2_POSTSCALER_DIV_BY_10      10
#define CCP_TIMER2_POSTSCALER_DIV_BY_11      11
#define CCP_TIMER2_POSTSCALER_DIV_BY_12      12
#define CCP_TIMER2_POSTSCALER_DIV_BY_13      13
#define CCP_TIMER2_POSTSCALER_DIV_BY_14      14
#define CCP_TIMER2_POSTSCALER_DIV_BY_15      15
#define CCP_TIMER2_POSTSCALER_DIV_BY_16      16

/* Timer2 Input Clock Pre-scaler */
#define CCP_TIMER2_PRESCALER_DIV_BY_1        1
#define CCP_TIMER2_PRESCALER_DIV_BY_4        4
#define CCP_TIMER2_PRESCALER_DIV_BY_16       16

/* CCP Capture Mode State  */
#define CCP_CAPTURE_NOT_READY                0X00
#define CCP_CAPTURE_READY                    0X01

/* CCP Compare Mode State  */
#define CCP_COMPARE_NOT_READY                0X00
#define CCP_COMPARE_READY                    0X01

/******* section : function-like macros Declarations *******/
#define ccp2_mode_config(_x)                (CCP2CONbits.CCP2M=_x)
#define ccp1_mode_config(_x)                (CCP1CONbits.CCP1M=_x)


/******* section : Data Types Declarations *******/
typedef enum{
    CCP_CAPTURE_MODE_SELECTED = 0, /* Select CCP Capture Mode */
    CCP_COMPARE_MODE_SELECTED,     /* Select CCP Compare Mode */
    CCP_PWM_MODE_SELECTED          /* Select CCP PWM Mode */
}ccp1_mode_t;

typedef enum{
    ccp1_ccp2_timer3=0,
    ccp1_timer1_ccp2_timer3,
    ccp1_ccp2_timer1       
}ccp_timer_select_t;

typedef enum{
    CCP1_INST = 0,
    CCP2_INST
}ccp_inst_t;

typedef union{
    struct{
        uint8 ccpL;
        uint8 ccpH;
    };
    struct{
        uint16 ccp_16Bit;
    };
}ccp_reg_t;

typedef struct{
    ccp_inst_t ccp_inst;
    ccp_timer_select_t ccp_timer;
    ccp1_mode_t ccp_mode;
    uint8 ccp_mode_variant;
#if CCP1_MODE_SELECT == CCP_CFG_COMPARE_MODE_SELECTED || CCP2_MODE_SELECT == CCP_CFG_COMPARE_MODE_SELECTED
    uint16 compare_value;
#endif
#if CCP1_MODE_SELECT == CCP_CFG_PWM_MODE_SELECTED || CCP2_MODE_SELECT == CCP_CFG_PWM_MODE_SELECTED
    uint32 pwm_frequency;
    uint8 timer2_postscaler_value;
    uint8 timer2_prescaler_value;
#endif
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE || CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* CCP1_interruptHandler)(void);
 #if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE   
    interrupt_priorty_t priority;
#endif
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* CCP2_interruptHandler)(void);
 #if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE   
    interrupt_priorty_t priority;
#endif
#endif    
}ccp_t;

/******* section : Function Declarations *******/
Std_ReturnType ccp_init(ccp_t *ccp_obj);
Std_ReturnType ccp_DeInit(ccp_t *ccp_obj);

#if CCP1_MODE_SELECT == CCP_CFG_COMPARE_MODE_SELECTED || CCP2_MODE_SELECT == CCP_CFG_COMPARE_MODE_SELECTED
Std_ReturnType CCP_IsCompareComplete(ccp_t *ccp_obj, uint8 *_compare_status);
Std_ReturnType CCP_Compare_Mode_Set_Value(ccp_t *_ccp_obj, uint16 compare_value);
#endif

#if CCP1_MODE_SELECT == CCP_CFG_CAPTURE_MODE_SELECTED || CCP2_MODE_SELECT == CCP_CFG_CAPTURE_MODE_SELECTED
Std_ReturnType CCP_IsCapturedDataReady(ccp_t *ccp_obj, uint8 *_capture_status);
Std_ReturnType CCP_Capture_Mode_Read_Value(ccp_t *ccp_obj, uint16 *capture_value);
#endif

#if CCP1_MODE_SELECT == CCP_CFG_PWM_MODE_SELECTED || CCP1_MODE_SELECT == CCP_CFG_PWM_MODE_SELECTED
Std_ReturnType set_dutyCycle(ccp_t *ccp_obj, uint8 dutyValue);
Std_ReturnType pwm_start(ccp_t *ccp_obj);
Std_ReturnType pwm_stop(ccp_t *ccp_obj);
#endif  

#endif	/* HAL_CCP1_H */

