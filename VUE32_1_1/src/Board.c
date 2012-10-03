/******************************************************************************
 * Board support drivers
 * for initialisation and board specific functions
 * All rights reserved to Projet VUE
 *
 * by Maxime Bedard - 24/09/2012
 * ****************************************************************************/

#include "Board.h"
#include "HardwareProfile.h"
#include "vue32_adc.h"
#include "NETV32_Common.h"
#include "VUE32_Impl.h"

// Persistent data
#pragma romdata reserved_section=0x1D07FFF0
const int persistentData = 0x00000001;
#pragma romdata

#define FIRMWARE_VERSION 0x0001

/*
 * Initialize the board
 * Timers, Communication, etc
 * Note : Should only be called once at the begginning of the main
 */
void InitBoard(void)
{
    SYSTEMConfigPerformance(GetSystemClock());
    SYSTEMConfig(GetSystemClock(), SYS_CFG_PCACHE);
    SYSTEMConfig(GetSystemClock(), SYS_CFG_PB_BUS);
    SYSTEMConfigPB(GetSystemClock());
    INTEnableSystemMultiVectoredInt();

    //Disable JTAG port
    DDPCONbits.JTAGEN = 0;

    // Initialize LEDs
    LED1_TRIS = 0;
    LED2_TRIS = 0;

    // Initialize Timers
    InitTimers();

    // Initialize ADC
    InitADC();

    // Initialize CAN buses
    CRX1_TRIS = 1;
    CTX1_TRIS = 0;
    CRX2_TRIS = 1;
    CTX2_TRIS = 0;
    netv_init_can_driver(GetBoardID(),CAN1);
    netv_init_can_driver(GetBoardID(),CAN2);

    //UART
    TRIS_U3ARX = 1;
    TRIS_U3ATX = 0;
    
    // Initialize I2C
    InitI2C();
    
    // Initialize digital IOs as inputs
    DIO_TRIS |= DIO_MASK;
    
    // Initialize Power Outputs (low)
    PWR1 = 0;
    PWR2 = 0;
    PWR3 = 0;
    PWR4 = 0;
    PWR1_TRIS = 1;
    PWR2_TRIS = 1;
    PWR3_TRIS = 1;
    PWR4_TRIS = 1;

    // Initialize Speed sensor
    TRIS_SPDO1 = 1;
    TRIS_SPDO2 = 1;

    //Motor #1
    IN1_M1 = 0;
    IN1_M1_TRIS = 0;
    IN2_M1 = 0;
    IN2_M1_TRIS = 0;

    //Motor #2
    IN1_M2 = 0;
    IN1_M2_TRIS = 0;
    IN2_M2 = 0;
    IN2_M2_TRIS = 0;

    //Unused - all inputs
    TRISBbits.TRISB5 = 1;
    TRISBbits.TRISB15 = 1;
    TRISDbits.TRISD8 = 1;
    TRISDbits.TRISD11 = 1;
    TRISGbits.TRISG6 = 1;
    TRISGbits.TRISG7 = 1;
    TRISGbits.TRISG8 = 1;
    TRISGbits.TRISG9 = 1;
    
    // TODO: Speed sensors, UART and motors inits are missing
    asm volatile ("ei"); //Enables the core to handle any pending interrupt requests
}

/*
 * Get the persistent Board Number
 * This value is fixed in flash memory
 */
VUE32_ID GetBoardID(void)
{
    return (persistentData & 0x000000FF);
}

/*
 * Get the firmware version
 */
unsigned short GetFirmVersion(void)
{
    return FIRMWARE_VERSION;
}

/*
 * Initialize the specific VUE32 board
 * Drivers and unique functionnalities
 * Note : Should only be called only once at the begginning of the main
 */
void InitVUE32(VUE32_ID id)
{
    gInitFunc[id]();
}

/*
 * Call the implementation of the main loop of a specific VUE32 board
 */
void CallVUE32Impl(VUE32_ID id)
{
    gImplFunc[id]();
}

