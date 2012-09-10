#ifndef INC_OFFBSENSORS_H
#define INC_OFFBSENSORS_H

//Ground fault sensor - counts based on a 1ms timebase
#define COUNT_50HZ  22  //50Hz = 20ms. 1.1*20 = 22
#define COUNT_40HZ  25  //40Hz = 20ms
#define COUNT_30HZ  33  //30Hz = 20ms
#define COUNT_20HZ  50  //20Hz = 20ms
#define COUNT_10HZ  100  //10Hz = 20ms
#define COUNT_0HZ   125

#define FREQ_0HZ        0
#define FREQ_10HZ       1
#define FREQ_20HZ       2
#define FREQ_30HZ       3
#define FREQ_40HZ       4
#define FREQ_50HZ       5


/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                         	Function prototypes                        //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

short read_current(unsigned int adc_in, unsigned int adc_vbat);
void read_yaw_lateral(unsigned int adc_yaw, unsigned int adc_lateral);
unsigned short gfi_freq_sensor(void);
unsigned short gfi_state_sensor(void);

#endif

