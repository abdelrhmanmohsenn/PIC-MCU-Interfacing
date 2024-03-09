/* 
 * File:   hal_spi.h
 * Author: mohsen
 *
 * Created on March 8, 2023, 10:14 PM
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H

/******* section : Includes *******/
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../compiler.h"
#include "../mcal_std_types.h"
#include "../std_libraries.h"

/******* section : macros Declarations *******/
#define SPI_MODULE_ENABLE                          1
#define SPI_MODULE_DISABLE                         0

#define CLOCK_LOW_TRAMITTING_ACTIVE_TO_IDLE        0
#define CLOCK_LOW_TRAMITTING_IDLE_TO_ACTIVE        1
#define CLOCK_HIGH_TRAMITTING_ACTIVE_TO_IDLE       2
#define CLOCK_HIGH_TRAMITTING_IDLE_TO_ACTIVE       3

#define MASTER_SAMPLE_MODE_AT_END                  0
#define MASTER_SAMPLE_MODE_AT_MIDDLE               1
#define SLAVE_SAMPLE_MODE                          2

#define COLLISION_DETECTED                         1
#define NO_COLLISION_DETECTED                      0

/******* section : function-like macros Declarations *******/
#define SPI_SERIAL_ENABLE()                         (SSPCON1bits.SSPEN=1)
#define SPI_SERIAL_DISABLE()                        (SSPCON1bits.SSPEN=0)

#define SPI_MASTER_SAMPLE_MODE_AT_END()             (SSPSTATbits.SMP=1)
#define SPI_MASTER_SAMPLE_MODE_AT_MIDDLE()          (SSPSTATbits.SMP=0)
#define SPI_SLAVE_SAMPLE_MODE()                     (SSPSTATbits.SMP=0)

#define SPI_CLOCK_ACTIVE_TO_IDLE()                  (SSPSTATbits.CKE=1)
#define SPI_CLOCK_IDLE_TO_ACTIVE()                  (SSPSTATbits.CKE=0)

#define SPI_CLOCK_IDLE_STATE_HIGH()                 (SSPCON1bits.CKP=1)
#define SPI_CLOCK_IDLE_STATE_LOW()                  (SSPCON1bits.CKP=0)

#define SPI_SYNC_MODE_SELECT(_X)                    (SSPCON1bits.SSPM=(_X))

#define TRANSMITTING_COLLISION_DECTOR_CLEAR()       (SSPCON1bits.WCOL=0)    /* transmitting mode only */

#define RECEIVE_OVERFLOW_INDICATOR_CLEAR()          (SSPCON1bits.SSPOV=0)  /* Slave mode only */
/******* section : Data Types Declarations *******/
typedef enum{
    SPI_MASTER_MODE_CLOCK_DIV_4,
    SPI_MASTER_MODE_CLOCK_DIV_16,
    SPI_MASTER_MODE_CLOCK_DIV_64,
    SPI_MASTER_MODE_CLOCK_TMR2_DIV_2,
    SPI_SLAVE_MODE_CLOCK_SCK_SS_ENABLED,
    SPI_SLAVE_MODE_CLOCK_SCK_SS_DISABLED        
}spi_mode_select_t ;

typedef pin_config_t slave_t;

typedef struct{
    spi_mode_select_t mode_select;
    uint8 sync_mode    : 2;
    uint8 sample_mode  : 2;
    uint8 reserved     : 4;
#if SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (*SPI_DefaultInterruptHandler)(void);
#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE   
    interrupt_priorty_t priority;
#endif
#endif
}spi_t;

/******* section : Function Declarations *******/
Std_ReturnType spi_init(const spi_t *spi_obj);
Std_ReturnType spi_Deinit(const spi_t *spi_obj);

Std_ReturnType spi_slave_select_init(const slave_t *slave_select);

Std_ReturnType spi_master_TransmitOnly_Blocking(const spi_t *spi_obj, slave_t *slave_select, uint8 transmit_data);
Std_ReturnType spi_master_ReceiveOnly_Blocking(const spi_t *spi_obj, slave_t *slave_select, uint8 *receive_data);
Std_ReturnType spi_master_Transmit_Receive_Blocking(const spi_t *spi_obj, slave_t *slave_select, uint8 transmit_data,
                                                    uint8 *receive_data);
Std_ReturnType spi_master_TransmitOnly_NonBlocking(const spi_t *spi_obj, slave_t *slave_select, uint8 transmit_data);
Std_ReturnType spi_master_ReceiveOnly_NonBlocking(const spi_t *spi_obj, slave_t *slave_select, uint8 *receive_data);
Std_ReturnType spi_master_Transmit_Receive_NonBlocking(const spi_t *spi_obj, slave_t *slave_select, uint8 *receive_data, 
                                                       uint8 transmit_data);

Std_ReturnType spi_slave_TransmitOnly(const spi_t *spi_obj, uint8 transmit_data);
Std_ReturnType spi_slave_ReceiveOnly_blocking(const spi_t *spi_obj, uint8 *receive_data);
Std_ReturnType spi_slave_Transmit_Receive_blocking(const spi_t *spi_obj, uint8 transmit_data, uint8 *receive_data);
Std_ReturnType spi_slave_ReceiveOnly_Nonblocking(const spi_t *spi_obj, uint8 *receive_data);
Std_ReturnType spi_slave_Transmit_Receive_Nonblocking(const spi_t *spi_obj, uint8 transmit_data, uint8 *receive_data);

#endif	/* HAL_SPI_H */

