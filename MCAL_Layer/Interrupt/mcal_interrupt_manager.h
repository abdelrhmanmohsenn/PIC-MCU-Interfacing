/* 
 * File:   mcal_interrupt_manager.h
 * Author: mohsen
 *
 * Created on February 11, 2023, 3:55 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/******* section : Includes *******/
#include "mcal_interrupt_config.h"

/******* section : macros Declarations *******/

/******* section : function-like macros Declarations *******/

/******* section : Data Types Declarations *******/

/******* section : Function Declarations *******/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB4_ISR(uint8 src);
void RB5_ISR(uint8 src);
void RB6_ISR(uint8 src);
void RB7_ISR(uint8 src);

void ADC_ISR(void);

void TMR0_ISR(void);
void TMR1_ISR(void);
void TMR2_ISR(void);
void TMR3_ISR(void);

void CCP1_ISR(void);
void CCP2_ISR(void);

void USART_TX_ISR(void);
void USART_RX_ISR(void);

void SPI_ISR(void);

#endif	/* MCAL_INTERRUPT_MANAGER_H */

