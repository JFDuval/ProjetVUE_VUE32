#ifndef INC_ADC_H
#define INC_ADC_H

#include "def.h"

#define ADC_CH              8   // 8 channels: AN0-4, AN9-11
#define ADC_MAX_CH          (ADC_CH - 1)
#define ADC_FILTER          8   // Moving average samples
#define ADC_FILTER_SHIFT    3   // (2^ADC_FILTER_SHIFT)=ADC_FILTER

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                         	Function prototypes                        //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

void InitADC(void);
void filter_adc(void);
void board_specific_adc_decode(void);

#endif
