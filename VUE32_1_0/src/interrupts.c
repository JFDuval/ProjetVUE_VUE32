#include "def.h"

volatile unsigned int flag_timer1_100us = 0;

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                         Interruptions                                    //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////



//Timer 1 - Main timebase 100µs - 10kHz
void __ISR(_TIMER_1_VECTOR, ipl3) isr_timer1(void)
{
    static unsigned int led_cnt = 0;
    static unsigned int tmb_cnt = 0;

    led_cnt++;
    if(led_cnt > 1500)
    {
        led_cnt = 0;
        LED1 ^= 1;          //Toggle
    }

    tmb_cnt++;
    if(tmb_cnt > 10)
    {
        tmb_cnt = 0;
        //1ms
    }

    //Sample ADC
    AD1CON1bits.ASAM = 1;   // Start sampling

    //Clear flag and return
    IFS0bits.T1IF = 0;
}

//Timer 3 - PWM - 20kHz
void __ISR(_TIMER_3_VECTOR, ipl3) isr_timer3 (void)
{
    //Should not happen...
    
    IFS0bits.T3IF = 0;           // Clearing Timer3 interrupt flag
}

//Timer 4
void __ISR(_TIMER_4_VECTOR, ipl4) isr_timer4(void)
{
    /*
	//ToDo
    //Shouldn't happen, error
    TMR4=0;
    speed[0] =0 ;
    speed[0] = 0 ;
    IFS0CLR = _IFS0_T4IF_MASK;
     */
}

//Change notification
void __ISR(_CHANGE_NOTICE_VECTOR, ipl4) CNHandler(void)
{
/*
    if (!SPDO2)	//CN0 down
    {
        speed[0]=CONV_SPEED(unTimer4Value[0]+TMR4);
        unTimer4Value[1]+=TMR4;
        unTimer4Value[0]=0;
    }
    if (!SPDO1)	//CN1 down
    {
        speed[1]=CONV_SPEED(unTimer4Value[1]+TMR4);
        unTimer4Value[0]+=TMR4;
        unTimer4Value[1]=0;
    }
    TMR4=0;
 *
 * */
    IFS1CLR = _IFS1_CNIF_MASK;
}