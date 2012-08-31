#include "def.h"

//ToDo:
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// => CAN
// => USB
// => Lecture accéléro
// => Speed sensor
// => Power Out
// => OpenECoSys


//Comments:
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//=> Do a Search in Files (CTRL+SHIFT+F) with "ToDo" to find incomplete
//   statements.


//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                    Constants and variables                               //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

unsigned int VUE32_ID = VUE32_4;

unsigned int flag_fsm = 0;
unsigned int pb_clk_test;

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                        Main function                                     //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
    unsigned int fsm_step = 0;
    unsigned int auto_test = FAIL;
    unsigned int dummy = 0;

    config();

    /*
    init_wiper_input();

    //Test function - To be removed later
    while (1)
    {
	dummy = read_wiper_input();
	Nop();
	Nop();
	wiper_action(dummy);
	Nop();
	Nop();
    }

    //Test function - To be removed later
    while (1)
    {
	auto_test = test_code1_adc_and_dio();

	if (auto_test)
	    LED2 = 0;
	else
	    LED2 = 1;
    }
*/

    while (1)
    {
	//ToDo
	if (flag_fsm)
	{
	    flag_fsm = 0;

	    switch (fsm_step)
	    {
		case 0:
		    fsm_step += 1;
		    break;

		case 1:
		    fsm_step += 1;
		    break;

		case 2:
		    fsm_step += 1;
		    break;

		case 3:
		    fsm_step = 0;
		    break;
	    }
	}
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                           Functions                                      //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

void config(void)
{
    SYSTEMConfigPerformance(80000000);
    pb_clk_test = SYSTEMConfig(SYSCLK, SYS_CFG_PCACHE);
    SYSTEMConfig(SYSCLK, SYS_CFG_PB_BUS);
    SYSTEMConfigPB(SYSCLK);
    INTEnableSystemMultiVectoredInt();

    //Disable JTAG port
    DDPCONbits.JTAGEN = 0;

    //Define inputs/outputs
    define_io();

    //Peripherals:
    //init_adc();	//ToDo enable
    init_timers();
    init_output_compare();
    //init_i2c();
    init_change_notification();

    asm volatile ("ei"); //This routine enables the core to handle any pending interrupt requests
}


//Config fuses
// SYSCLK = (8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// SYSCLK = (8MHz Crystal/ 2 * 20 / 1) = 80MHz
// PBCLK = SYSCLK = 80MHz
#pragma config UPLLEN   = ON            // USB PLL Enabled
#pragma config FPLLMUL  = MUL_20        // PLL Multiplier
#pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider
#pragma config FPLLODIV = DIV_1         // PLL Output Divider
#pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
#pragma config FWDTEN   = OFF           // Watchdog Timer
#pragma config WDTPS    = PS1           // Watchdog Timer Postscale
#pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
#pragma config OSCIOFNC = OFF           // CLKO Enable
#pragma config POSCMOD  = HS            // Primary Oscillator
#pragma config IESO     = OFF           // Internal/External Switch-over
#pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable
#pragma config FNOSC    = PRIPLL        // Oscillator Selection
#pragma config CP       = OFF           // Code Protect
#pragma config BWP      = OFF           // Boot Flash Write Protect
#pragma config PWP      = OFF           // Program Flash Write Protect
#pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
#pragma config DEBUG    = ON           	// Debugger Disabled for Starter Kit