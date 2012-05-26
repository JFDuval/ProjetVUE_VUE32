
#include "periph.h"


//PORTE is reserved for Digital I/O (either for Wipers or the Lights) (Active for WIPER_ON_BOARD or LIGHT_ON_BOARD)
//PORTB is reserved for Analog and other Analog peripheric
//PORTC is reserved for external crystal (the rest is not used)
//PORTF is reserved for the UART communication (the rest is not used)
//PORTD is reserved for power component (the rest is not used)
//PORTG is reserved for USB communication (the rest is not used)

unsigned int init_cnt;

void pinout_init(void)
{
    // ADC pin
    TRISBbits.TRISB0 = 1;   //Analog 1 (AN0)
    TRISBbits.TRISB1 = 1;   //Analog 2 (AN1)
    TRISBbits.TRISB2 = 1;   //Analog 3 (AN2)
    TRISBbits.TRISB3 = 1;   //Analog 4 (AN3)
    TRISBbits.TRISB4 = 1;   //Unknown (MSC1) (AN4)
    TRISBbits.TRISB9 = 1;   //Unknown (MCS2) (AN9)
    TRISBbits.TRISB10 = 1;  //Temperature of the board (AN10)

    // LED pin

    mInitAllLEDs(); // define in def.h

    //Pin for speed sensor
    TRISCbits.TRISC14 =1;   //CN0
    TRISCbits.TRISC13 =1;   //CN1
    //PWM Pins
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD3 = 0;
    //PWR Pins
    TRISDbits.TRISD4 = 0;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD7 = 0;

    // Wiper and lights are defined in there own .c as they use the same Port.

}

