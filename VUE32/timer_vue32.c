
#include "timer_vue32.h"

void __ISR(_TIMER_1_VECTOR, ipl3) FCT_Timer1_Handler(void){
//     asm volatile ("ei");

     IFS0CLR = _IFS0_T1IF_MASK;
     unGlobalTimestamp += 1;

}

void Fct_Timer1_init(void){
    // Init sampler timer
    T1CON = 0x0000;                 // clear registers
    T1CONbits.TGATE = 0;            
    T1CONbits.TCS = 0;              // 1 = external clock from pin T1CK
    T1CONbits.TCKPS = 3;            //256 divider
    TMR1 = 0;                               // zero timer
    PR1 = 3125;                               // set period register for 80 MHz / (256*100) = 3125 = ~10ms sample rate;
    IFS0bits.T1IF = 0;              // clear interrupt flag
    IPC1bits.T1IP = 3;              // interrupt priority
    IEC0bits.T1IE = 1;              // enable interrupt
    T1CONbits.ON = 1;               // start timer
}
