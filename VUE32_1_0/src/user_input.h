#ifndef INC_UINPUT_H
#define INC_UINPUT_H

//Note: Pin names given according to the wiring convention written on the levers.

//Wiper control:
#define WP_OUT_W        LATEbits.LATE7          //Output - W - Red/Green
#define WP_OUT_I        LATEbits.LATE6          //Output - I - Brown/Grey
#define WP_OUT_54       LATEbits.LATE5          //Output - 54 - Green/Blue & Green/Yellow
#define WP_OUT_53b      LATEbits.LATE4          //Output - 53b - Yellow
#define WP_OUT_53c      LATEbits.LATE3          //Output - 53c - Brown/Blue & Green/Blue
#define WP_IN_15        PORTEbits.RE2           //Input - 15 - Pink/Red
#define WP_IN_31        PORTEbits.RE1           //Input - 31 - Brown
#define WP_IN_31b       PORTEbits.RE0           //Input - 31b - Blue/Black

//Wiper states:
#define WP_E0           0b00000001
#define WP_E1           0b00000010
#define WP_E2           0b00000011
#define WP_E3           0b00000100
#define WP_RLX1         0b00010000
#define WP_RLX2         0b00100000
#define WP_ACT1         0b00110000
#define WP_ACT2         0b01000000

//Speed:
#define WP_SUPER_SLOW   1
#define WP_SLOW         2
#define WP_FAST         3
#define WP_SUPER_FAST   4
#define WP_PUMP_MIN     1
#define WP_PUMP_MAX     4

//Assigned power output:
#define POWER_OUT_WIPER 4

//Light control:
#define LT_OUT_30       LATEbits.LATE7          //Output - 30 - Fixed +3V3	//ToDo remove, link to "real" 3.3V
#define LT_OUT_31       LATEbits.LATE6          //Output - 31 - Fixed +3V3	//ToDo remove, link to "real" 3.3V
#define LT_IN_L         PORTEbits.RE5           //Input - L
#define LT_IN_R         PORTEbits.RE4           //Input - R
#define LT_IN_58        PORTEbits.RE3           //Input - 58
#define LT_IN_56b       PORTEbits.RE2           //Input - 56b
#define LT_IN_56a       PORTEbits.RE1           //Input - 56a
#define LT_IN_83b       PORTEbits.RE0           //Input - 83b

//Light states:
#define LT_FLASHER_LEFT     0b00010000
#define LT_FLASHER_RIGHT    0b00100000
#define LT_LOW              0b00000001
#define LT_MID              0b00000010
#define LT_HIGH             0b00000011
#define LT_BRAKE            0b10000000

//Assigned power output:
#define LT_PWR_FRONT_LOW    1
#define LT_PWR_FRONT_HIGH   1
#define LT_PWR_FLASH_RIGHT  2
#define LT_PWR_BRAKE        2
#define LT_PWR_FLASH_LEFT   3
#define LT_PWR_REAR         3

//Levels (ON - OFF):
#define LT_MIN              1
#define LT_MAX              4

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                         	Function prototypes                        //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

void init_wiper_input(void);
unsigned char read_wiper_input(void);
unsigned int wiper_action(unsigned char wiper_input);
unsigned int read_accelerator(unsigned int adc_in);
unsigned int read_brake(unsigned int adc_in);
void init_light_input(void);
unsigned char read_light_input(void);

#endif

