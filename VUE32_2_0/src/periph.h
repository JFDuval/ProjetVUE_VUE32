#ifndef INC_PERIPH_H
#define INC_PERIPH_H

//Auto test ADC values:
#define TEST_AN0    822
#define TEST_AN1    614
#define TEST_AN2    410
#define TEST_AN3    205
#define TEST_SPAN   10

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                         	Function prototypes                        //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

void define_io(void);
void ShortDelay(unsigned int DelayCount);
unsigned int test_code1_adc_and_dio(void);
void com_led_toggle(void);

#endif

