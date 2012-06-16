/*********************************************************************
 * FileName:        AD110_basic.c
 * Dependencies:	plib.h
 *plib.h
 *
 * Processor:       PIC32MX795F512H
 *
 * Complier:        MPLAB C32
 *                  MPLAB IDE v8.0+
 * Company:         Microchip Technology Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the Company) for its PIC32 Microcontroller is intended
 * and supplied to you, the Companys customer, for use solely and
 * exclusively on Microchip PIC32 Microcontroller products.
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN AS IS CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************
 * File description : à écrire
 *
 *
 ********************************************************************/

#include "adc_vue32.h"


unsigned int AD1Value[AD1_NUM_CH][SAMPLE_MEAN]; //Primary variable, used to calculate the mean value and is the Round Robin Archive
unsigned int AD116Ptr;
unsigned char BUF_position; //Counter used to scan the different AD1_Buffer in the interrupt
unsigned char AD1_RRA_position; //Counter for the Round Robin Archive (contain the position of the value to be erased)
unsigned char initChannel;  //Counter used to initialize the Channel of the AD1 auto-scan
unsigned char AD1_counter;   //Primary counter for AD1 Interruption
unsigned char AD1_counter2;   //Secondary counter for AD1 Interruption


void __ISR(_ADC_VECTOR,ipl2) FCT_ADC_Handler(void){

    // Read all buffers
    for (BUF_position=0; BUF_position<AD1_NB_BUFFERS; BUF_position++)
    {
        AD1Value[BUF_position][AD1_RRA_position] = ReadADC10(BUF_position);
    }

    // Management of the round robin archive for stocking the value
    AD1_RRA_position++;
    if(AD1_RRA_position>=SAMPLE_MEAN) {AD1_RRA_position=0;}

    flagAD1 = TRUE;

    // Clear the AD1 interrupt flag
    IFS1CLR = _IFS1_AD1IF_MASK;
}
void Fct_AD1_init(const unsigned short cusUsedChannels){

        //initialisation des variables globales de l'AD1
        unsigned short j,i;
        BUF_position = 0;
        AD1_RRA_position =0;
        flagAD1 = FALSE;
        for ( i = 0; i < AD1_NUM_CH; i++)

            for ( j = 0; j < SAMPLE_MEAN; j++)
                AD1Value[i][j] = 0;

        // Configuration de l'ADC
        AD1CON1 = AD1ON1_STOP_IN_IDLE_MODE | AD1ON1_DATA_OUPUT_FORMAT_u16 | AD1ON1_AUTO_CONVERT_TRIGGER | AD1ON1_SAMBPLE_AUTO_START;
        AD1CON2 = AD1ON2_SCAN_INPUTS | AD1ON2_INT_EVERY_X_SAMPLE(AD1_NB_BUFFERS);
        AD1CON3 = AD1ON3_AUTOSAMPLE_TIME(CONVERSION_TIME_AD) | AD1ON3_TIME_FOR_1_TAD(ADC_PB_DIVIDER);
        AD1CSSL = cusUsedChannels;
        TRISB = TRISB | cusUsedChannels;
        AD1PCFG = AD1PCFG & ~cusUsedChannels;
    
        IFS1bits.AD1IF = 0;              // clear interrupt flag
        IPC6bits.AD1IP = 2;              // interrupt priority 2
        IEC1bits.AD1IE = 1;              // enable interrupt
        AD1CON1bits.ADON = 1;            //turn ON the AD1
        function_table[ucFunctTableSize++] = &Fct_AD1_Mean; //Put the mean value function into the function table
}

void Fct_AD1_Mean(void)
{
    if(flagAD1 == TRUE)
    {
    //Calculating the mean value
        for(AD1_counter=0;AD1_counter<AD1_NUM_CH;AD1_counter++)
        {
            AD1_mean[AD1_counter] = 0 ;
            for (AD1_counter2=0;AD1_counter2<SAMPLE_MEAN;AD1_counter2++)
            {
                AD1_mean[AD1_counter] = AD1Value[AD1_counter][AD1_counter2]+AD1_mean[AD1_counter];
            }
            AD1_mean[AD1_counter] = AD1_mean[AD1_counter]>>(SAMPLE_MEAN/2);
        }
        flagAD1=FALSE;
    }
}
