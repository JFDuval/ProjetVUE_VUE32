#ifndef ADC_PARAM_H
#define ADC_PARAM_H

#include "def.h"
/*Variable*/
//unsigned int AD1_mean[AD1_NUM_CH];

/*function*/
char flagAD1;
void AD1_init(const unsigned short cusUsedChannels);
void AD1_Mean(void);


#define AD1_MAX_CH 		16		//# of channels on this PIC
#define VUE32_ADC_CHANNEL USE_ANx(0)|USE_ANx(1)|USE_ANx(2)|USE_ANx(3)|USE_ANx(4)|USE_ANx(9)|USE_ANx(10)

#define SAMPLE_MEAN 		8   //Number of sample contained for the mean value PER BUFFER
#define AD1_NB_BUFFERS          AD1_NUM_CH
#define CONVERSION_TIME_AD 27
#define ADC_PB_DIVIDER 32
#define ADC_DATA_FREQUENCY (FPB/AD1_NUM_CH/(CONVERSION_TIME_AD+12)/ADC_PB_DIVIDER);

#if AD1_NUM_CH > AD1_MAX_CH
    #error The number of channel is too high
#endif

// Defines for the AD1 configuration
#define AD1ON1_STOP_IN_IDLE_MODE (1<<13)
#define AD1ON1_START_IN_IDLE_MODE (0<<13)
#define AD1ON1_DATA_OUPUT_FORMAT_u16 (0<<8)
#define AD1ON1_AUTO_CONVERT_TRIGGER (0b111<<5)
#define AD1ON1_STOP_CONV_TO_PREVENT_OW (1<<4) // If used, you have to set ASAM after every conv
#define AD1ON1_SAMBPLE_AUTO_START (1<<2)
#define AD1ON2_SCAN_INPUTS (1<<10)
#define AD1ON2_INT_EVERY_X_SAMPLE(nbBuff) ((((nbBuff) -1)&0x0F)<<2)
#define AD1ON3_AUTOSAMPLE_TIME(Tad) (((Tad)&0x1F)<<8) // Valide pour 1 à 31
#define AD1ON3_TIME_FOR_1_TAD(Tpb) ((((Tpb)-2)>>1)&0x00FF) // Valide pour 2 à 512
#define USE_ANx(AN) (1<<(AN))

#endif
