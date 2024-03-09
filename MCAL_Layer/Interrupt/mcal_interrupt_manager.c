/* 
 * File:   mcal_interrupt_manager.c
 * Author: mohsen
 *
 * Created on February 11, 2023, 3:55 PM
 */

#include "mcal_interrupt_manager.h"

#if INTERRUPT_PRIORTY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
void __interrupt() InterruptHighManeger(void){
    if((INTCONbits.INT0IE == 1) && (INTCONbits.INT0IF == 1)){
        INT0_ISR();
    }
    else{/* Do Nothing */}
    if((INTCON3bits.INT2IE == 1) && (INTCON3bits.INT2IF == 1)){
        INT2_ISR();
    }
    else{/* Do Nothing */}
    
    /*******************PORTB_ON_CHANGE_INTERRUPT*************************/
    if((INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1) && (PORTBbits.RB4 == 1)){
        RB4_ISR(1);
    }
    else {/* Do Nothing */}
    if((INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1) && (PORTBbits.RB4 == 0)){
        RB4_ISR(0);
    }
    else{/* Do Nothing */} 
}

void __interrupt(low_priority) InterruptLowManeger(void){
    if((INTCON3bits.INT1IE == 1) && (INTCON3bits.INT1IF == 1)){
        INT1_ISR();
    }
    else{/* Do Nothing */}
}
#else
void __interrupt() InterruptManager(void){
    
    /*******************ADC_INTERRUPT*************************/
    if((1 == PIE1bits.ADIE) && (1 == PIR1bits.ADIF)){
        ADC_ISR();
    }
    else{/* Do Nothing */}
    
    /*******************EXTERNAL_INTERRUPT*************************/
    if((INTCONbits.INT0IE == 1) && (INTCONbits.INT0IF == 1)){
        INT0_ISR();
    }
    else{/* Do Nothing */}
    if((INTCON3bits.INT2IE == 1) && (INTCON3bits.INT2IF == 1)){
        INT1_ISR();
    }
    else{/* Do Nothing */}
    if((INTCON3bits.INT1IE == 1) && (INTCON3bits.INT1IF == 1)){
        INT2_ISR();
    }
    else{/* Do Nothing */}
    
    /****************PORTB_ON_CHANGE_INTERRUPT**********************/
    if((INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1)){
        RB4_ISR(1);
    }
    else {/* Do Nothing */}
    if((INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1)){
        RB4_ISR(0);
    }
    else{/* Do Nothing*/ }
    
    /*******************TIMERS_INTERRUPT*************************/
    if((T0CONbits.TMR0ON == 1) && (INTCONbits.TMR0IF == 1)){
        TMR0_ISR();
    }
    else {/* Do Nothing */}
    if((PIE1bits.TMR1IE == 1) && (PIR1bits.TMR1IF == 1)){
        TMR1_ISR();
    }
    else {/* Do Nothing */}
    if((PIE1bits.TMR2IE == 1) && (PIR1bits.TMR2IF == 1)){
        TMR2_ISR();
    }
    else {/* Do Nothing */}
    if((PIE2bits.TMR3IE == 1) && (PIR2bits.TMR3IF == 1)){
        TMR3_ISR();
    }
    else {/* Do Nothing */}
    
    /*******************CCP_INTERRUPT*************************/
    if((PIE1bits.CCP1IE == 1) && (PIR1bits.CCP1IF == 1)){
        CCP1_ISR();
    }
    else {/* Do Nothing */}
    if((PIE2bits.CCP2IE == 1) && (PIR2bits.CCP2IF == 1)){
        CCP2_ISR();
    }
    else {/* Do Nothing */}
    
    /*******************USART_INTERRUPT*************************/
    if((PIE1bits.TXIE == 1) && (PIR1bits.TXIF == 1)){
        USART_TX_ISR();
    }
    else {/* Do Nothing */}
    if((PIE1bits.RCIE == 1) && (PIR1bits.RCIF == 1)){
        USART_RX_ISR();
    }
    else {/* Do Nothing */}
    
    /*******************SPI_INTERRUPT*************************/
    if((PIE1bits.SSPIE == 1) && (PIR1bits.SSPIF == 1)){
        SPI_ISR();
    }
    else {/* Do Nothing */}
}
#endif