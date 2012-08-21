#include "vue32_adc.h"
#include "def.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                    Constants and variables                               //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

unsigned int adc_raw[ADC_CH][ADC_FILTER];
unsigned int adc_mean[ADC_CH];
volatile unsigned int flag_adc_valid = 0;

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                             ISR                                          //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

//ADC - ToDo Hz
void __ISR(_ADC_VECTOR,ipl2) isr_adc(void)
{
    unsigned short i = 0;
    static unsigned int adc_pos = 0;

    AD1CON1bits.ASAM = 0;   // Stop auto-sampling

    //From ADC1BUFx to adc_raw[x][adc_pos]
    adc_raw[0][adc_pos] = ADC1BUF0;
    adc_raw[1][adc_pos] = ADC1BUF1;
    adc_raw[2][adc_pos] = ADC1BUF2;
    adc_raw[3][adc_pos] = ADC1BUF3;
    adc_raw[4][adc_pos] = ADC1BUF4;
    adc_raw[5][adc_pos] = ADC1BUF9;
    adc_raw[6][adc_pos] = ADC1BUFA;
    adc_raw[7][adc_pos] = ADC1BUFB;

    //Fills the right buffer
    adc_pos++;
    if(adc_pos >= ADC_FILTER)
        adc_pos = 0;

    //Data valid?
    if(adc_pos == 0)
        flag_adc_valid = 1; //Yes, we filled all the variables

    // Clear the AD1 interrupt flag
    IFS1bits.AD1IF = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                          Functions                                       //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

void init_adc(void)
{
    unsigned short i = 0, j = 0;

    //Init buffers
    for ( i = 0; i < ADC_MAX_CH; i++)
    {
        for ( j = 0; j < ADC_FILTER - 1; j++)
        {
            adc_raw[i][j] = 0;
        }
        adc_mean[i] = 0;
    }

    //ADC config registers:
    //8 channels: AN0-4, AN9-11
    //Auto sample, auto-convert
    //8 samples/interrupt
    
    AD1CON1bits.ON = 0;             // ADC OFF
    AD1CON1bits.SIDL = 0;           // Continue in idle
    AD1CON1bits.FORM = 0;           // Integer 16bits
    AD1CON1bits.SSRC = 7;           // Auto convert
    AD1CON1bits.ASAM = 0;           // Manual sampling

    AD1CON2bits.VCFG = 0;           // Ref = VDD/VSS
    AD1CON2bits.OFFCAL = 0;         // Disable offset calibration
    AD1CON2bits.CSCNA = 1;          // Scan inputs
    AD1CON2bits.SMPI = 7;           // 8 channels
    AD1CON2bits.BUFM = 0;           // Word buffer
    AD1CON2bits.ALTS = 0;           // Always use MUXA

    AD1CON3bits.ADRC = 1;           // Internal ADC clock
    AD1CON3bits.SAMC = 31;          // x TAD - Max                 ToDo: Confirm
    AD1CON3bits.ADCS = 128;         // x TAD                      ToDo: Confirm

    AD1CHSbits.CH0NA = 0;           // Negative input is VR-
    AD1CHSbits.CH0SA = 0;           // By default, AN0

    AD1PCFG = 0b1111000111100000;   // 0 = analog, 1 = digital
    AD1CSSL = 0b0000111000011111;   // 0 = skip, 1 = scan

    IFS1bits.AD1IF = 0;              // clear interrupt flag
    IPC6bits.AD1IP = 2;              // interrupt priority 2
    IEC1bits.AD1IE = 1;              // enable interrupt
    AD1CON1bits.ADON = 1;            // ADC ON  
}

//Fills adc_mean[] with the filtered values
void filter_adc(void)
{
    unsigned short i = 0, j = 0;
    unsigned long sum = 0;

    for ( i = 0; i < ADC_MAX_CH; i++)
    {
        sum = 0;
        for ( j = 0; j < ADC_FILTER - 1; j++)
        {
            sum += adc_raw[i][j];
        }
        adc_mean[i] = (sum >> ADC_FILTER_SHIFT);
    }
}
