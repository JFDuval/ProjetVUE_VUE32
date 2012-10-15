/******************************************************************************
 * Hardware Profile Definitions
 *
 * All rights reserved to Projet VUE
 *
 * by Maxime Bedard - 24/09/2012
 * ****************************************************************************/

#ifndef _HARDWAREPROFILE_H_
#define _HARDWAREPROFILE_H_

#include <p32xxxx.h>

/*********************************************************************
* GetSystemClock() returns system clock frequency.
*
* GetPeripheralClock() returns peripheral clock frequency.
*
* GetInstructionClock() returns instruction clock frequency.
*
********************************************************************/

/*********************************************************************
* Macro: #define	GetSystemClock()
*
* Overview: This macro returns the system clock frequency in Hertz.
*			* value is 8 MHz x 4 PLL for PIC24
*			* value is 8 MHz/2 x 18 PLL for PIC32
*
********************************************************************/
    #if defined(__PIC24F__)
        #define GetSystemClock()    (32000000ul)
    #elif defined(__PIC32MX__)
        #define GetSystemClock()    (80000000ul)
    #elif defined(__dsPIC33F__) || defined(__PIC24H__)
        #define GetSystemClock()    (80000000ul)
    #elif defined(__dsPIC33E__) || defined(__PIC24E__)
    	#define GetSystemClock()    (120000000ul)
    #endif

/*********************************************************************
* Macro: #define	GetPeripheralClock()
*
* Overview: This macro returns the peripheral clock frequency
*			used in Hertz.
*			* value for PIC24 is <PRE>(GetSystemClock()/2) </PRE>
*			* value for PIC32 is <PRE>(GetSystemClock()/(1<<OSCCONbits.PBDIV)) </PRE>
*
********************************************************************/
    #if defined(__PIC24F__) || defined(__PIC24H__) || defined(__dsPIC33F__) || defined(__dsPIC33E__) || defined(__PIC24E__)
        #define GetPeripheralClock()    (GetSystemClock() / 2)
    #elif defined(__PIC32MX__)
        #define GetPeripheralClock()    (GetSystemClock() / (1 << OSCCONbits.PBDIV))
    #endif

/*********************************************************************
* Macro: #define	GetInstructionClock()
*
* Overview: This macro returns instruction clock frequency
*			used in Hertz.
*			* value for PIC24 is <PRE>(GetSystemClock()/2) </PRE>
*			* value for PIC32 is <PRE>(GetSystemClock()) </PRE>
*
********************************************************************/
    #if defined(__PIC24F__) || defined(__PIC24H__) || defined(__dsPIC33F__) || defined(__dsPIC33E__) || defined(__PIC24E__)
        #define GetInstructionClock()   (GetSystemClock() / 2)
    #elif defined(__PIC32MX__)
        #define GetInstructionClock()   (GetSystemClock())
    #endif


/*********************************************************************/
/******************* Pin and Register Definitions ********************/
/*********************************************************************/

// Diagnostic LEDs (1 = Off (PNP driver))
#define LED1			LATBbits.LATB12	
#define LED1_TRIS		TRISBbits.TRISB12
#define LED2			LATBbits.LATB13	
#define LED2_TRIS		TRISBbits.TRISB13

// Digital Inputs or Outputs
#define DIO_TRIS		TRISE
#define DIO_LAT			LATE
#define DIO_PORT		PORTE
#define DIO_MASK                0x000000FF

//Digital I/Os - Board Specific pins
#define DIO0                    PORTEbits.RE0
#define DIO1                    PORTEbits.RE1
#define DIO2                    PORTEbits.RE2
#define DIO3                    PORTEbits.RE3
#define DIO4                    PORTEbits.RE4
#define DIO5                    PORTEbits.RE5
#define DIO6                    PORTEbits.RE6
#define DIO7                    PORTEbits.RE7
#define DIO0_TRIS               TRISEbits.TRISE0
#define DIO1_TRIS               TRISEbits.TRISE1
#define DIO2_TRIS               TRISEbits.TRISE2
#define DIO3_TRIS               TRISEbits.TRISE3
#define DIO4_TRIS               TRISEbits.TRISE4
#define DIO5_TRIS               TRISEbits.TRISE5
#define DIO6_TRIS               TRISEbits.TRISE6
#define DIO7_TRIS               TRISEbits.TRISE7

//Analog inputs
#define TRIS_AN0		TRISBbits.TRISB0	//AN0
#define TRIS_AN1		TRISBbits.TRISB1	//AN1
#define TRIS_AN2		TRISBbits.TRISB2	//AN2
#define TRIS_AN3		TRISBbits.TRISB3	//AN3
#define TRIS_MCS1		TRISBbits.TRISB4	//AN4
#define TRIS_MCS2		TRISBbits.TRISB9	//AN9
#define TRIS_TEMP		TRISBbits.TRISB10	//AN10
#define TRIS_VOLT		TRISBbits.TRISB11	//AN11

// I2C TRIS bits 
#define I2C_SDA                 TRISDbits.TRISD9
#define I2C_SCL                 TRISDbits.TRISD10

//Speed sensor
#define SPDO1			PORTCbits.RC13		//CN1
#define SPDO2			PORTCbits.RC14		//CN0
#define SPDO1_TRIS		TRISCbits.TRISC13	
#define SPDO2_TRIS		TRISCbits.TRISC14

//Power outputs
#define PWR1			LATDbits.LATD4		//OC5
#define PWR2			LATDbits.LATD5
#define PWR3			LATDbits.LATD6	
#define PWR4			LATDbits.LATD7	
#define PWR1_TRIS		TRISDbits.TRISD4	
#define PWR2_TRIS		TRISDbits.TRISD5
#define PWR3_TRIS		TRISDbits.TRISD6
#define PWR4_TRIS		TRISDbits.TRISD7

//Motor #1
#define IN1_M1			LATDbits.LATD0		//OC1
#define IN2_M1			LATDbits.LATD2		//OC3
#define IN1_M1_TRIS		TRISDbits.TRISD0
#define IN2_M1_TRIS		TRISDbits.TRISD2

//Motor #2
#define IN1_M2			LATDbits.LATD1		//OC2
#define IN2_M2			LATDbits.LATD3		//OC4
#define IN1_M2_TRIS		TRISDbits.TRISD1
#define IN2_M2_TRIS		TRISDbits.TRISD3

//CAN
#define CRX1_TRIS		TRISFbits.TRISF0	
#define CTX1_TRIS		TRISFbits.TRISF1
#define CRX2_TRIS		TRISBbits.TRISB14
#define CTX2_TRIS		TRISBbits.TRISB8

//UART
#define U3ARX_TRIS		TRISFbits.TRISF4
#define U3ATX_TRIS		TRISFbits.TRISF5

//#define USE_SELF_POWER_SENSE_IO
#define tris_self_power     TRISAbits.TRISA2    // Input
#define self_power          1

//#define USE_USB_BUS_SENSE_IO
#define tris_usb_bus_sense  TRISBbits.TRISB5    // Input
#define USB_BUS_SENSE       1


/** I/O pin definitions ********************************************/
#define INPUT_PIN 1
#define OUTPUT_PIN 0

#endif
