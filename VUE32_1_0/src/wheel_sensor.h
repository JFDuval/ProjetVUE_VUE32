#ifndef INC_WSENS_H
#define INC_WSENS_H


/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                         	Function prototypes                        //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

void init_change_notification(void);
unsigned int wheel_period_to_freq(unsigned int period);
unsigned int wheel_freq_to_kph(unsigned int freq);

#endif

