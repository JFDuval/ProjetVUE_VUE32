#include "vue32_oc_pwm.h"
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

void init_output_compare(void)
{
	init_oc1();
	init_oc2();
	init_oc3();
	init_oc4();
}

//Output compare 1 - IN1_M1
void init_oc1(void)
{
	OC1CONbits.ON = 0;              // close OC1
	OC1CONbits.OCTSEL = 1;          // Select Timer 3 as time base
	OC1CONbits.OC32 = 0;            // Compare only the 16-bit of OCxR
	OC1CONbits.SIDL = 0;            // Continue operation while idle
	OC1CONbits.OCM = 0b110;         // Configure for PWM mode without Fault pin enabled

	OC1R = 0x0000;                  // Initialize primary Compare register
	OC1RS = 0x0000;                 // Initialize second compare register (next value)

	OC1CONbits.ON = 1;             	// Enable OC1
}

//Output compare 1 - IN1_M2
void init_oc2(void)
{
	OC2CONbits.ON = 0;              //close OC2
	OC2CONbits.OCTSEL = 1;          //Select Timer 3 as time base
	OC2CONbits.OC32 = 0;            //Compare only the 16-bit of OCxR
	OC2CONbits.SIDL = 0;            //Continue operation while idle
	OC2CONbits.OCM = 0b110;         // Configure for PWM mode without Fault pin enabled

	OC2R = 0x0000;                  // Initialize primary Compare register
	OC2RS = 0x0000;                 //Initialize second compare register (next value)

	OC2CONbits.ON = 1;             // Enable OC2
}

//Output compare 3 - IN2_M1
void init_oc3(void)
{
	OC3CONbits.ON = 0;              //close OC3
	OC3CONbits.OCTSEL = 1;          //Select Timer 3 as time base
	OC3CONbits.OC32 = 0;            //Compare only the 16-bit of OCxR
	OC3CONbits.SIDL = 0;            //Continue operation while idle
	OC3CONbits.OCM = 0b110;         // Configure for PWM mode without Fault pin enabled

	OC3R = 0x0000;                  // Initialize primary Compare register
	OC3RS = 0x0000;                 //Initialize second compare register (next value)

	OC1CONbits.ON = 1;             // Enable OC3
}

//Output compare 4 - IN2_M2
void init_oc4(void)
{
	OC4CONbits.ON = 0;              //close OC4
	OC4CONbits.OCTSEL = 1;          //Select Timer 3 as time base
	OC4CONbits.OC32 = 0;            //Compare only the 16-bit of OCxR
	OC4CONbits.SIDL = 0;            //Continue operation while idle
	OC4CONbits.OCM = 0b110;         // Configure for PWM mode without Fault pin enabled

	OC4R = 0x0000;                  // Initialize primary Compare register
	OC4RS = 0x0000;                 //Initialize second compare register (next value)

	OC4CONbits.ON = 1;             // Enable OC4
}