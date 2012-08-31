#include "wheel_sensor.h"
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

//Configure interrupts for CN0 (SPDO2) and CN1 (SPDO1)
//All CNx interrupts are or'ed together
void init_change_notification(void)
{
    unsigned int dummy = 0;

    CNCONbits.ON = 1;	    //Module enabled
    CNCONbits.SIDL = 0;	    //Continue in idle

    //Enable CN0 and CN1:
    //CNENbits.CNEN0 = 1;   //ToDo enable
    CNENbits.CNEN1 = 1;

    //Read port to clear past interrupts:
    dummy = SPDO1;
    dummy = SPDO2;

    //Interrupts
    IFS1bits.CNIF = 0;	    //Clear flag
    IPC6bits.CNIP = 2;	    //Priority	    //ToDo set!
    IEC1bits.CNIE = 1;	    //Enable interrupt
}

unsigned int cnt = 0, log[10];

//Change notification ISR
void __ISR(_CHANGE_NOTICE_VECTOR, ipl4) CNHandler(void)
{
    unsigned int spdo1 = 0, spdo2 = 0;
    static unsigned int last_spdo1 = 0, last_spdo2 = 0;
    unsigned int period1 = 0, period2 = 0;

    //Read inputs
    spdo1 = SPDO1;
    spdo2 = SPDO2;

    //Negative edge detection - ToDo to be debuged
    if(!spdo1)
    {
	if(last_spdo1)
	{
	    period1 = TMR4;
	    TMR4 = 0;
	}
	last_spdo1 = 0;
    }
    else
	last_spdo1 = 1;

    cnt++;
    if(cnt>=10)
	cnt = 0;
    log[cnt] = period1;

    if(cnt == 9)
	Nop();


    IFS1bits.CNIF = 0;	    //Clear flag
}
