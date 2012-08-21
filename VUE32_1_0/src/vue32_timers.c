#include "vue32_timers.h"
#include "def.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                    Constants and variables                               //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                          Functions                                       //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

//Initialize all the timers
void init_timers(void)
{
    init_timer1();
    init_timer3();
    init_timer4();
}

//Main timebase - 100µs - 10kHz
void init_timer1(void)
{
    T1CON = 0x0000;                 // clear registers
    T1CONbits.TGATE = 0;            
    T1CONbits.TCS = 0;              // 1 = external clock from pin T1CK
    T1CONbits.TCKPS = 1;            // 8 Prescaler
    TMR1 = 0;                       // zero timer
    PR1 = 1000;                     // 100µs
    IFS0bits.T1IF = 0;              // clear interrupt flag
    IPC1bits.T1IP = 3;              // interrupt priority		//ToDo
    IEC0bits.T1IE = 1;              // enable interrupt
    T1CONbits.ON = 1;               // start timer
}

//Output compare (motor PWM) - 20kHz
void init_timer3(void)
{
    T3CONbits.ON =0;
    T3CONbits.SIDL = 0 ;            // continue operation while CPU is IDLE
    T3CONbits.TCKPS = 0;            // prescaler value = 2^(TCKPS) = 0
        //T3CONbits.TCS = 0;        // clock (1= external clock)
    IFS0bits.T3IF = 0;              // clear interrupt flag
    IPC3bits.T3IP = 3;              // Set T3 interrupt priority to 7
    IEC0bits.T3IE = 0;              // Disable interrupts
    PR3 = 4000;                     // PWM_frequency compared to time base
    T3CONbits.ON = 1;               // Activate Timer3
}

//Input capture (speed sensor) - 3.2µs/tick
void init_timer4(void)
{
    //Configure Timer 4
    T4CONbits.SIDL = 0;    		// continue operation while CPU is IDLE
    T4CONbits.TCKPS = 7;    		// prescaler value =2^(TCKPS+1) = 128
    //T4CONbits.TCS = 0;      		// Internal clock (1= external clock)
    T4CONbits.T32 = 0;       		// 16-bit Timer	
    T4CONbits.ON = 1;
}