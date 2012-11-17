#include <p32xxxx.h>
#include <plib.h>
#include <sys/kmem.h>
#include "def.h"

#ifdef __32MX575F512H__
#include "../BMS_2_0.X/Board.h"
#endif

volatile unsigned int flag_1ms_a = 0, flag_1ms_b = 0, flag_8ms = 0;
volatile unsigned char flag_drives = 0;
volatile unsigned int flag_flash = 0, flag_x100ms = 0;
volatile unsigned char spd1_moving = 0, spd2_moving = 0;

//power_out.c
extern unsigned int PWR4_enable;
extern unsigned int pwr4_pwm_dc;

//wheel_sensor.c
extern unsigned int last_spdo1, last_spdo2;
extern volatile unsigned char pulses_spd1, pulses_spd2;

// Global timestamp, should only be accessed with a function call (TODO)
volatile unsigned int uiTimeStamp = 0;

//user_input.c
extern volatile unsigned short wiper_delay;

//VUE32_ID GetBoardID(void);
void OnMsgBMS(NETV_MESSAGE *msg);
void RunLongPolling(void);

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                         Interruptions                                    //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __32MX575F512H__
//Timer 1 - Main timebase 100µs - 10kHz
void __ISR(_TIMER_1_VECTOR, ipl3) isr_timer1(void)
{
    static unsigned int time_cnt = 0;

    static unsigned int led_cnt = 0, flash_cnt = 0;
    static unsigned int tmb_b_cnt = 4;
    static unsigned int tmb_moving = 0;
    static unsigned int last_pulses_spd1 = 0, last_pulses_spd2 = 0;
    static unsigned int tmb_x100ms = 0;
    static unsigned short usDrivesCNT = 0;


    //1ms - 1000Hz (timestamp)
    time_cnt++;
    if(time_cnt > 10)
    {
        time_cnt = 0;
        uiTimeStamp++;
        flag_1ms_a = 1;
    }

    //1ms Time base B
    tmb_b_cnt++;
    if(tmb_b_cnt > 10)
    {
	flag_1ms_b = 1;
        tmb_b_cnt = 0;
    }

    //125ms - 8Hz
    led_cnt++;
    if(led_cnt > 1250)
    {
        led_cnt = 0;
        flag_8ms = 1;
        //LED1 ^= 1;  //Toggle LED 4Hz
    }

    //50ms - 20 Hz
    usDrivesCNT++;
    if(usDrivesCNT >= 500)
    {
        usDrivesCNT = 0;
        flag_drives = 1;
    }

    //100ms - 10Hz (wipers)
    tmb_x100ms++;
    if(tmb_x100ms > wiper_delay)
    {
        tmb_x100ms = 0;

        flag_x100ms = 1;
    }

    //Flashers
    flash_cnt++;
    if(flash_cnt > 4000)
    {
        flash_cnt = 0;
        flag_flash = 1;
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
    static unsigned int diy_pwm_cnt = 0;
    //PWM:
    diy_pwm_cnt = (diy_pwm_cnt + 1) % 5;

    if((pwr4_pwm_dc >= diy_pwm_cnt) && (PWR4_enable == 1))
	PWR4 = 1;
    else
	PWR4 = 0;

    IFS0bits.T5IF = 0;           // Clear interrupt flag
}

#else

//Timer 1 - Main timer
void __ISR(_TIMER_1_VECTOR, ipl3) isr_timer1(void)
{
    static unsigned int time_cnt = 0;
    static unsigned int time_cnt2 = 0;

    //1ms - 1000Hz (timestamp)
    time_cnt++;
    if(time_cnt > 10)
    {
        time_cnt = 0;
        uiTimeStamp++;
    }
    
    // Process network stack every 5 ms
    time_cnt2++;
    if ( time_cnt2 > 10)
    {
        time_cnt2 = 0;
        NETV_MESSAGE oMsgRecep;

        asm("di");
        if(netv_transceiver((unsigned char)GetMyAddr(), &oMsgRecep))
        {
            LED2 ^= 1;
            OnMsgBMS(&oMsgRecep);
        }
            
        //RunLongPolling();
        asm("ei");
    }

    //Clear flag and return
    IFS0bits.T1IF = 0;
}

#endif
