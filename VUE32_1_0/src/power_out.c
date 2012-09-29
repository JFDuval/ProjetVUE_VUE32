#include "power_out.h"
#include "def.h"

// Note: the Power Outputs are High-Side switches
// Connect the load between the Output (+) and the vehicle's GND (-)
// 1 = +12V on OUTx = Powered load

// Connexions - VUE32 #2
// ======================
// => OUT1: Lights - Brake - Rear Right - 21W
// => OUT2: Lights - Reverse - Rear Right - 21W
// => OUT3: Lights - Night - Rear Right - 21W

// Connexions - VUE32 #3
// ======================
// => OUT1: Cooling pump - 100W
// => OUT2: Main contactor - 5W

// Connexions - VUE32 #4
// ======================
// => OUT1: Lights - Low Beams - 110W (2x 55W)
// => OUT2: Wipers - Arms - 60W
// => OUT3: Lights - Left Flashers - 42W (2x 21W)
// => OUT4: Lights - Right Flashers - 42W (2x 21W)

// Connexions - VUE32 #5
// ======================
// => OUT1: Amplifier Enable - 1W

// Connexions - VUE32 #6
// ======================
// => OUT1: Lights - High Beams - 110W (2x 55W)
// => OUT2: Wipers - Fluid pump - 60W

// Connexions - VUE32 #7
// ======================
// => OUT1: Lights - Brake - Rear Left - 21W
// => OUT2: Lights - Reverse - Rear Left - 21W
// => OUT3: Lights - Night - Rear Left - 21W

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                    Constants and variables                               //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

unsigned int PWR4_enable = 0;
unsigned int pwr4_pwm_dc = 0;

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                          Functions                                       //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

unsigned int power_out(unsigned char outx, unsigned int duty)
{
    //Note: only OUT4 has PWM functionnality

    if(outx == 1)
    {
	if(duty)
	    PWR1 = 1;
	else
	    PWR1 = 0;
    }
    else if(outx == 2)
    {
	if(duty)
	    PWR2 = 1;
	else
	    PWR2 = 0;
    }
    else if(outx == 3)
    {
	if(duty)
	    PWR3 = 1;
	else
	    PWR3 = 0;
    }
    else if(outx == 4)
    {
	if(duty)
	    PWR4_enable = 1;
	else
	    PWR4_enable = 0;

	pwr4_pwm_dc = duty;
    }
    else
    {
	return 1;
    }

    return 0;
}