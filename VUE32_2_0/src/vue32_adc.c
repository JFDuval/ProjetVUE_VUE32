#include "vue32_adc.h"
#include "def.h"
#include "Board.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                    Constants and variables                               //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

unsigned short adc_raw[ADC_CH][ADC_FILTER];
unsigned short adc_mean[ADC_CH];
volatile unsigned char flag_adc_valid = 0, flag_adc_filter = 0;

//Decoded ADC values:
char board_temp = 0, current = 0;
unsigned short board_volt = 0;
unsigned short pedal_accelerator = 0, pedal_brake = 0;


//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                             ISR                                          //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

//ADC - 8kHz
void __ISR(_ADC_VECTOR,ipl2) isr_adc(void)
{
    unsigned short i = 0;
    static unsigned int adc_pos = 0;

    //From ADC1BUFx to adc_raw[x][adc_pos]
    adc_raw[0][adc_pos] = (unsigned short) ADC1BUF0;
    adc_raw[1][adc_pos] = (unsigned short) ADC1BUF1;
    adc_raw[2][adc_pos] = (unsigned short) ADC1BUF2;
    adc_raw[3][adc_pos] = (unsigned short) ADC1BUF3;
    adc_raw[4][adc_pos] = (unsigned short) ADC1BUF4;
    adc_raw[5][adc_pos] = (unsigned short) ADC1BUF5;
    adc_raw[6][adc_pos] = (unsigned short) ADC1BUF6;
    adc_raw[7][adc_pos] = (unsigned short) ADC1BUF7;

    //Fills the right buffer
    adc_pos++;
    if(adc_pos >= ADC_FILTER)
    {
        adc_pos = 0;
	flag_adc_filter = 1;	//Ready to be computed
    }

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

//We have 8 channels and we want 1kHz filtered results/channel
//We use a movering average of 8 samples
//f = 8*8*1kHz = 64kHz
//With 8 samples/ISR, the ISR frequency will be 8kHz

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
    Nop();			    // 1:1 PBCLK, wait 1 clock after changing ON
    AD1CON1bits.SIDL = 1;           // Stop in idle
    AD1CON1bits.FORM = 0;           // Integer 16bits
    AD1CON1bits.SSRC = 0b111;       // Auto convert
    AD1CON1bits.ASAM = 1;           // Automatic sampling
    AD1CON1bits.CLRASAM = 0;	    // Normal operation

    AD1CON2bits.VCFG = 0;           // Ref = VDD/VSS
    AD1CON2bits.OFFCAL = 0;         // Disable offset calibration
    AD1CON2bits.CSCNA = 1;          // Scan inputs
    AD1CON2bits.SMPI = 7;           // 8 channels
    AD1CON2bits.BUFM = 0;           // One buffer
    AD1CON2bits.ALTS = 0;           // Always use MUXA

    AD1CON3bits.ADRC = 0;           // PBCLK clock
    AD1CON3bits.SAMC = 1;	    // 
    AD1CON3bits.ADCS = 45;	    // 

    AD1CHSbits.CH0NA = 0;           // Negative input is VR-
    AD1CHSbits.CH0SA = 0;           // By default, AN0

    AD1PCFG = 0b1111000111100000;   // 0 = analog, 1 = digital
    AD1CSSL = 0b0000111000011111;   // 0 = skip, 1 = scan

    AD1CON1bits.ADON = 1;           // ADC ON
    Nop();			    // 1:1 PBCLK, wait 1 clock after changing ON

    IFS1bits.AD1IF = 0;              // clear interrupt flag
    IPC6bits.AD1IP = 2;              // interrupt priority 2
    IEC1bits.AD1IE = 1;              // enable interrupt

    IFS1bits.AD1IF = 0;              // clear interrupt flag - Errata
}

//Fills adc_mean[] with the filtered values
void filter_adc(void)
{
    unsigned short i = 0, j = 0;
    unsigned long sum = 0;

    for ( i = 0; i < ADC_CH; i++)
    {
        sum = 0;
        for ( j = 0; j < ADC_FILTER; j++)
        {
            sum += adc_raw[i][j];
        }
        adc_mean[i] = (sum >> ADC_FILTER_SHIFT);
    }
}

//Calls the proper conversion functions
void board_specific_adc_decode(void)
{
    //Onboard sensors:
    board_temp = read_temp(adc_mean[ADC_FILTERED_TEMP]);
    board_volt = read_vbat(adc_mean[ADC_FILTERED_VOLT]);

    if(GetBoardID() == VUE32_GENERIC)
    {
	Nop();
    }
    else if(GetBoardID() == VUE32_1)
    {
	Nop();
    }
    else if(GetBoardID() == VUE32_2)
    {
        Nop();
    }
    else if(GetBoardID() == VUE32_3)
    {
	Nop();
    }
    else if(GetBoardID() == VUE32_4)
    {
	Nop();
    }
    else if(GetBoardID() == VUE32_5)
    {
	pedal_accelerator = read_accelerator(adc_mean[ADC_FILTERED_AN0], adc_mean[ADC_FILTERED_AN1]);
	pedal_brake = read_brake(adc_mean[ADC_FILTERED_AN2]);
    }
    else if(GetBoardID() == VUE32_6)
    {
	read_yaw_lateral(adc_mean[ADC_FILTERED_AN1], adc_mean[ADC_FILTERED_AN0]);
    }
    else if(GetBoardID() == VUE32_7)
    {
	Nop();
    }
}
