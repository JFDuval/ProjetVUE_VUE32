#include "wheel_sensor.h"
#include "def.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                    Constants and variables                               //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

unsigned int last_spdo1 = 0, last_spdo2 = 0;

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
    IPC6bits.CNIP = 4;	    //Priority	    //ToDo set!
    IEC1bits.CNIE = 1;	    //Enable interrupt
}

unsigned int cnt1 = 0;
unsigned int cnt2 = 0;
unsigned int log_period1[10];
unsigned int log_period2[10];

//Change notification ISR
void __ISR(_CHANGE_NOTICE_VECTOR, ipl4) CNHandler(void)
{
    unsigned int spdo1 = 0, spdo2 = 0;
    
    unsigned int period1 = 0, period2 = 0;

    //Read inputs
    spdo1 = SPDO1;
    spdo2 = SPDO2;

    //Negative edge detection - SPDO1
    if(!spdo1)
    {
	if(last_spdo1)
	{
	    period1 = TMR4;
	    TMR4 = 0;

	    //ToDo remove test only
	    LATE = 0xFF;
	    LATE = 0x00;

	        cnt1++;
		if(cnt1>=10)
		    cnt1 = 0;
		log_period1[cnt1] = period1;

		if(cnt1 == 9)
		    Nop();
	}
    }
    else
	last_spdo1 = 1;

    //Negative edge detection - SPDO2
    if(!spdo2)
    {
	if(last_spdo2)
	{
	    period2 = TMR2;
	    TMR2 = 0;

	    //ToDo remove, test only
	        cnt2++;
		if(cnt2>=10)
		    cnt2 = 0;
		log_period2[cnt2] = period2;

		if(cnt2 == 9)
		    Nop();
		//==========
	}
    }
    else
	last_spdo2 = 1;

    //From timer count to Hertz:
    //ToDo


    IFS1bits.CNIF = 0;	    //Clear flag
}
