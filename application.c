/*
 * File:   application.c
 * Author: Abdelrhman Mohsen
 *
 * Created on January 27, 2023, 8:22 PM
 */

#include"application.h"

uint8 ack=0 , received_data=0 ,counter=0;

i2c_t i2c_obj={
  .clock_speed=100000,
  .i2c_slew_rate=I2C_SLEW_RATE_DISABLE,
  .mode_select=I2C_MASTER_MODE_DEFINED_CLOCK  
};

i2c_t i2c_slave={
    .clock_speed=100000,
    .i2c_slew_rate=I2C_SLEW_RATE_DISABLE,
    .i2c_slave_address=0x55,
    .mode_select=I2C_SLAVE_MODE_7BIT_ADDRESS
};
       

void main(void){
    
    application_initialize();
    
    /********** MASTER 0**************/
    I2C_master_Init(&i2c_obj);
    MSSP_I2C_Master_Send_Start(&i2c_obj);
    __delay_ms(100);
    MSSP_I2C_Master_Write_NBlocking(&i2c_obj ,0xAB ,&ack);
    __delay_ms(100);
//    MSSP_I2C_Master_Write_NBlocking(&i2c_obj ,0x18 ,&ack);
//    __delay_ms(100);
//    MSSP_I2C_Master_Write_NBlocking(&i2c_obj ,0x5 ,&ack);
//    __delay_ms(100);
    
        
    /********** SLAVE ***************/
//    I2C_slave_Init(&i2c_slave);
//    MSSP_I2C_slave_Write_Blocking(&i2c_slave , 0x18 ,&ack);
//    MSSP_I2C_slave_Read_Blocking(&i2c_slave ,&received_data);
//    MSSP_I2C_slave_Read_Blocking(&i2c_slave ,&received_data);
    while(1){
        MSSP_I2C_Master_Read_NBlocking(&i2c_obj , 1 ,&received_data);
//        __delay_ms(100);
        if(0x18 == received_data && 0 == counter){
            MSSP_I2C_Master_Send_Stop(&i2c_obj);
            return;
        }
        
    }
    
    return;
}

void application_initialize(void){
    
    
}


/***
 
 
char_lcd_4bit_t lcd1={
    .lcd_en     ={.port=PORTC_INDEX, .pin=PIN1, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW},
    .lcd_rs     ={.port=PORTC_INDEX, .pin=PIN0, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW},
    .lcd_data[0]={.port=PORTC_INDEX, .pin=PIN2, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW},
    .lcd_data[1]={.port=PORTC_INDEX, .pin=PIN3, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW},
     .lcd_data[0]={.port=PORTD_INDEX, .pin=PIN0, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW},
    .lcd_data[1]={.port=PORTD_INDEX, .pin=PIN1, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW},
    .lcd_data[2]={.port=PORTD_INDEX, .pin=PIN2, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW},
    .lcd_data[3]={.port=PORTD_INDEX, .pin=PIN3, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW},
    .lcd_data[4]={.port=PORTD_INDEX, .pin=PIN4, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW},
    .lcd_data[5]={.port=PORTD_INDEX, .pin=PIN5, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW},
    .lcd_data[6]={.port=PORTD_INDEX, .pin=PIN6, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW},
    .lcd_data[7]={.port=PORTD_INDEX, .pin=PIN7, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW}
};

char_lcd_8bit_t lcd2={
    .lcd_en     ={.port=PORTC_INDEX, .pin=PIN7, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW},
    .lcd_rs     ={.port=PORTC_INDEX, .pin=PIN6, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW},
    .lcd_data[0]={.port=PORTD_INDEX, .pin=PIN0, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW},
    .lcd_data[1]={.port=PORTD_INDEX, .pin=PIN1, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW},
    .lcd_data[2]={.port=PORTD_INDEX, .pin=PIN2, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW},
    .lcd_data[3]={.port=PORTD_INDEX, .pin=PIN3, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW},
    .lcd_data[4]={.port=PORTD_INDEX, .pin=PIN4, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW},
    .lcd_data[5]={.port=PORTD_INDEX, .pin=PIN5, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW},
    .lcd_data[6]={.port=PORTD_INDEX, .pin=PIN6, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW},
    .lcd_data[7]={.port=PORTD_INDEX, .pin=PIN7, .direction=PIN_DIRECTION_OUTPUT, .logic=PIN_LOW}
};
 
 
 */



/****
 button_state_t btn_state             = BUTTON_RELEASED;
uint16         btn_valid_counter     = 0;
button_state_t btn_valid_status      = BUTTON_RELEASED;
button_state_t btn_valid_last_status = BUTTON_RELEASED;
sint8          led_counter           = -1;
led_t          led1                  = {.port=PORTC_INDEX,.pin=0,.led_status=PIN_LOW};
led_t          previous_led          = {0};
pin_config_t   btn_pin               = {.port=PORTD_INDEX, .pin=PIN7, .direction=PIN_DIRECTION_INPUT };
button_t       btn1                  = {.button_pin=&btn_pin , .button_connection=BUTTON_ACTIVE_LOW ,
                                        .button_state=BUTTON_RELEASED};
relay_t        relay1                = {.port=PORTA_INDEX ,.pin=PIN0 ,.relay_status=RELAY_OFF};
 
led_t led_array[8]={
    {.port=PORTC_INDEX,.pin=0,.led_status=PIN_LOW},
    {.port=PORTC_INDEX,.pin=1,.led_status=PIN_LOW},
    {.port=PORTC_INDEX,.pin=2,.led_status=PIN_LOW},
    {.port=PORTC_INDEX,.pin=3,.led_status=PIN_LOW},
    {.port=PORTC_INDEX,.pin=4,.led_status=PIN_LOW},
    {.port=PORTC_INDEX,.pin=5,.led_status=PIN_LOW},
    {.port=PORTC_INDEX,.pin=6,.led_status=PIN_LOW},
    {.port=PORTC_INDEX,.pin=7,.led_status=PIN_LOW}
};
 
    

 */





/****
 button_read_state(&btn1, &btn_state);
        
        if(BUTTON_PRESSED == btn_state){
            btn_valid_counter++;
            if(btn_valid_counter > 500){
                btn_valid_status = BUTTON_PRESSED;    
            }   
        }
        else{
                btn_valid_status = BUTTON_RELEASED;
                btn_valid_counter=0;
            }
        
        if(btn_valid_last_status != btn_valid_status){
            btn_valid_last_status=btn_valid_status;
            if(btn_valid_status == BUTTON_PRESSED){
                led_counter++;
            }
        }
        
        led1.pin=led_counter;
        if(-1 == led_counter){
            led_turn_off(&led1);
        }
        else if(led1.pin != previous_led.pin){
                if(led_counter > 7){
                    led_counter =-1;
                    led_turn_off(&led1);
                }
                else{
                    led_turn_on(&led1);
                    led_turn_off(&previous_led);
                    previous_led=led1;
                }
        }
        else{
            
        }
 
 
 
 */


/***   WATCH APPLICATION
 * 
 * 
 uint8 seconds=55 , minutes=59 , hours=23;
 
 for(unsigned int counter=0 ; counter<50 ; counter++){
            gpio_port_write(PORTD_INDEX,1);
            gpio_port_write(PORTC_INDEX,(uint8)hours/10);
            __delay_us(3333);
            gpio_port_write(PORTD_INDEX,2);
            gpio_port_write(PORTC_INDEX,(uint8)hours%10);
            __delay_us(3333);
            gpio_port_write(PORTD_INDEX,4);
            gpio_port_write(PORTC_INDEX,(uint8)minutes/10);
            __delay_us(3333);
            gpio_port_write(PORTD_INDEX,8);
            gpio_port_write(PORTC_INDEX,(uint8)minutes%10);
            __delay_us(3333);
            gpio_port_write(PORTD_INDEX,16);
            gpio_port_write(PORTC_INDEX,(uint8)seconds/10);
            __delay_us(3333);
            gpio_port_write(PORTD_INDEX,32);
            gpio_port_write(PORTC_INDEX,(uint8)seconds%10);
            __delay_us(3333);
        }
        seconds++;
        if(seconds == 60){
            minutes++;
            seconds=0;
        }
        if(minutes == 60){
            hours++;
            minutes=0;
        }
        if(hours == 24){
            hours=0;
        }
 
 
 */


/*** KEYPAD INITIALIZE 
 
 keypad_t keypad1={
    .keypad_rows_pins[0]={.port=PORTC_INDEX,.pin=PIN0,.direction=PIN_DIRECTION_OUTPUT,.logic=PIN_LOW},
    .keypad_rows_pins[1]={.port=PORTC_INDEX,.pin=PIN1,.direction=PIN_DIRECTION_OUTPUT,.logic=PIN_LOW},
    .keypad_rows_pins[2]={.port=PORTC_INDEX,.pin=PIN2,.direction=PIN_DIRECTION_OUTPUT,.logic=PIN_LOW},
    .keypad_rows_pins[3]={.port=PORTC_INDEX,.pin=PIN3,.direction=PIN_DIRECTION_OUTPUT,.logic=PIN_LOW},
    .keypad_columns_pins[0]={.port=PORTC_INDEX,.pin=PIN4,.direction=PIN_DIRECTION_INPUT},
    .keypad_columns_pins[1]={.port=PORTC_INDEX,.pin=PIN5,.direction=PIN_DIRECTION_INPUT},
    .keypad_columns_pins[2]={.port=PORTC_INDEX,.pin=PIN6,.direction=PIN_DIRECTION_INPUT},
    .keypad_columns_pins[3]={.port=PORTC_INDEX,.pin=PIN7,.direction=PIN_DIRECTION_INPUT}
};
 
 
 
 */