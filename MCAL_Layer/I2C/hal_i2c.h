/* 
 * File:   hal_i2c.h
 * Author: mohsen
 *
 * Created on March 16, 2023, 5:11 PM
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H

/******* section : Includes *******/
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../compiler.h"
#include "../mcal_std_types.h"
#include "../std_libraries.h"

/******* section : macros Declarations *******/
#define I2C_SLEW_RATE_DISABLE               1
#define I2C_SLEW_RATE_ENABLE                0

#define I2C_SMBus_ENABLE                    1
#define I2C_SMBus_DISABLE                   0

#define I2C_LAST_RT_BYTE_DATA	            1
#define I2C_LAST_RT_BYTE_ADDRESS            0

#define I2C_STOP_BIT_DETECTED               1
#define I2C_STOP_BIT_NOT_DETECTED           0

#define I2C_START_BIT_DETECTED              1
#define I2C_START_BIT_NOT_DETECTED          0

#define I2C_ACK_RECEIVED_FROM_SLAVE         0
#define I2C_ACK_NOT_RECEIVED_FROM_SLAVE     1

#define I2C_MASTER_SEND_ACK                 0
#define I2C_MASTER_SEND_NACK                1

#define I2C_SLAVE_RECEIVE_DATA              0
#define I2C_SLAVE_SEND_DATA                 1

#define I2C_GENERAL_CALL_ENABLE             1
#define I2C_GENERAL_CALL_DISABLE            0

#define I2C_MASTER_RECEIVE_ENABLE           1
#define I2C_MASTER_RECEIVE_DISABLE          0

/******* section : function-like macros Declarations *******/
#define I2C_SLEW_RATE_DISABLE_CFG()         (SSPSTATbits.SMP = 1)
#define I2C_SLEW_RATE_ENABLE_CFG()          (SSPSTATbits.SMP = 0)

#define I2C_SMBus_DISABLE_CFG()             (SSPSTATbits.CKE = 0)
#define I2C_SMBus_ENABLE_CFG()              (SSPSTATbits.CKE = 1)

#define MSSP_MODULE_ENABLE_CFG()            (SSPCON1bits.SSPEN = 1)
#define MSSP_MODULE_DISABLE_CFG()           (SSPCON1bits.SSPEN = 0)

#define I2C_CLOCK_STRETCH_ENABLE()          (SSPCON2bits.SEN = 1)
#define I2C_CLOCK_STRETCH_DISABLE()         (SSPCON2bits.SEN = 0)

#define I2C_CLOCK_STRETCH_HOLD()            (SSPCON1bits.CKP = 0)
#define I2C_CLOCK_STRETCH_RELEASE()         (SSPCON1bits.CKP = 1)

#define I2C_MODE_SELECT(_X)                 (SSPCON1bits.SSPM=_X)

#define I2C_MASTER_ACK_BIT(_X)              (SSPCON2bits.ACKDT=_X)

#define I2C_MASTER_ACK_BIT_SEND()           (SSPCON2bits.ACKEN=1)

#define I2C_GENERAL_CALL_DISABLE_CFG()      (SSPCON2bits.GCEN = 0)
#define I2C_GENERAL_CALL_ENABLE_CFG()       (SSPCON2bits.GCEN = 1)

#define I2C_MASTER_RECEIVE_DISABLE_CFG()    (SSPCON2bits.RCEN = 0)
#define I2C_MASTER_RECEIVE_ENABLE_CFG()     (SSPCON2bits.RCEN = 1)

#define I2C_MASTER_SEND_STOP()              (SSPCON2bits.PEN = 1)

#define I2C_MASTER_SEND_START()             (SSPCON2bits.SEN = 1)

#define I2C_MASTER_SEND_REPEAT_START()      (SSPCON2bits.RSEN = 1)

#define PIN_CFG(){\
    TRISCbits.RC3=1; \
    TRISCbits.RC4=1; \
}

/******* section : Data Types Declarations *******/
typedef enum{
    I2C_SLAVE_MODE_7BIT_ADDRESS=6,
    I2C_SLAVE_MODE_10BIT_ADDRESS,
    I2C_MASTER_MODE_DEFINED_CLOCK,
    I2C_MASTER_MODE_FIRMWARE_CONTROLLED,
    I2C_SLAVE_MODE_7BIT_ADDRESS_SS_INT_ENABLE,
    I2C_SLAVE_MODE_10BIT_ADDRESS_SS_INT_ENABLE
}i2c_mode_cfg_t;

typedef struct{
    i2c_mode_cfg_t mode_select;
    uint32 clock_speed;
    uint8 i2c_slave_address;
    uint8 i2c_slew_rate      : 1;
    uint8 i2c_general_call   : 1;
    uint8 i2c_reserved       : 6; 
#if I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (*I2C_Report_Write_Collision)(void);	/* Write Collision Indicator */
    void (*I2C_DefaultInterruptHandler)(void); 	/* Default Interrupt Handler */
    void (*I2C_Report_Receive_Overflow)(void); 	/* Receive Overflow Indicator */
#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg i2c_priority;
    interrupt_priority_cfg i2c_bc_priority;
#endif 
#endif      
}i2c_t;

/******* section : Function Declarations *******/
Std_ReturnType I2C_master_Init(const i2c_t *i2c_obj);
Std_ReturnType I2C_slave_Init(const i2c_t *i2c_obj);
Std_ReturnType I2C_DeInit(const i2c_t *i2c_obj);

Std_ReturnType MSSP_I2C_Master_Write_Blocking(const i2c_t *i2c_obj, uint8 i2c_data, uint8 *_ack);
Std_ReturnType MSSP_I2C_Master_Read_Blocking(const i2c_t *i2c_obj, uint8 ack, uint8 *i2c_data);

Std_ReturnType MSSP_I2C_Master_Write_NBlocking(const i2c_t *i2c_obj, uint8 i2c_data, uint8 *_ack);
Std_ReturnType MSSP_I2C_Master_Read_NBlocking(const i2c_t *i2c_obj, uint8 ack, uint8 *i2c_data);

Std_ReturnType MSSP_I2C_slave_Write_Blocking(const i2c_t *i2c_obj, uint8 i2c_data, uint8 *_ack);
Std_ReturnType MSSP_I2C_slave_Read_Blocking(const i2c_t *i2c_obj, uint8 *i2c_data);

Std_ReturnType MSSP_I2C_slave_Write_NBlocking(const i2c_t *i2c_obj, uint8 i2c_data, uint8 *_ack);
Std_ReturnType MSSP_I2C_slave_Read_NBlocking(const i2c_t *i2c_obj, uint8 *i2c_data);

Std_ReturnType MSSP_I2C_Master_Send_Start(const i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Stop(const i2c_t *i2c_obj);

#endif	/* HAL_I2C_H */

