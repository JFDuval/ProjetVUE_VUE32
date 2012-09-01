#include "def.h"

//"The user-selectable priority levels range from 1 (lowest) to 7 (highest)."

volatile unsigned int flag_timer1_100us = 0;

//power_out.c
extern unsigned int PWR4_enable;
extern unsigned int pwr4_pwm_dc;

//wheel_sensor.c
extern unsigned int last_spdo1, last_spdo2;

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
//    AD1CON1bits.SAMP = 1;   // Start sampling

    //Wheel sensors:
    last_spdo1 = SPDO1;
    last_spdo2 = SPDO2;

    //Clear flag and return
    IFS0bits.T1IF = 0;
}

//Timer 3 - PWM - 20kHz
void __ISR(_TIMER_3_VECTOR, ipl3) isr_timer3 (void)
{
    //Should not happen...
    
    IFS0bits.T3IF = 0;           // Clearing Timer3 interrupt flag
}

//Timer 2
void __ISR(_TIMER_2_VECTOR, ipl4) isr_timer2(void)
{
    //Shouldn't happen, error
}

//Timer 4
void __ISR(_TIMER_4_VECTOR, ipl4) isr_timer4(void)
{
    //Shouldn't happen, error
}

//Timer 5 - Custom PWM for output 4
void __ISR(_TIMER_5_VECTOR, ipl4) isr_timer5(void)
{
    static unsigned int diy_pwm_cnt = 0;

    diy_pwm_cnt = (diy_pwm_cnt + 1) % 5;

    if((pwr4_pwm_dc >= diy_pwm_cnt) && (PWR4_enable == 1))
	PWR4 = 1;
    else
	PWR4 = 0;

    IFS0CLR = _IFS0_T5IF_MASK;
}
