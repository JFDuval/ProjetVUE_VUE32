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
    init_timer2();
    init_timer3();
    init_timer4();
    init_timer5();
}

//Main timebase - 100탎 - 10kHz
void init_timer1(void)
{
    T1CON = 0x0000;                 // clear registers
    T1CONbits.TGATE = 0;            
    T1CONbits.TCS = 0;              // 1 = external clock from pin T1CK
    T1CONbits.TCKPS = 1;            // 8 Prescaler
    TMR1 = 0;                       // zero timer
    PR1 = 1000;                     // 100탎
    IFS0bits.T1IF = 0;              // clear interrupt flag
    IPC1bits.T1IP = 3;              // interrupt priority		//ToDo
    IEC0bits.T1IE = 1;              // enable interrupt
    T1CONbits.ON = 1;               // start timer
}

//Input capture (speed sensor SPDO2) - 3.2탎/tick
void init_timer2(void)
{
    //Configure Timer 2
    T2CONbits.ON = 0;			// Off
    T2CONbits.SIDL = 0;    		// continue operation while CPU is IDLE
    T2CONbits.TCKPS = 7;    		// prescaler value =2^(TCKPS+1) = 128
    //T4CONbits.TCS = 0;      		// Internal clock (1= external clock)
    T2CONbits.T32 = 0;       		// 16-bit Timer
    PR2 = 20000;			// 20000*3.2탎 = 64ms
    TMR2 = 0;
    T2CONbits.ON = 1;			// On
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

//Input capture (speed sensor SPDO1) - 3.2탎/tick
void init_timer4(void)
{
    //Configure Timer 4
    T4CONbits.ON = 0;			// Off
    T4CONbits.SIDL = 0;    		// continue operation while CPU is IDLE
    T4CONbits.TCKPS = 7;    		// prescaler value =2^(TCKPS+1) = 128
    //T4CONbits.TCS = 0;      		// Internal clock (1= external clock)
    T4CONbits.T32 = 0;       		// 16-bit Timer
    PR4 = 20000;			// 20000*3.2탎 = 64ms
    TMR4 = 0;
    T4CONbits.ON = 1;			// On
}

//Custom 2-bit 20kHz PWM for Power out 4
void init_timer5(void)
{
    //Configure Timer 5 - 80kHz, 16bits
    T5CONbits.ON = 0;			// Off
    T5CONbits.SIDL = 0;    		// continue operation while CPU is IDLE
    T5CONbits.TCKPS = 0;    		// prescaler value =2^(TCKPS+1) = 0
    PR5 = 1000;				// 80MHz/80kHz = 1000
    IFS0bits.T5IF = 0;			// clear interrupt flag
    IPC5bits.T5IP = 3;			// Set T5 interrupt priority to 0
    IEC0bits.T5IE = 1;			// Enable interrupts
    T5CONbits.ON = 1;			// On
}