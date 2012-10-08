#include <p32xxxx.h>
#include <plib.h>
#include <sys/kmem.h>

// Global timestamp, should only be accessed with a function call (TODO)
volatile unsigned int uiTimeStamp = 0;

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                         Interruptions                                    //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

//Timer 1 - Main timebase 100µs - 10kHz
void __ISR(_TIMER_1_VECTOR, ipl3) isr_timer1(void)
{
    static unsigned int time_cnt = 0;

    //1ms - 1000Hz (timestamp)
    time_cnt++;
    if(time_cnt > 10)
    {
        time_cnt = 0;
        uiTimeStamp++;
    }

    //Clear flag and return
    IFS0bits.T1IF = 0;
}

//Timer 2
void __ISR(_TIMER_2_VECTOR, ipl1) isr_timer2(void)
{
    //Shouldn't happen, error

    IFS0bits.T2IF = 0;           // Clear interrupt flag
}

//Timer 3 - PWM - 20kHz
void __ISR(_TIMER_3_VECTOR, ipl3) isr_timer3 (void)
{
    //Should not happen...
    
    IFS0bits.T3IF = 0;           // Clear interrupt flag
}

//Timer 4
void __ISR(_TIMER_4_VECTOR, ipl1) isr_timer4(void)
{
    //Shouldn't happen, error

    IFS0bits.T4IF = 0;           // Clear interrupt flag
}

//Timer 5 - Custom PWM for output 4 - Wheel sensors
void __ISR(_TIMER_5_VECTOR, ipl4) isr_timer5(void)
{
    // PWM?

    IFS0bits.T5IF = 0;           // Clear interrupt flag
}
