#ifndef INC_SENSORS_H
#define INC_SENSORS_H


/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                         	Function prototypes                        //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

char read_temp(unsigned short adc_in);
unsigned short read_vbat(unsigned short adc_in);

#endif

