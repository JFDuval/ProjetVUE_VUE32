#include "periph.h"
#include "def.h"

extern unsigned int adc_raw[8][8];

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
    static unsigned short led2_cnt = 0;

    led2_cnt++;
    if(led2_cnt > 25)
    {
	led2_cnt = 0;
	LED2 ^= 1;  //Toggle LED
    } 
}
