#include "def.h"

//"The user-selectable priority levels range from 1 (lowest) to 7 (highest)."

volatile unsigned int flag_timer1_100us = 0, flag_1ms = 0;

volatile unsigned int wheel_spdo1_kph = 0, wheel_spdo2_kph = 0;

//Debug only
//unsigned int log_spd[5];
//unsigned int pos = 0;

//power_out.c
extern unsigned int PWR4_enable;
extern unsigned int pwr4_pwm_dc;

//wheel_sensor.c
extern unsigned int last_spdo1, last_spdo2;
extern unsigned int period_spdo1, period_spdo2;

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
    static unsigned int whl_cnt = 0;

    led_cnt++;
    if(led_cnt > 1500)
    {
        led_cnt = 0;
        LED1 ^= 1;          //Toggle
    }

    tmb_cnt++;
    if(tmb_cnt > 10)
    {
	flag_1ms = 1;
        tmb_cnt = 0;
        //1ms
    }

    whl_cnt++;
    if(whl_cnt > 10)	//10ms
    {
        whl_cnt = 0;

	//ToDo place in main()
	wheel_spdo1_kph = wheel_freq_to_kph(wheel_period_to_freq(period_spdo1));
	wheel_spdo2_kph = wheel_freq_to_kph(wheel_period_to_freq(period_spdo2));

	//Debug only
	/*
	pos++;
	if(pos >= 5)
	    pos = 0;
	log_spd[pos] = wheel_spdo1_kph;
	if(pos == 4)
	    Nop();
	 */
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
