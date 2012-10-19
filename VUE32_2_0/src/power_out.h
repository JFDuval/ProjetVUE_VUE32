#ifndef INC_PWROUT_H
#define INC_PWROUT_H

#define ROOF_LIGHT      3
#define TRUNK_SW        2

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                         	Function prototypes                        //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

unsigned int power_out(unsigned char outx, unsigned int duty);
void pwr_roof_light(unsigned char on_off);
void pwr_trunk_switch(unsigned char on_off);

#endif