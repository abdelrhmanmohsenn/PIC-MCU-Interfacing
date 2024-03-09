/*
 * File:   application.c
 * Author: Abdelrhman Mohsen
 *
 * Created on January 27, 2023, 8:22 PM
 */

#include"application.h"

void main(void){
    
    
    while(1){
        led_toggle(&led1); //API used from the LED driver
		__delay_ms(500);
        
    }
    
    return;
}

void application_initialize(void){
	
	Std_ReturnType ret = E_NOT_OK;
    led_t led1 = {.port = PORTC_INDEX, .pin = PIN0, .led_status = PIN_LOW};
}
