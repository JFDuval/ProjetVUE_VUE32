#ifndef INC_OFFBSENSORS_H
#define INC_OFFBSENSORS_H


/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                         	Function prototypes                        //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

short read_current(unsigned int adc_in, unsigned int adc_vbat);
void read_yaw_lateral(unsigned int adc_yaw, unsigned int adc_lateral);

#endif

