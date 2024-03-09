/* 
 * File:   ecu_7_segment.c
 * Author: mohsen
 *
 * Created on February 5, 2023, 12:38 PM
 */

#include "ecu_7_segment.h"

/**
 * 
 * @param segment
 * @return 
 */
Std_ReturnType segment_initialize(const segment_t *segment){
    Std_ReturnType ret=E_OK;
    
    if(NULL == segment){
        ret=E_NOT_OK;
    }
    else{
        for(unsigned int i=0 ; i<4 ; i++){
            ret = gpio_pin_initialize(&(segment->segment_pin[i]));
        }
    }
    
    return ret;
}

/**
 * 
 * @param segment
 * @param number
 * @return 
 */
Std_ReturnType segment_write_number(const segment_t *segment, uint8 number){
    Std_ReturnType ret=E_OK;
    
    if(NULL == segment && number > 9){
        ret=E_NOT_OK;
    }
    else{
        for(unsigned int i=0 ; i<4 ; i++){
            ret = gpio_pin_write(&(segment->segment_pin[i]),(number>>i)&0x01);
        }
    }
    
    return ret;
}
