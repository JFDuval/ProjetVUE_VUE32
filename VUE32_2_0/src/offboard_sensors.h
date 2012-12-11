#ifndef INC_OFFBSENSORS_H
#define INC_OFFBSENSORS_H

//Ground fault sensor - counts based on a 1ms timebase
#define COUNT_50HZ  20  //50Hz = 20ms
#define COUNT_40HZ  25  //40Hz = 20ms
#define COUNT_30HZ  33  //30Hz = 20ms
#define COUNT_20HZ  50  //20Hz = 20ms
#define COUNT_10HZ  100  //10Hz = 20ms
#define COUNT_0HZ   125

#define FREQ_0HZ        0
#define FREQ_10HZ       10
#define FREQ_20HZ       20
#define FREQ_30HZ       30
#define FREQ_40HZ       40
#define FREQ_50HZ       50
#define FAULT           0x80
#define STATE_0HZ       0x40


/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                         	Function prototypes                        //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

short read_current(unsigned short adc_in, unsigned short adc_vbat);
short read_yaw(unsigned short adc_yaw);
short read_lateral(unsigned short adc_lateral);
unsigned char gfi_freq_sensor(void);
short read_motor_temp(unsigned short adc_in);
#endif

