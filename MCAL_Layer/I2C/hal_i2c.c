/* 
 * File:   hal_i2c.c
 * Author: mohsen
 *
 * Created on March 16, 2023, 5:11 PM
 */

#include "hal_i2c.h"

static void inline pin_cfg();

Std_ReturnType I2C_master_Init(const i2c_t *i2c_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == i2c_obj){
        ret=E_NOT_OK;
    }
    else{ 
        MSSP_MODULE_DISABLE_CFG();
        I2C_MODE_SELECT(i2c_obj->mode_select);
        SSPADD = (uint8)((_XTAL_FREQ / (4.0 * i2c_obj->clock_speed)) - 1);
        PIN_CFG();
        if(I2C_SLEW_RATE_ENABLE == i2c_obj->i2c_slew_rate){
            I2C_SLEW_RATE_ENABLE_CFG();
        }
        else if(I2C_SLEW_RATE_DISABLE == i2c_obj->i2c_slew_rate){
            I2C_SLEW_RATE_DISABLE_CFG();
        }
        else{ /* Nothing */ }
        if(I2C_SMBus_ENABLE == i2c_obj->i2c_slew_rate){
            I2C_SMBus_ENABLE_CFG();
        }
        else if(I2C_SMBus_DISABLE == i2c_obj->i2c_slew_rate){
            I2C_SMBus_DISABLE_CFG();
        }
        else{ /* Nothing */ };
        MSSP_MODULE_ENABLE_CFG();
    }
    
    return ret;
}

Std_ReturnType I2C_slave_Init(const i2c_t *i2c_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == i2c_obj){
        ret=E_NOT_OK;
    }
    else{ 
        MSSP_MODULE_DISABLE_CFG();
        I2C_MODE_SELECT(i2c_obj->mode_select);
        PIN_CFG();
        if(I2C_SLEW_RATE_ENABLE == i2c_obj->i2c_slew_rate){
            I2C_SLEW_RATE_ENABLE_CFG();
        }
        else if(I2C_SLEW_RATE_DISABLE == i2c_obj->i2c_slew_rate){
            I2C_SLEW_RATE_DISABLE_CFG();
        }
        else{ /* Nothing */ }
        if(I2C_SMBus_ENABLE == i2c_obj->i2c_slew_rate){
            I2C_SMBus_ENABLE_CFG();
        }
        else if(I2C_SMBus_DISABLE == i2c_obj->i2c_slew_rate){
            I2C_SMBus_DISABLE_CFG();
        }
        else{ /* Nothing */ };
        if(I2C_GENERAL_CALL_ENABLE == i2c_obj->i2c_general_call){
            I2C_GENERAL_CALL_ENABLE_CFG();
        }
        else if(I2C_GENERAL_CALL_DISABLE == i2c_obj->i2c_general_call){
            I2C_GENERAL_CALL_DISABLE_CFG();
        }
        else{ /* Nothing */ };
        SSPADD=(uint8)(i2c_obj->i2c_slave_address<<1);
        MSSP_MODULE_ENABLE_CFG();
    }
    
    return ret;
}

Std_ReturnType I2C_DeInit(const i2c_t *i2c_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == i2c_obj){
        ret=E_NOT_OK;
    }
    else{ 
        MSSP_MODULE_DISABLE_CFG();
    }
    
    return ret;
}


Std_ReturnType MSSP_I2C_Master_Write_Blocking(const i2c_t *i2c_obj, uint8 i2c_data, uint8 *_ack){
    Std_ReturnType ret=E_OK;
    
    if(NULL == i2c_obj || NULL == _ack){
        ret=E_NOT_OK;
    }
    else{
        SSPBUF = i2c_data;
        while(SSPSTATbits.BF);
        PIR1bits.SSPIF = 0;
        if(I2C_ACK_RECEIVED_FROM_SLAVE == SSPCON2bits.ACKDT){
            *_ack=I2C_ACK_RECEIVED_FROM_SLAVE;
        }
        else if(I2C_ACK_NOT_RECEIVED_FROM_SLAVE == SSPCON2bits.ACKDT){
            *_ack=I2C_ACK_NOT_RECEIVED_FROM_SLAVE;
            ret=E_NOT_OK;
        }
        else{ /* Nothing */ }
    }
    
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Read_Blocking(const i2c_t *i2c_obj, uint8 ack, uint8 *i2c_data){
    Std_ReturnType ret=E_OK;
    
    if(NULL == i2c_obj || NULL == i2c_data){
        ret=E_NOT_OK;
    }
    else{
        I2C_MASTER_RECEIVE_ENABLE_CFG();
        while(!SSPSTATbits.BF);
        *i2c_data=SSPBUF;
        PIR1bits.SSPIF = 0;
        I2C_MASTER_RECEIVE_DISABLE_CFG();
        if(I2C_MASTER_SEND_ACK == ack){
            SSPCON2bits.ACKDT=I2C_MASTER_SEND_ACK;
            I2C_MASTER_ACK_BIT_SEND();
            while(SSPCON2bits.ACKEN);
        }
        else if(I2C_MASTER_SEND_NACK == ack){
            SSPCON2bits.ACKDT=I2C_MASTER_SEND_NACK;
            I2C_MASTER_ACK_BIT_SEND();
            while(SSPCON2bits.ACKEN);
        }
        else{ /* Nothing */ }
    }
    
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Write_NBlocking(const i2c_t *i2c_obj, uint8 i2c_data, uint8 *_ack){
    Std_ReturnType ret=E_OK;
    
    if(NULL == i2c_obj || NULL == _ack){
        ret=E_NOT_OK;
    }
    else{
        if(1 == PIR1bits.SSPIF){
            PIR1bits.SSPIF = 0;
        }
        else{ /* Nothing */ }
        if(0 == SSPSTATbits.BF){
            SSPBUF = i2c_data;
            if(I2C_ACK_RECEIVED_FROM_SLAVE == SSPCON2bits.ACKDT){
                *_ack=I2C_ACK_RECEIVED_FROM_SLAVE;
            }
            else if(I2C_ACK_NOT_RECEIVED_FROM_SLAVE == SSPCON2bits.ACKDT){
                *_ack=I2C_ACK_NOT_RECEIVED_FROM_SLAVE;
                ret=E_NOT_OK;
            }
            else{ /* Nothing */ }
        }
        else{
            ret=E_NOT_OK;
        }
    }
    
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Read_NBlocking(const i2c_t *i2c_obj, uint8 ack, uint8 *i2c_data){
    Std_ReturnType ret=E_OK;
    
    if(NULL == i2c_obj || NULL == i2c_data){
        ret=E_NOT_OK;
    }
    else{
        I2C_MASTER_RECEIVE_ENABLE_CFG();
        if(1 == PIR1bits.SSPIF && 1 == SSPSTATbits.BF){
            *i2c_data=SSPBUF;
            I2C_MASTER_RECEIVE_DISABLE_CFG();
            if(I2C_MASTER_SEND_ACK == ack){
                SSPCON2bits.ACKDT=I2C_MASTER_SEND_ACK;
                I2C_MASTER_ACK_BIT_SEND();
            }
            else if(I2C_MASTER_SEND_NACK == ack){
                SSPCON2bits.ACKDT=I2C_MASTER_SEND_NACK;
                I2C_MASTER_ACK_BIT_SEND();
            }
            else{ /* Nothing */ }
        }
    }
    
    return ret;
}

Std_ReturnType MSSP_I2C_slave_Write_Blocking(const i2c_t *i2c_obj, uint8 i2c_data, uint8 *_ack){
    Std_ReturnType ret=E_OK;
    
    if(NULL == i2c_obj || NULL == _ack){
        ret=E_NOT_OK;
    }
    else{ 
        while(!PIR1bits.SSPIF);
        PIR1bits.SSPIF=0;
        if(I2C_SLAVE_SEND_DATA == SSPSTATbits.RW){
            SSPBUF=i2c_data;
            SSPCON1bits.CKP=1;
            while(!SSPSTATbits.BF);
        }
        
    }
    
    return ret;
}

Std_ReturnType MSSP_I2C_slave_Read_Blocking(const i2c_t *i2c_obj, uint8 *i2c_data){
    Std_ReturnType ret=E_OK;
    
    if(NULL == i2c_obj || NULL == i2c_data){
        ret=E_NOT_OK;
    }
    else{
        if(0 == SSPSTATbits.DA){
            while(!PIR1bits.SSPIF);
            PIR1bits.SSPIF=0;
            *i2c_data=SSPBUF;
        }
        else{ /* Nothing */ }
        while(!PIR1bits.SSPIF);
        PIR1bits.SSPIF=0;
        if(1 == SSPSTATbits.DA && I2C_SLAVE_RECEIVE_DATA == SSPSTATbits.RW){
            *i2c_data=SSPBUF;
            SSPCON1bits.CKP=1;
        }
    }
    
    return ret;
}

Std_ReturnType MSSP_I2C_slave_Write_NBlocking(const i2c_t *i2c_obj, uint8 i2c_data, uint8 *_ack){
    Std_ReturnType ret=E_OK;
    
    if(NULL == i2c_obj || NULL == _ack){
        ret=E_NOT_OK;
    }
    else{ 
        if(1 == PIR1bits.SSPIF){
            PIR1bits.SSPIF=0;
            if(0 == SSPCON1bits.WCOL && I2C_SLAVE_SEND_DATA == SSPSTATbits.RW){
                SSPBUF=i2c_data;
                SSPCON1bits.CKP=1;
            }
        }
        else{ /* Nothing */ }
    }
    
    return ret;
}

Std_ReturnType MSSP_I2C_slave_Read_NBlocking(const i2c_t *i2c_obj, uint8 *i2c_data){
    Std_ReturnType ret=E_OK;
    
    if(NULL == i2c_obj || NULL == i2c_data){
        ret=E_NOT_OK;
    }
    else{ 
        if(0 == SSPSTATbits.DA){
            PIR1bits.SSPIF=0;
            *i2c_data=SSPBUF;
        }
        else{ /* Nothing */ }
        if(1 == SSPSTATbits.DA && I2C_SLAVE_RECEIVE_DATA == SSPSTATbits.RW){
            PIR1bits.SSPIF=0;
            *i2c_data=SSPBUF;
            SSPCON1bits.CKP=1;
        }
    }
    
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Start(const i2c_t *i2c_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == i2c_obj){
        ret=E_NOT_OK;
    }
    else{ 
        I2C_MASTER_SEND_START();
        while(SSPCON2bits.SEN);
        PIR1bits.SSPIF = 0;
        if(I2C_START_BIT_DETECTED == SSPSTATbits.S){
            ret = E_OK; 
        }
        else{
            ret = E_NOT_OK; 
        }
    }
    
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const i2c_t *i2c_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == i2c_obj){
        ret=E_NOT_OK;
    }
    else{ 
        I2C_MASTER_SEND_REPEAT_START();
        while(SSPCON2bits.RSEN);
        PIR1bits.SSPIF = 0;
        if(I2C_START_BIT_DETECTED == SSPSTATbits.S){
            ret = E_OK; 
        }
        else{
            ret = E_NOT_OK; 
        }
    }
    
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Stop(const i2c_t *i2c_obj){
    Std_ReturnType ret=E_OK;
    
    if(NULL == i2c_obj){
        ret=E_NOT_OK;
    }
    else{ 
        I2C_MASTER_SEND_STOP();
        while(SSPCON2bits.PEN);
        PIR1bits.SSPIF = 0;
        if(I2C_START_BIT_DETECTED == SSPSTATbits.P){
            ret = E_OK; 
        }
        else{
            ret = E_NOT_OK; 
        }
    }
    
    return ret;
}

