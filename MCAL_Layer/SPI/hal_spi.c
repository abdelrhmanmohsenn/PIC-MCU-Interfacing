/* 
 * File:   hal_spi.h
 * Author: mohsen
 *
 * Created on March 8, 2023, 10:14 PM
 */

#include "hal_spi.h"

#if SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*SPI_InterruptHandler)(void) = NULL;
#endif

#if SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void SPI_ISR(void){
    SPI_FlagClear();
    if(SPI_InterruptHandler){ SPI_InterruptHandler(); }
    else{/* Nothing */}
}
#endif

static void spi_mode_select(const spi_t *spi_obj);
static void spi_sync_mode_select(const spi_t *spi_obj);
static void spi_sample_mode_select(const spi_t *spi_obj);
static void spi_gpio_cfg(const spi_t *spi_obj);

Std_ReturnType spi_init(const spi_t *spi_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == spi_obj){
        ret=E_NOT_OK;
    }
    else{ 
        SPI_SERIAL_DISABLE();
        spi_mode_select(spi_obj);
        spi_sync_mode_select(spi_obj);
        spi_sample_mode_select(spi_obj);
        spi_gpio_cfg(spi_obj);
#if SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        SPI_InterruptHandler=spi_obj->SPI_DefaultInterruptHandler;
#endif
        SPI_SERIAL_ENABLE();
    }
    
    return ret;
}

Std_ReturnType spi_Deinit(const spi_t *spi_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == spi_obj){
        ret=E_NOT_OK;
    }
    else{ 
        SPI_SERIAL_DISABLE();
    }
    
    return ret;
}

Std_ReturnType spi_slave_select_init(const slave_t *slave_select){
    Std_ReturnType ret=E_OK;
    
    if(NULL == slave_select){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_initialize(slave_select);
    }
    
    return ret;
}

Std_ReturnType spi_master_TransmitOnly_Blocking(const spi_t *spi_obj, slave_t *slave_select, uint8 transmit_data){
    Std_ReturnType ret=E_OK;
    
    if(NULL == spi_obj){
        ret=E_NOT_OK;
    }
    else{
        if(NO_COLLISION_DETECTED == SSPCON1bits.WCOL){
            gpio_pin_write(slave_select,PIN_LOW);
            SSPBUF=transmit_data;
            while(PIR1bits.SSPIF);
            PIR1bits.SSPIF=0;
            gpio_pin_write(slave_select,PIN_HIGH);
        }
        else if(COLLISION_DETECTED == SSPCON1bits.WCOL){
            TRANSMITTING_COLLISION_DECTOR_CLEAR();
            ret=E_NOT_OK;
        }
        else {/* Nothing */}
    }    
    
    return ret;
}

Std_ReturnType spi_master_ReceiveOnly_Blocking(const spi_t *spi_obj, slave_t *slave_select, uint8 *receive_data){
    Std_ReturnType ret=E_OK;
    
    if(NULL == spi_obj || NULL == receive_data){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_write(slave_select,PIN_LOW);
        SSPBUF=0x00;
        while(!SSPSTATbits.BF);
        *receive_data=SSPBUF;
        gpio_pin_write(slave_select,PIN_HIGH);
    }
    
    return ret;
}

Std_ReturnType spi_master_Transmit_Receive_Blocking(const spi_t *spi_obj, slave_t *slave_select, uint8 transmit_data, 
                                             uint8 *receive_data){
    Std_ReturnType ret=E_OK;
    
    if(NULL == spi_obj || NULL == receive_data){
        ret=E_NOT_OK;
    }
    else{
        if(NO_COLLISION_DETECTED == SSPCON1bits.WCOL){
            gpio_pin_write(slave_select,PIN_LOW);
            SSPBUF=transmit_data;
            while(SSPSTATbits.BF);
            *receive_data=SSPBUF;
            gpio_pin_write(slave_select,PIN_HIGH);
        }
        else if(COLLISION_DETECTED == SSPCON1bits.WCOL){
            TRANSMITTING_COLLISION_DECTOR_CLEAR();
            ret=E_NOT_OK;
        }
        else {/* Nothing */}
    }
    
    return ret;
}

Std_ReturnType spi_master_TransmitOnly_NonBlocking(const spi_t *spi_obj, slave_t *slave_select, uint8 transmit_data){
    Std_ReturnType ret=E_OK;
    static uint8 indicator=0;
    
    if(NULL == spi_obj || NULL == slave_select){
        ret=E_NOT_OK;
    }
    else{
        if((0 == indicator) && (NO_COLLISION_DETECTED == SSPCON1bits.WCOL)){
            gpio_pin_write(slave_select,PIN_LOW);
            SSPBUF=transmit_data;
            indicator++;
        }
        else{
            if(PIR1bits.SSPIF){
                PIR1bits.SSPIF=0;
                gpio_pin_write(slave_select,PIN_HIGH);
                indicator=0;
            }
            else {/* Nothing */}
        }
    }
    
    return ret;
}

Std_ReturnType spi_master_ReceiveOnly_NonBlocking(const spi_t *spi_obj, slave_t *slave_select, uint8 *receive_data){
    Std_ReturnType ret=E_OK;
    static uint8 indicator=0;
    
    if(NULL == spi_obj || NULL == receive_data){
        ret=E_NOT_OK;
    }
    else{
        if(0 == indicator){
            gpio_pin_write(slave_select,PIN_LOW);
            SSPBUF=0x00;
            indicator++;
        }
        else{
            if(SSPSTATbits.BF){
                *receive_data=SSPBUF;
                gpio_pin_write(slave_select,PIN_HIGH);
                indicator=0;
            }
            else {/* Nothing */}
        }
    }
    
    return ret;
}

Std_ReturnType spi_master_Transmit_Receive_NonBlocking(const spi_t *spi_obj, slave_t *slave_select, uint8 *receive_data, 
                                                       uint8 transmit_data){
    Std_ReturnType ret=E_OK;
    static uint8 indicator=0;
    
    if(NULL == spi_obj || NULL == receive_data || NULL == slave_select){
        ret=E_NOT_OK;
    }
    else{
        if((0 == indicator) && (NO_COLLISION_DETECTED == SSPCON1bits.WCOL)){
            gpio_pin_write(slave_select,PIN_LOW);
            SSPBUF=transmit_data;
            indicator++;
        }
        else{
            if(SSPSTATbits.BF){
                *receive_data=SSPBUF;
                gpio_pin_write(slave_select,PIN_HIGH);
                indicator=0;
            }
            else {/* Nothing */}
        }
    }
    
    return ret;
}

Std_ReturnType spi_slave_TransmitOnly(const spi_t *spi_obj, uint8 transmit_data){
    Std_ReturnType ret=E_OK;
    
    if(NULL == spi_obj){
        ret=E_NOT_OK;
    }
    else{
        SSPBUF=transmit_data;
    }
    
    return ret;
}

Std_ReturnType spi_slave_ReceiveOnly_blocking(const spi_t *spi_obj, uint8 *receive_data){
    Std_ReturnType ret=E_OK;
    
    if(NULL == spi_obj){
        ret=E_NOT_OK;
    }
    else{
        while(!SSPSTATbits.BF);
        *receive_data=SSPBUF;
    }
    
    return ret;
}

Std_ReturnType spi_slave_Transmit_Receive_blocking(const spi_t *spi_obj, uint8 transmit_data, uint8 *receive_data){
    Std_ReturnType ret=E_OK;
    
    if(NULL == spi_obj){
        ret=E_NOT_OK;
    }
    else{
        SSPBUF=transmit_data;
        while(!SSPSTATbits.BF);
        *receive_data=SSPBUF;
    }
    
    return ret;
}

Std_ReturnType spi_slave_ReceiveOnly_Nonblocking(const spi_t *spi_obj, uint8 *receive_data){
    Std_ReturnType ret=E_OK;
    
    if(NULL == spi_obj){
        ret=E_NOT_OK;
    }
    else{
        if(SSPSTATbits.BF){
           *receive_data=SSPBUF; 
        }
        else {/* Nothing */}
    }
    
    return ret;
}

Std_ReturnType spi_slave_Transmit_Receive_Nonblocking(const spi_t *spi_obj, uint8 transmit_data, uint8 *receive_data){
    Std_ReturnType ret=E_OK;
    static uint8 indicator=0;
    
    if(NULL == spi_obj || NULL == receive_data){
        ret=E_NOT_OK;
    }
    else{
        if(0 == indicator){
            SSPBUF=transmit_data;
            indicator++;
        }
        else{
            if(SSPSTATbits.BF){
                *receive_data=SSPBUF; 
                indicator=0;
            }
            else {/* Nothing */}
        }
    }
    
    return ret;
    
}

static void spi_mode_select(const spi_t *spi_obj){
    switch(spi_obj->mode_select){
        case SPI_MASTER_MODE_CLOCK_DIV_4  : SPI_SYNC_MODE_SELECT(SPI_MASTER_MODE_CLOCK_DIV_4); break;
        case SPI_MASTER_MODE_CLOCK_DIV_16 : SPI_SYNC_MODE_SELECT(SPI_MASTER_MODE_CLOCK_DIV_16); break;
        case SPI_MASTER_MODE_CLOCK_DIV_64 : SPI_SYNC_MODE_SELECT(SPI_MASTER_MODE_CLOCK_DIV_64); break;
        case SPI_MASTER_MODE_CLOCK_TMR2_DIV_2 : SPI_SYNC_MODE_SELECT(SPI_MASTER_MODE_CLOCK_TMR2_DIV_2); break;
        case SPI_SLAVE_MODE_CLOCK_SCK_SS_ENABLED : SPI_SYNC_MODE_SELECT(SPI_SLAVE_MODE_CLOCK_SCK_SS_ENABLED); break;
        case SPI_SLAVE_MODE_CLOCK_SCK_SS_DISABLED : SPI_SYNC_MODE_SELECT(SPI_SLAVE_MODE_CLOCK_SCK_SS_DISABLED); break;
    }
}

static void spi_sync_mode_select(const spi_t *spi_obj){
    if(CLOCK_LOW_TRAMITTING_ACTIVE_TO_IDLE == spi_obj->sync_mode){
        SPI_CLOCK_IDLE_STATE_LOW();
        SPI_CLOCK_ACTIVE_TO_IDLE();
    }
    else if(CLOCK_LOW_TRAMITTING_IDLE_TO_ACTIVE == spi_obj->sync_mode){
        SPI_CLOCK_IDLE_STATE_LOW();
        SPI_CLOCK_IDLE_TO_ACTIVE();
    }
    else if(CLOCK_HIGH_TRAMITTING_ACTIVE_TO_IDLE == spi_obj->sync_mode){
        SPI_CLOCK_IDLE_STATE_HIGH();
        SPI_CLOCK_ACTIVE_TO_IDLE();
    }
    else if(CLOCK_HIGH_TRAMITTING_IDLE_TO_ACTIVE == spi_obj->sync_mode){
        SPI_CLOCK_IDLE_STATE_HIGH();
        SPI_CLOCK_IDLE_TO_ACTIVE();
    }
    else {/* Nothing */}
}

static void spi_sample_mode_select(const spi_t *spi_obj){
    switch(spi_obj->sample_mode){
        case MASTER_SAMPLE_MODE_AT_END    : SPI_MASTER_SAMPLE_MODE_AT_END(); break;
        case MASTER_SAMPLE_MODE_AT_MIDDLE : SPI_MASTER_SAMPLE_MODE_AT_MIDDLE(); break;
        case SLAVE_SAMPLE_MODE            : SPI_SLAVE_SAMPLE_MODE(); break;
    }
}

static void spi_gpio_cfg(const spi_t *spi_obj){
    TRISCbits.RC5=0;     /* Clear SDI pin */
    TRISAbits.RA5=1;     /* Set SS pin */
    if(SPI_SLAVE_MODE_CLOCK_SCK_SS_ENABLED == spi_obj->mode_select ||
       SPI_SLAVE_MODE_CLOCK_SCK_SS_DISABLED  == spi_obj->mode_select){
        TRISCbits.RC3=1;
    }
    else{
        TRISCbits.RC3=0;
    }
}

