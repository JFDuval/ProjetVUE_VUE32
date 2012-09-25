#include "wheel_sensor.h"
#include "def.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                    Constants and variables                               //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

unsigned int last_spdo1 = 0, last_spdo2 = 0;
unsigned short period_spdo1[8], period_spdo2[8];
unsigned short spdo1_mean = 0, spdo2_mean = 0;
unsigned short time_stamp1[2] = {0,0};
unsigned short time_stamp2[2] = {0,0};

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
    CNEN = 0x0000;
    CNENbits.CNEN0 = 1;
    CNENbits.CNEN1 = 1;

    //Read port to clear past interrupts:
    dummy = SPDO1;
    dummy = SPDO2;

    //Interrupts
    IFS1bits.CNIF = 0;	    //Clear flag
    IPC6bits.CNIP = 6;	    //Priority	    //ToDo set!
    IEC1bits.CNIE = 1;	    //Enable interrupt
}

//Change notification ISR
//ToDo test with 2 channels at the same time
//ToDo update: fails if the 2 inputs are synchronized. To be fixed!
void __ISR(_CHANGE_NOTICE_VECTOR, ipl6) CNHandler(void)
{
    unsigned int spdo1 = 0, spdo2 = 0;
    static unsigned short pos1 = 0, pos2 = 0, cnt = 0;

    //Read inputs
    spdo1 = SPDO1;
    spdo2 = SPDO2;

    //Negative edge detection - SPDO1
    if(!spdo1)
    {
	if(last_spdo1)
	{
	    time_stamp1[1] = time_stamp1[0];
	    time_stamp1[0] = TMR4;
	    period_spdo1[pos1] = wheel_period(time_stamp1[0], time_stamp1[1]);
	    pos1 = (pos1 + 1) % 8;
	}
	last_spdo1 = 0;
    }
    else
	last_spdo1 = 1;

    //Negative edge detection - SPDO2
    if(!spdo2)
    {
	if(last_spdo2)
	{
	    time_stamp2[1] = time_stamp2[0];
	    time_stamp2[0] = TMR2;
	    period_spdo2[pos2] = wheel_period(time_stamp2[0], time_stamp2[1]);	    
	    pos2 = (pos2 + 1) % 8;
	}
	last_spdo2 = 0;
    }
    else
	last_spdo2 = 1;

    IFS1bits.CNIF = 0;	    //Clear flag
}

void filter_wheel(void)
{
    unsigned short j = 0;
    unsigned long sum = 0;
    unsigned short temp_moy1 = 0, temp_moy2 = 0;
    unsigned short min = 0, max = 0;

    //Speed 1 preliminary average
    sum = 0;
    for ( j = 0; j < 8; j++)
    {
	sum += period_spdo1[j];
    }
    temp_moy1 = (sum >> 3);

    //Do we have spikes?
    min = temp_moy1 - (temp_moy1 >> 2);
    max = temp_moy1 + (temp_moy1 >> 2);
    for ( j = 0; j < 8; j++)
    {
	if((period_spdo1[j] > max) || (period_spdo1[j] < min))
	    period_spdo1[j] = temp_moy1;
    }

    //Compute spikeless average:
    sum = 0;
    for ( j = 0; j < 8; j++)
    {
	sum += period_spdo1[j];
    }
    spdo1_mean = (sum >> 3);

    //===

    //Speed 2 preliminary average
    sum = 0;
    for ( j = 0; j < 8; j++)
    {
	sum += period_spdo2[j];
    }
    temp_moy2 = (sum >> 3);

    //Do we have spikes?
    min = temp_moy2 - (temp_moy2 >> 2);
    max = temp_moy2 + (temp_moy2 >> 2);
    for ( j = 0; j < 8; j++)
    {
	if((period_spdo2[j] > max) || (period_spdo2[j] < min))
	    period_spdo2[j] = temp_moy2;
    }

    //Compute spikeless average:
    sum = 0;
    for ( j = 0; j < 8; j++)
    {
	sum += period_spdo2[j];
    }
    spdo2_mean = (sum >> 3);
}

//ToDo: no pulse should read 0, not 21824

unsigned short wheel_period(unsigned short ts1, unsigned short ts2)
{
    unsigned short period = 0, diff = 0;

    //Compute period
    if(ts1 > ts2)
	period = ts1 - ts2;
    else if (ts1 == ts2)
	period = 0;
    else
    {
	diff = WCMAX - ts2;
	period = ts1 + diff;
    }

    return period;
}

unsigned short wheel_period_to_kph(unsigned short period)
{
    return (639539/period);
}