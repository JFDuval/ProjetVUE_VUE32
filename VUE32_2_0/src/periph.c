#include "periph.h"
#include "def.h"
#include "VUE32_Utils.h"

extern unsigned int adc_raw[8][8];

void define_io(void)
{
    //Analog inputs
    TRIS_AN0 = 1;	//AN0
    TRIS_AN1 = 1;	//AN1
    TRIS_AN2 = 1;	//AN2
    TRIS_AN3 = 1;	//AN3
    TRIS_MCS1 = 1;	//AN4
    TRIS_MCS2 = 1;	//AN9
    TRIS_TEMP = 1;	//AN10
    TRIS_VOLT = 1;	//AN11

    //LEDs
    LED1 = LED_OFF;
    TRIS_LED1 = 0;
    LED2 = LED_OFF;
    TRIS_LED2 = 0;

    //Digital I/Os
    TRIS_DIO = 0xFFFF;	//By default, all inputs

    //Speed sensor
    TRIS_SPDO1 = 1;
    TRIS_SPDO2 = 1;

    //Power outputs
    PWR1 = 0;
    TRIS_PWR1 = 0;
    PWR2 = 0;
    TRIS_PWR2 = 0;
    PWR3 = 0;
    TRIS_PWR3 = 0;
    PWR4 = 0;
    TRIS_PWR4 = 0;

    //I2C
    TRIS_SDA = 1;
    TRIS_SCL = 1;

    //Motor #1
    IN1_M1 = 0;
    TRIS_IN1_M1 = 0;
    IN2_M1 = 0;
    TRIS_IN2_M1 = 0;

    //Motor #2
    IN1_M2 = 0;
    TRIS_IN1_M2 = 0;
    IN2_M2 = 0;
    TRIS_IN2_M2 = 0;

    //CAN
    TRIS_CRX1 = 1;
    TRIS_CTX1 = 0;
    TRIS_CRX2 = 1;
    TRIS_CTX2 = 0;

    //UART
    TRIS_U3ARX = 1;
    TRIS_U3ATX = 0;

    //Unused - all inputs
    TRISBbits.TRISB5 = 1;
    TRISBbits.TRISB15 = 1;
    TRISDbits.TRISD8 = 1;
    TRISDbits.TRISD11 = 1;
    TRISGbits.TRISG6 = 1;
    TRISGbits.TRISG7 = 1;
    TRISGbits.TRISG8 = 1;
    TRISGbits.TRISG9 = 1;
}

//µs delays:
void ShortDelay(unsigned int DelayCount)      // Delay Time (CoreTimer Ticks)
{
    unsigned int StartTime;                    // Start Time

    StartTime = ReadCoreTimer();         // Get CoreTimer value for StartTime

    while( (unsigned int)(ReadCoreTimer() - StartTime) < DelayCount ) {};
}

unsigned int test_code1_adc_and_dio(void)
{
    unsigned int test_dio = 0;

    /*
     * To use this code, you need to plug the Test Connector #1 to the
     * Logic connector. The digital pattern should be 0xAA (170d) and the ADC
     * values [AN0 ... AN3] = [819 618 412 205]
    */

    //Digital I/Os (inputs)
    test_dio = PORT_DIO;
    if(test_dio != 0xAA)
        return FAIL;

    //External ADC inputs
    if(!((adc_raw[0][0] > (TEST_AN0 - TEST_SPAN)) && (adc_raw[0][0] < (TEST_AN0 + TEST_SPAN))))
        return FAIL;

    if(!((adc_raw[1][0] > (TEST_AN1 - TEST_SPAN)) && (adc_raw[1][0] < (TEST_AN1 + TEST_SPAN))))
        return FAIL;

    if(!((adc_raw[2][0] > (TEST_AN2 - TEST_SPAN)) && (adc_raw[2][0] < (TEST_AN2 + TEST_SPAN))))
        return FAIL;

    if(!((adc_raw[3][0] > (TEST_AN3 - TEST_SPAN)) && (adc_raw[3][0] < (TEST_AN3 + TEST_SPAN))))
        return FAIL;

    return PASS;
}

//ToDo call this function from CAN too
void com_led_toggle(void)
{
    EVERY_X_MS(100)
	LED2 ^= 1;  //Toggle LED
    END_OF_EVERY
}
