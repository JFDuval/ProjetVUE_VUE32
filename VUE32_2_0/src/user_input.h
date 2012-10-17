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
#define WIPER_PWR_ARMS      2
#define WIPER_PWR_PUMP      2
#define MISC_PWR_CONTACTOR  2
#define MISC_PWR_COOLING    1
#define MISC_PWR_AMP_EN     1

//Light control:
#define LT_OUT_31       LATEbits.LATE7          //Output - 31 - Brown
#define LT_IN_L         PORTEbits.RE5           //Input - L - Red/White
#define LT_IN_R         PORTEbits.RE4           //Input - R - Brown/Black
#define LT_IN_58        PORTEbits.RE3           //Input - 58 - Green/Blue
#define LT_IN_56b       PORTEbits.RE2           //Input - 56b - Purple/Blue
#define LT_IN_56a       PORTEbits.RE1           //Input - 56a - Yellow
#define LT_IN_83b       PORTEbits.RE0           //Input - 83b - Yellow/Red
//Note: Red (30) linked to +3V3
//Note: some functions are not cabled

//Light states:
#define LT_FLASHER_LEFT     0b00010000
#define LT_FLASHER_RIGHT    0b00100000
#define LT_OFF              0b00000001
#define LT_LOW              0b00000010
#define LT_HIGH             0b00000011
#define LT_BRAKE            0b10000000
#define LT_REVERSE          0b01000000

//Assigned power output:
#define LT_PWR_FRONT_LOW            1
#define LT_PWR_FRONT_HIGH           1
#define LT_PWR_FLASH_REAR_RIGHT     4
#define LT_PWR_FLASH_REAR_LEFT      4
#define LT_PWR_FLASH_FRONT_RIGHT    4
#define LT_PWR_FLASH_FRONT_LEFT     3
#define LT_PWR_BRAKE                1
#define LT_PWR_REAR                 3
#define LT_PWR_REVERSE              2

//Levels (ON - OFF):
#define LT_MIN              1
#define LT_MAX              4

//D/P/R and Key states
#define DPRK_KEY_OFF        0b00000001
#define DPRK_KEY_ON         0b00000010
#define DPRK_DPR_PARK       0b00001000
#define DPRK_DPR_DRIVE      0b00010000
#define DPRK_DPR_REVERSE    0b00100000

//Accelerator pedal
#define DEADBAND            50

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                         	Function prototypes                        //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

void init_wiper_input(void);
unsigned char read_wiper_input(void);
unsigned int wiper_action(unsigned char wiper_input);
unsigned short read_accelerator(unsigned short adc_in1, unsigned short adc_in2);
unsigned short read_brake(unsigned short adc_in);
void init_light_input(void);
unsigned char read_light_input(void);
void light_flashers(unsigned char light_input, unsigned char flash_state);
void init_dpr_key(void);
unsigned char read_dpr_key(void);

#endif
