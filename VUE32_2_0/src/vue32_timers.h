#ifndef INC_TIMERS_H
#define INC_TIMERS_H


/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                         	Function prototypes                        //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#ifndef __32MX575F512H__
void InitTimers(void);
void init_timer1(void);
void init_timer2(void);
void init_timer3(void);
void init_timer4(void);
void init_timer5(void);

#else
void initTimerBMS(void);

#endif

#endif

