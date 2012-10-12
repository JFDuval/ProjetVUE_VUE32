#include "def.h"

//"The user-selectable priority levels range from 1 (lowest) to 7 (highest)."

volatile unsigned int flag_timer1_100us = 0;
volatile unsigned int flag_1ms_a = 0, flag_1ms_b = 0;
volatile unsigned char spd1_moving = 0, spd2_moving = 0;

//power_out.c
extern unsigned int PWR4_enable;
extern unsigned int pwr4_pwm_dc;

//wheel_sensor.c
extern unsigned int last_spdo1, last_spdo2;
extern volatile unsigned char pulses_spd1, pulses_spd2;

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                         Interruptions                                    //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

//Timer 1 - Main timebase 100µs - 10kHz
void __ISR(_TIMER_1_VECTOR, ipl3) isr_timer1(void)
{
    static unsigned int led_cnt = 0;
    static unsigned int tmb_a_cnt = 0, tmb_b_cnt = 4;
    static unsigned int tmb_moving = 0;
    static unsigned int last_pulses_spd1 = 0, last_pulses_spd2 = 0;

    //125ms - 8Hz
    led_cnt++;
    if(led_cnt > 1250)
    {
        led_cnt = 0;
        LED1 ^= 1;  //Toggle LED 4Hz
    }

    //1ms Time base A
    tmb_a_cnt++;
    if(tmb_a_cnt > 10)
    {
	flag_1ms_a = 1;
        tmb_a_cnt = 0;
    }

    //1ms Time base B
    tmb_b_cnt++;
    if(tmb_b_cnt > 10)
    {
	flag_1ms_b = 1;
        tmb_b_cnt = 0;
    }

    //20ms - Is the wheel moving?
    tmb_moving++;
    if(tmb_moving > 200)
    {
	if(last_pulses_spd1 == pulses_spd1)
	    spd1_moving = 0;
	else
	    spd1_moving = 1;
	if(last_pulses_spd2 == pulses_spd2)
	    spd2_moving = 0;
	else
	    spd2_moving = 1;

	last_pulses_spd1 = pulses_spd1;
	last_pulses_spd2 = pulses_spd2;

        tmb_moving = 0;
    }

    //Wheel sensors (needed for the edge detection):
    last_spdo1 = SPDO1;
    last_spdo2 = SPDO2;


    //Clear flag and return
    IFS0bits.T1IF = 0;
}

//Timer 3 - PWM - 20kHz
void __ISR(_TIMER_3_VECTOR, ipl3) isr_timer3 (void)
{
    //Should not happen...
    
    IFS0bits.T3IF = 0;           // Clear interrupt flag
}

//Timer 2
void __ISR(_TIMER_2_VECTOR, ipl1) isr_timer2(void)
{
    //Shouldn't happen, error

    IFS0bits.T2IF = 0;           // Clear interrupt flag
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
    static unsigned int diy_pwm_cnt = 0;

    //PWM:
    diy_pwm_cnt = (diy_pwm_cnt + 1) % 5;

    if((pwr4_pwm_dc >= diy_pwm_cnt) && (PWR4_enable == 1))
	PWR4 = 1;
    else
	PWR4 = 0;

    IFS0bits.T5IF = 0;           // Clear interrupt flag
}
