#include "power_out.h"
#include "def.h"

// Note: the Power Outputs are High-Side switches
// Connect the load between the Output (+) and the vehicle's GND (-)
// 1 = +12V on OUTx = Powered load

// Connections - VUE32 #4
// ======================
// => OUT1: Lights - Front Low/Night - 110W (2x 55W)
// => OUT2: Lights - Right flashers - 42W (2x 21W)
// => OUT3: Lights - Left flashers - 42W (2x 21W)
// => OUT4: Wipers - Arms - 60W

// Connections - VUE32 #6
// ======================
// => OUT1: Lights - High - 110W (2x 55W)
// => OUT2: Lights - Rear brakes - 42W (2x 21W)
// => OUT3: Lights - Rear night - 42W (2x 21W)
// => OUT4: Wipers - Fluid pump - 60W

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

unsigned int power_out(unsigned char outx, unsigned int duty)
{
    if(outx == 1)
    {

    }
    else if(outx == 2)
    {

    }
    else if(outx == 3)
    {

    }
    else if(outx == 4)
    {

    }
    else
    {
        
    }
}