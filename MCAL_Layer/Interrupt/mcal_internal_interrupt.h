/* 
 * File:   mcal_internal_interrupt.h
 * Author: mohsen
 *
 * Created on February 11, 2023, 3:59 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

#include "mcal_interrupt_config.h"

/******* section : Includes *******/

/******* section : macros Declarations *******/

/******* section : function-like macros Declarations *******/

/********************ADC INTERRUPT***********************/
/* This routine clears the interrupt Flag for the ADC */
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define ADC_FlagClear()                 (PIR1bits.ADIF=0)
/* This routine sets the interrupt enable for the ADC */
#define ADC_InterruptEnable()           (PIE1bits.ADIE=1)
/* This routine clears the interrupt enable for the ADC */
#define ADC_InterruptDisable()          (PIE1bits.ADIE=0)

#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the ADC Interrupt Priority to be High priority */
#define ADC_PriorityHigh()                 (IPR1bits.ADIP=1)
/* This routine set the ADC Interrupt Priority to be Low priority */
#define ADC_PriorityLow()                  (IPR1bits.ADIP=0)
#endif
#endif

/********************TMR0 INTERRUPT***********************/
/* This routine clears the interrupt Flag for the TMR0 */
#if TMR0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define TMR0_FlagClear()                 (INTCONbits.TMR0IF=0)
/* This routine sets the interrupt enable for the TMR0 */
#define TMR0_InterruptEnable()           (INTCONbits.TMR0IE=1)
/* This routine clears the interrupt enable for the TMR0 */
#define TMR0_InterruptDisable()          (INTCONbits.TMR0IE=0)

#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the TMR0 Interrupt Priority to be High priority */
#define TMR0_PriorityHigh()                 (INTCON2bits.TMR0IP=1)
/* This routine set the TMR0 Interrupt Priority to be Low priority */
#define TMR0_PriorityLow()                  (INTCON2bits.TMR0IP=0)
#endif
#endif

/********************TMR1 INTERRUPT***********************/
/* This routine clears the interrupt Flag for the TMR1 */
#if TMR1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define TMR1_FlagClear()                 (PIR1bits.TMR1IF=0)
/* This routine sets the interrupt enable for the TMR1 */
#define TMR1_InterruptEnable()           (PIE1bits.TMR1IE=1)
/* This routine clears the interrupt enable for the TMR1 */
#define TMR1_InterruptDisable()          (PIE1bits.TMR1IE=0)

#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the TMR1 Interrupt Priority to be High priority */
#define TMR1_PriorityHigh()                 (IPR1bits.TMR1IP=1)
/* This routine set the TMR1 Interrupt Priority to be Low priority */
#define TMR1_PriorityLow()                  (IPR1bits.TMR1IP=0)
#endif
#endif

/********************TMR2 INTERRUPT***********************/
/* This routine clears the interrupt Flag for the TMR1 */
#if TMR2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define TMR2_FlagClear()                 (PIR1bits.TMR2IF=0)
/* This routine sets the interrupt enable for the TMR2 */
#define TMR2_InterruptEnable()           (PIE1bits.TMR2IE=1)
/* This routine clears the interrupt enable for the TMR2 */
#define TMR2_InterruptDisable()          (PIE1bits.TMR2IE=0)

#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the TMR1 Interrupt Priority to be High priority */
#define TMR2_PriorityHigh()                 (IPR1bits.TMR2IP=1)
/* This routine set the TMR1 Interrupt Priority to be Low priority */
#define TMR2_PriorityLow()                  (IPR1bits.TMR2IP=0)
#endif
#endif

/********************TMR3 INTERRUPT***********************/
/* This routine clears the interrupt Flag for the TMR3 */
#if TMR2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define TMR3_FlagClear()                    (PIR2bits.TMR3IF=0)
/* This routine sets the interrupt enable for the TMR3 */
#define TMR3_InterruptEnable()              (PIE2bits.TMR3IE=1)
/* This routine clears the interrupt enable for the TMR3 */
#define TMR3_InterruptDisable()             (PIE2bits.TMR3IE=0)

#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the TMR3 Interrupt Priority to be High priority */
#define TMR3_PriorityHigh()                 (IPR2bits.TMR3IP=1)
/* This routine set the TMR3 Interrupt Priority to be Low priority */
#define TMR3_PriorityLow()                  (IPR2bits.TMR3IP=0)
#endif
#endif

/********************CCP1 INTERRUPT***********************/
/* This routine clears the interrupt Flag for the CCP1 */
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define CCP1_FlagClear()                    (PIR1bits.CCP1IF=0)
/* This routine sets the interrupt enable for the CCP1 */
#define CCP1_InterruptEnable()              (PIE1bits.CCP1IE=1)
/* This routine clears the interrupt enable for the CCP1 */
#define CCP1_InterruptDisable()             (PIE1bits.CCP1IE=0)

#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the CCP1 Interrupt Priority to be High priority */
#define CCP1_PriorityHigh()                 (IPR1bits.CCP1IP=1)
/* This routine set the CCP1 Interrupt Priority to be Low priority */
#define CCP1_PriorityLow()                  (IPR1bits.CCP1IP=0)
#endif
#endif

/********************CCP2 INTERRUPT***********************/
/* This routine clears the interrupt Flag for the CCP2 */
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define CCP2_FlagClear()                    (PIR2bits.CCP2IF=0)
/* This routine sets the interrupt enable for the CCP2 */
#define CCP2_InterruptEnable()              (PIE2bits.CCP2IE=1)
/* This routine clears the interrupt enable for the CCP2 */
#define CCP2_InterruptDisable()             (PIE2bits.CCP2IE=0)

#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the CCP2 Interrupt Priority to be High priority */
#define CCP2_PriorityHigh()                 (IPR2bits.CCP2IP=1)
/* This routine set the CCP2 Interrupt Priority to be Low priority */
#define CCP2_PriorityLow()                  (IPR2bits.CCP2IP=0)
#endif
#endif

/********************USART_TX INTERRUPT***********************/
/* This routine clears the interrupt Flag for the USART_TX */
#if USART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define USART_TX_FlagClear()                    (PIR1bits.TXIF=0)
/* This routine sets the interrupt enable for the USART_TX */
#define USART_TX_InterruptEnable()              (PIE1bits.TXIE=1)
/* This routine clears the interrupt enable for the USART_TX */
#define USART_TX_InterruptDisable()             (PIE1bits.TXIE=0)

#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the USART_TX Interrupt Priority to be High priority */
#define USART_TX_PriorityHigh()                 (IPR1bits.TXIP=1)
/* This routine set the USART_TX Interrupt Priority to be Low priority */
#define USART_TX_PriorityLow()                  (IPR1bits.TXIP=0)
#endif
#endif

/********************USART_RX INTERRUPT***********************/
#if USART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine sets the interrupt enable for the USART_RX */
#define USART_RX_InterruptEnable()              (PIE1bits.RCIE=1)
/* This routine clears the interrupt enable for the USART_RX */
#define USART_RX_InterruptDisable()             (PIE1bits.RCIE=0)

#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the USART_RX Interrupt Priority to be High priority */
#define USART_TX_PriorityHigh()                 (IPR1bits.RCIP=1)
/* This routine set the USART_RX Interrupt Priority to be Low priority */
#define USART_TX_PriorityLow()                  (IPR1bits.RCIP=0)
#endif
#endif

/********************SPI_INTERRUPT***********************/
#if SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define SPI_FlagClear()                    (PIR1bits.SSPIF=0)
/* This routine sets the interrupt enable for the SPI */
#define SPI_InterruptEnable()              (PIE1bits.SSPIE=1)
/* This routine clears the interrupt enable for the SPI */
#define SPI_InterruptDisable()             (PIE1bits.SSPIE=0)

#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the SPI Interrupt Priority to be High priority */
#define SPI_PriorityHigh()                 (IPR1bits.SSPIP=1)
/* This routine set the SPI Interrupt Priority to be Low priority */
#define SPI_PriorityLow()                  (IPR1bits.SSPIP=0)
#endif
#endif

/******* section : Data Types Declarations *******/

/******* section : Function Declarations *******/

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

