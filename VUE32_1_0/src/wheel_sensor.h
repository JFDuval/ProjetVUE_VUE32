#ifndef INC_WSENS_H
#define INC_WSENS_H


/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                         	Function prototypes                        //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

void init_change_notification(void);
unsigned short wheel_period(unsigned short ts1, unsigned short ts2);
unsigned short wheel_period_to_kph(unsigned short period, unsigned char moving);

#endif

