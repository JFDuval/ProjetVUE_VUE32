

// PIC32MX460F512L Configuration Bit Settings


#include <p32xxxx.h>

// DEVCFG3
// USERID = No Setting


// DEVCFG2
#pragma config FPLLIDIV = DIV_1         // PLL Input Divider (1x Divider)

#pragma config FPLLMUL = MUL_24         // PLL Multiplier (24x Multiplier)

#pragma config UPLLIDIV = DIV_12        // USB PLL Input Divider (12x Divider)

#pragma config UPLLEN = OFF             // USB PLL Enable (Disabled and Bypassed)

#pragma config FPLLODIV = DIV_1         // System PLL Output Clock Divider (PLL Divide by 1)


// DEVCFG1
#pragma config FNOSC = FRCPLL           // Oscillator Selection Bits (Fast RC Osc with PLL)

#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)

#pragma config IESO = ON                // Internal/External Switch Over (Enabled)

#pragma config POSCMOD = OFF            // Primary Oscillator Configuration (Primary osc disabled)

#pragma config OSCIOFNC = ON            // CLKO Output Signal Active on the OSCO Pin (Enabled)

#pragma config FPBDIV = DIV_1           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/1)

#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)

#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)

#pragma config FWDTEN = ON              // Watchdog Timer Enable (WDT Enabled)


// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)

#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)

#pragma config PWP = OFF                // Program Flash Write Protect (Disable)

#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)

#pragma config CP = OFF                 // Code Protect (Protection Disabled)




