#ifndef INC_DEF_H
#define INC_DEF_H

#include <p32xxxx.h>
#include <plib.h>
#include "periph.h"
#include "interrupt.h"

//Peripherals to use:
//====================


//Network Viewer
//#define NETV

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                  	Function prototypes                                 //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

void config(void);

/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//                                          Definitions                                    //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////

// Let compile time pre-processor calculate the CORE_TICK_PERIOD
#define SYS_FREQ 				(80000000)
#define TOGGLES_PER_SEC			5
#define CORE_TICK_RATE	        (SYS_FREQ/2/TOGGLES_PER_SEC)

#define ADC_CHANNELS 			11 //(AN2 - AN12)
#define MIN_ADC_CH				2
#define MAX_ADC_CH				12

//LED
#define HBLED1 		PORTBbits.RB12
#define TRIS_HBLED1	TRISBbits.TRISB12
#define HBLED2		PORTBbits.RB13
#define TRIS_HBLED2	TRISBbits.TRISB13

#endif
