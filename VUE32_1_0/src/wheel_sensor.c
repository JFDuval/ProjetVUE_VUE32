#include "wheel_sensor.h"
#include "def.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                    Constants and variables                               //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

unsigned int last_spdo1 = 0, last_spdo2 = 0;
unsigned int period_spdo1 = 0, period_spdo2 = 0;

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                          Functions                                       //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

//Configure interrupts for CN0 (SPDO2) and CN1 (SPDO1)
//All CNx interrupts are or'ed together
void init_change_notification(void)
{
    unsigned int dummy = 0;

    CNCONbits.ON = 1;	    //Module enabled
    CNCONbits.SIDL = 0;	    //Continue in idle

    //Enable CN0 and CN1:
    CNENbits.CNEN0 = 1;
    CNENbits.CNEN1 = 1;

    //Read port to clear past interrupts:
    dummy = SPDO1;
    dummy = SPDO2;

    //Interrupts
    IFS1bits.CNIF = 0;	    //Clear flag
    IPC6bits.CNIP = 4;	    //Priority	    //ToDo set!
    IEC1bits.CNIE = 1;	    //Enable interrupt
}

unsigned int cnt1 = 0;
unsigned int cnt2 = 0;
unsigned int log_period1[10];
unsigned int log_period2[10];

//Change notification ISR
//ToDo test with 2 channels at the same time
//ToDo update: fails if the 2 inputs are synchronized. To be fixed!
void __ISR(_CHANGE_NOTICE_VECTOR, ipl4) CNHandler(void)
{
    unsigned int spdo1 = 0, spdo2 = 0;
    unsigned int result = 0, speed;

    //Read inputs
    spdo1 = SPDO1;
    spdo2 = SPDO2;

    //Negative edge detection - SPDO1
    if(!spdo1)
    {
	if(last_spdo1)
	{
	    period_spdo1 = TMR4;
	    TMR4 = 0;
	}
    }
    else
	last_spdo1 = 1;

    //Negative edge detection - SPDO2
    if(!spdo2)
    {
	if(last_spdo2)
	{
	    if(last_spdo2)
	    {
		period_spdo2 = TMR2;
		TMR2 = 0;
	    }
	}
    }
    else
	last_spdo2 = 1;

    IFS1bits.CNIF = 0;	    //Clear flag
}

//ToDo: we need to increase the resolution and/or filter
//ToDo: no pulse should read 0, not 21824

//Converts the timer value in (Hertz*10)
unsigned int wheel_period_to_freq(unsigned int period)
{
    //1 Tick = 3.2µs
    float freq = 1 / (6.4e-6 * period);

    return (unsigned int) (freq * 10);
}

//Converts the frequency to speed in km/h * 10
unsigned int wheel_freq_to_kph(unsigned int freq)
{
    float speed = 0.1023 * freq;

    return (unsigned int) speed;
}