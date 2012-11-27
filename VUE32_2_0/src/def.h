#ifndef INC_DEF_H
#define INC_DEF_H

#include <p32xxxx.h>
#include <plib.h>
#include <sys/kmem.h>
#include "bsp.h"
#include "periph.h"
#include "vue32_adc.h"
#include "vue32_i2c.h"
#include "vue32_oc_pwm.h"
#include "vue32_timers.h"
#include "onboard_sensors.h"
#include "offboard_sensors.h"
#include "drive.h"
#include "user_input.h"
#include "power_out.h"
#include "wheel_sensor.h"
#include "NETV32_Utils.h"
#include "USB-CDC_Microchip/usb.h"
#include "USB-CDC_Microchip/usb_function_cdc.h"
#ifdef __32MX575F512H__
#include "../BMS_2_0.X/HardwareProfile.h"
#endif
#include "GenericTypeDefs.h"
#include "USB-CDC_Microchip\Compiler.h"
#include "USB-CDC_Microchip\usb_config.h"
#include "USB-CDC_Microchip\usb_device.h"
#include "USB-CDC_Microchip\usb.h"
#include "microchip_usb_fct.h"
#include "NETV32_Common.h"
#include "NETV32_Shared.h"

//Enable/Disable high-level functions:
//#define USE_I2C

//Main data structure ToDo: useful?
struct vue32_data
{
    unsigned char       board_id;
    //4x Generic analog channels
    unsigned short      adc_an0;
    unsigned short      adc_an1;
    unsigned short      adc_an2;
    unsigned short      adc_an3;
    //Decoded analog values
    unsigned short      mcs1;
    unsigned short      mcs2;
    char                temp;
    unsigned short      vbat;
    //Speed sensor
    int                 speed1;
    int                 speed2;
    //Digital I/O
    unsigned char       dio;
    //Power out
    short               pwr1;
    short               pwr2;
    short               pwr3;
    short               pwr4;
    //Motor control
    short               motor1;
    short               motor2;
};

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                  	Function prototypes                                 //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

void setup_oscillator(void);
void config(void);
void board_specific_config(void);

/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//                                         Definitions                                     //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////

//System Clock definition and Peripheral Clock
#define SYSCLK                  80000000L
#define SYS_XTAL_FREQ           SYSCLK
#define FPB                     SYSCLK
#define US_TO_CT_TICKS          (SYSCLK/2000000UL)

//LEDs
#define LED_ON			0
#define LED_OFF			1

//Automatic tests
#define PASS                    1
#define FAIL                    0

//D/P/R
#define DRIVE                   1
#define PARK                    0
#define REVERSE                 2

//Doors
#define OPENED                  1
#define CLOSED                  0

//ADC Pins
#define ADC_FILTERED_AN0        0
#define ADC_FILTERED_AN1        1
#define ADC_FILTERED_AN2        2
#define ADC_FILTERED_AN3        3
#define ADC_FILTERED_MCS1       4
#define ADC_FILTERED_MCS2       5
#define ADC_FILTERED_TEMP       6
#define ADC_FILTERED_VOLT       7

//Wheel counter
#define WCMAX                   65535

/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//                                       Pin Definitions                                   //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////

//Analog inputs
#define TRIS_AN0		TRISBbits.TRISB0	//AN0
#define TRIS_AN1		TRISBbits.TRISB1	//AN1
#define TRIS_AN2		TRISBbits.TRISB2	//AN2
#define TRIS_AN3		TRISBbits.TRISB3	//AN3
#define TRIS_MCS1		TRISBbits.TRISB4	//AN4
#define TRIS_MCS2		TRISBbits.TRISB9	//AN9
#define TRIS_TEMP		TRISBbits.TRISB10	//AN10
#define TRIS_VOLT		TRISBbits.TRISB11	//AN11

#ifndef __32MX575F512H__
//LEDs
#define LED1			LATBbits.LATB12	
#define TRIS_LED1		TRISBbits.TRISB12
#define LED2			LATBbits.LATB13	
#define TRIS_LED2		TRISBbits.TRISB13
//1 = Off (PNP driver)
#endif

//Digital I/Os - Port
#define TRIS_DIO		TRISE	
#define LAT_DIO			LATE
#define PORT_DIO		PORTE
//Digital I/Os - Board Specific pins
#define DIO_GFI_FREQ            PORTEbits.RE0
#define TRIS_DIO_GFI_FREQ       TRISEbits.TRISE0
#define DIO_GFI_STATE           PORTEbits.RE2
#define TRIS_DIO_GFI_STATE      TRISEbits.TRISE2
#define DIO_WIPER_SW            PORTEbits.RE6
#define TRIS_DIO_WIPER_SW       TRISEbits.TRISE6
#define DIO_BRAKE_SW            PORTEbits.RE0
#define TRIS_DIO_BRAKE_SW       TRISEbits.TRISE0
#define DIO_DPR_SW1             PORTEbits.RE1
#define TRIS_DIO_DPR_SW1        TRISEbits.TRISE1
#define DIO_DPR_SW2             PORTEbits.RE2
#define TRIS_DIO_DPR_SW2        TRISEbits.TRISE2
#define DIO_DISP_CLK            PORTEbits.RE1
#define TRIS_DIO_DISP_CLK       TRISEbits.TRISE1
#define DIO_DISP_DATA           PORTEbits.RE3
#define TRIS_DIO_DISP_DATA      TRISEbits.TRISE3

//Speed sensor
#define SPDO1			PORTCbits.RC13		//CN1
#define TRIS_SPDO1		TRISCbits.TRISC13	
#define SPDO2			PORTCbits.RC14		//CN0
#define TRIS_SPDO2		TRISCbits.TRISC14

//Power outputs
#define PWR1			LATDbits.LATD4		//OC5
#define TRIS_PWR1		TRISDbits.TRISD4	
#define PWR2			LATDbits.LATD5
#define TRIS_PWR2		TRISDbits.TRISD5
#define PWR3			LATDbits.LATD6	
#define TRIS_PWR3		TRISDbits.TRISD6
#define PWR4			LATDbits.LATD7	
#define TRIS_PWR4		TRISDbits.TRISD7

//I2C
#define TRIS_SDA		TRISDbits.TRISD9
#define TRIS_SCL		TRISDbits.TRISD10

//Motor #1
#define IN1_M1			LATDbits.LATD0		//OC1
#define TRIS_IN1_M1		TRISDbits.TRISD0
#define IN2_M1			LATDbits.LATD2		//OC3
#define TRIS_IN2_M1		TRISDbits.TRISD2

//Motor #2
#define IN1_M2			LATDbits.LATD1		//OC2
#define TRIS_IN1_M2		TRISDbits.TRISD1
#define IN2_M2			LATDbits.LATD3		//OC4
#define TRIS_IN2_M2		TRISDbits.TRISD3

//CAN
#define TRIS_CRX1		TRISFbits.TRISF0	
#define TRIS_CTX1		TRISFbits.TRISF1
#define TRIS_CRX2		TRISBbits.TRISB14
#define TRIS_CTX2		TRISBbits.TRISB8

//UART
#define TRIS_U3ARX		TRISFbits.TRISF4
#define TRIS_U3ATX		TRISFbits.TRISF5

#define DATAFLAGSSIZE           11
#define MAXCOMMANDTORQUE        100 //MAX 200 N*m

#endif
