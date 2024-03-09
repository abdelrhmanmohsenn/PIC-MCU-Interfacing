/* 
 * File:   hal_usart.c
 * Author: mohsen
 *
 * Created on March 5, 2023, 7:37 PM
 */

#include "hal_usart.h"

#if USART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*USART_TxInterruptHandler)(void) = NULL;
#endif
#if USART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*USART_RxInterruptHandler)(void) = NULL;
    static void (*USART_FramingErrorHandler)(void) = NULL;
    static void (*USART_OverrunErrorHandler)(void) = NULL;
#endif

static void USART_Baud_Rate_Calculation(const usart_t *usart);
static void USART_ASYNC_TX_Init(const usart_t *usart);
static void USART_ASYNC_RX_Init(const usart_t *usart);

#if USART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void USART_TX_ISR(void){
    USART_TX_FlagClear();
    if(USART_TxInterruptHandler){ USART_TxInterruptHandler(); }
    else{/* Nothing */}
}
#endif

#if USART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void USART_RX_ISR(void){
    if(USART_RxInterruptHandler){ USART_RxInterruptHandler(); }
    else{/* Nothing */}
    if(USART_FramingErrorHandler){ USART_FramingErrorHandler(); }
    else{/* Nothing */}
    if(USART_OverrunErrorHandler){ USART_OverrunErrorHandler(); }
    else{/* Nothing */}
}
#endif

Std_ReturnType USART_ASYNC_Init(const usart_t *usart){
    Std_ReturnType ret=E_OK;
    
    if(NULL == usart){
        ret=E_NOT_OK;
    }
    else{ 
        RCSTAbits.SPEN=EUSART_MODULE_DISABLE;
        TRISCbits.RC7 = 1;                      
        TRISCbits.RC6 = 1;
        USART_ASYNC_TX_Init(usart);
        USART_ASYNC_RX_Init(usart);
        USART_Baud_Rate_Calculation(usart);
        RCSTAbits.SPEN=EUSART_MODULE_ENABLE;
    }
    
    return ret;
}

Std_ReturnType USART_ASYNC_DeInit(const usart_t *usart){
    Std_ReturnType ret=E_OK;
    
    if(NULL == usart){
        ret=E_NOT_OK;
    }
    else{ 
       RCSTAbits.SPEN=EUSART_MODULE_DISABLE;
    }
    
    return ret;
}

Std_ReturnType USART_ASYNC_ReadByteBlocking(uint8 *data){
    Std_ReturnType ret=E_OK;
    
    if(NULL == data){
        ret=E_NOT_OK;
    }
    else{ 
        while(!PIR1bits.RCIF);
        *data = RCREG;
    }
    
    return ret;
}

Std_ReturnType USART_ASYNC_ReadByteNonBlocking(uint8 *data){
    Std_ReturnType ret = E_NOT_OK;
    if(1 == PIR1bits.RCIF){
        *data = RCREG;
        ret = E_OK;
    }
    else{
        ret = E_NOT_OK;
    }
    return ret;
}

Std_ReturnType USART_ASYNC_RX_Restart(void){
    Std_ReturnType ret = E_OK;
    RCSTAbits.CREN = 0; /* Disables receiver */
    RCSTAbits.CREN = 1; /* Enables receiver */
    return ret;
}

Std_ReturnType USART_ASYNC_WriteByteBlocking(uint8 data){
    Std_ReturnType ret=E_OK;
    
    while(!TXSTAbits.TRMT);
    TXREG=data;
    
    return ret;
}

Std_ReturnType USART_ASYNC_WriteStringBlocking(uint8 *data, uint16 str_len){
    Std_ReturnType ret=E_OK;
    
    if(NULL == data){
        ret=E_NOT_OK;
    }
    else{ 
        for(int i=0 ; i<str_len ; i++){
            USART_ASYNC_WriteByteBlocking(data[i]);
        }
    }
    
    return ret;
}

Std_ReturnType USART_ASYNC_WriteByteNonBlocking(uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    if(1 == TXSTAbits.TRMT){
        TXREG=data;
        ret = E_OK;
    }
    else{
        ret = E_NOT_OK;
    }
    return ret;
}

Std_ReturnType USART_ASYNC_WriteStringNonBlocking(uint8 *data, uint16 str_len){
    Std_ReturnType ret=E_OK;
    static int i=0;
    if(NULL == data){
        ret=E_NOT_OK;
    }
    else{ 
        for(i=0 ; i<str_len ; i++){
            ret = USART_ASYNC_WriteByteNonBlocking(data[i]);
            if(E_NOT_OK == ret){
                i--;
            }
            else{/* Nothing */}
            if(str_len == i){
                i=0;
            }
            else{/* Nothing */}
        }
    }
    
    return ret;
}


static void USART_Baud_Rate_Calculation(const usart_t *usart){
    float tempbaud=0;
    
    if(BAUDRATE_ASYN_8BIT_lOW_SPEED == usart->baudrate_gen_gonfig){
        TXSTAbits.BRGH=EUSART_ASYNCHRONOUS_LOW_SPEED;
        TXSTAbits.SYNC=EUSART_ASYNCHRONOUS_MODE;
        BAUDCONbits.BRG16=EUSART_08BIT_BAUDRATE_GEN;
        tempbaud=((_XTAL_FREQ/(64*(float)usart->baudrate))-1);
    }
    else if(BAUDRATE_ASYN_8BIT_HIGH_SPEED == usart->baudrate_gen_gonfig){
        TXSTAbits.BRGH=EUSART_ASYNCHRONOUS_HIGH_SPEED;
        TXSTAbits.SYNC=EUSART_ASYNCHRONOUS_MODE;
        BAUDCONbits.BRG16=EUSART_08BIT_BAUDRATE_GEN;
        tempbaud=((_XTAL_FREQ/(16*(float)usart->baudrate))-1);
    }
    else if(BAUDRATE_ASYN_16BIT_lOW_SPEED == usart->baudrate_gen_gonfig){
        TXSTAbits.BRGH=EUSART_ASYNCHRONOUS_LOW_SPEED;
        TXSTAbits.SYNC=EUSART_ASYNCHRONOUS_MODE;
        BAUDCONbits.BRG16=EUSART_16BIT_BAUDRATE_GEN;
        tempbaud=((_XTAL_FREQ/(16*(float)usart->baudrate))-1);
    }
    else if(BAUDRATE_ASYN_16BIT_HIGH_SPEED == usart->baudrate_gen_gonfig){
        TXSTAbits.BRGH=EUSART_ASYNCHRONOUS_HIGH_SPEED;
        TXSTAbits.SYNC=EUSART_ASYNCHRONOUS_MODE;
        BAUDCONbits.BRG16=EUSART_16BIT_BAUDRATE_GEN;
        tempbaud=((_XTAL_FREQ/(4*(float)usart->baudrate))-1);
    }
    else if(BAUDRATE_SYN_8BIT == usart->baudrate_gen_gonfig){
        TXSTAbits.SYNC=EUSART_SYNCHRONOUS_MODE;
        BAUDCONbits.BRG16=EUSART_08BIT_BAUDRATE_GEN;
        tempbaud=((_XTAL_FREQ/(4*(float)usart->baudrate))-1);
    }
    else if(BAUDRATE_SYN_16BIT == usart->baudrate_gen_gonfig){
        TXSTAbits.SYNC=EUSART_SYNCHRONOUS_MODE;
        BAUDCONbits.BRG16=EUSART_16BIT_BAUDRATE_GEN;
        tempbaud=((_XTAL_FREQ/(4*(float)usart->baudrate))-1);
    }
    else{/* Nothing */}
    
    SPBRG=(uint8)((uint16)tempbaud);
    SPBRGH=(uint8)((uint16)tempbaud>>8);
}

static void USART_ASYNC_TX_Init(const usart_t *usart){
    if(EUSART_ASYNCHRONOUS_TX_ENABLE == usart->usart_tx_cfg.usart_tx_enable){
        TXSTAbits.TXEN=EUSART_ASYNCHRONOUS_TX_ENABLE;
    }
    else if(EUSART_ASYNCHRONOUS_TX_DISABLE == usart->usart_tx_cfg.usart_tx_enable){
        TXSTAbits.TXEN=EUSART_ASYNCHRONOUS_TX_DISABLE;
    }
    else{/* Nothing */}
    if(EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE == usart->usart_tx_cfg.usart_tx_9bit_enable){
        TXSTAbits.TX9=EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE;
    }
    else if(EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE == usart->usart_tx_cfg.usart_tx_9bit_enable){
        TXSTAbits.TX9=EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE;
    }
    else{/* Nothing */}
    
#if USART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE == usart->usart_tx_cfg.usart_tx_interrupt_enable){
        USART_TxInterruptHandler=usart->USART_TxDefaultInterruptHandler;
        USART_TX_FlagClear();
        USART_TX_InterruptEnable();
    }
    else{/* Nothing */}
#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE   
    INTERRUPT_PriortyLevelEnable();
    if(INTERRUPT_HIGH_PRIORTY == usart->usart_tx_cfg.usart_tx_int_priority){
        INTERRUPT_GlobalInterruptHighEnable();
    }
    else if(INTERRUPT_LOW_PRIORTY == usart->usart_tx_cfg.usart_tx_int_priority){
        INTERRUPT_GlobalInterruptLowEnable();
    }
    else{/* Nothing */}
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif 
#endif
}

static void USART_ASYNC_RX_Init(const usart_t *usart){
    if(EUSART_ASYNCHRONOUS_RX_ENABLE == usart->usart_rx_cfg.usart_rx_enable){
        RCSTAbits.CREN=EUSART_ASYNCHRONOUS_RX_ENABLE;
    }
    else if(EUSART_ASYNCHRONOUS_RX_DISABLE == usart->usart_rx_cfg.usart_rx_enable){
        RCSTAbits.CREN=EUSART_ASYNCHRONOUS_RX_DISABLE;
    }
    else{/* Nothing */}
    if(EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE == usart->usart_rx_cfg.usart_rx_9bit_enable){
        RCSTAbits.RX9=EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE;
    }
    else if(EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE == usart->usart_rx_cfg.usart_rx_9bit_enable){
        RCSTAbits.RX9=EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE;
    }
    else{/* Nothing */}
    
#if USART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE == usart->usart_rx_cfg.usart_rx_interrupt_enable){
        USART_RxInterruptHandler=usart->USART_RxDefaultInterruptHandler;
        USART_RX_InterruptEnable();
    }
    else{/* Nothing */}
#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE   
    INTERRUPT_PriortyLevelEnable();
    if(INTERRUPT_HIGH_PRIORTY == usart->usart_rx_cfg.usart_rx_int_priority){
        INTERRUPT_GlobalInterruptHighEnable();
    }
    else if(INTERRUPT_LOW_PRIORTY == usart->usart_rx_cfg.usart_rx_int_priority){
        INTERRUPT_GlobalInterruptLowEnable();
    }
    else{/* Nothing */}
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif 
#endif
}
