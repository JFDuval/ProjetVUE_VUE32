#include "def.h"

int motor_speed = 0;
extern unsigned int adc_buf[ADC_CHANNELS];

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                         Interruptions                                    //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

void __ISR(_CORE_TIMER_VECTOR, ipl2) CoreTimerHandler(void)
{
    // .. things to do

	// .. Toggle the LED
    mPORTGToggleBits(BIT_15);
    
//    //Test: Send SPI word to control motor
//    motor_speed += 250;
//    if(motor_speed > 3000)
//    	motor_speed = 0;
//    SpiChnPutC(4, motor_speed);        

    // update the period
    UpdateCoreTimer(CORE_TICK_RATE);

    // clear the interrupt flag
    mCTClearIntFlag();
}

//ADC ISR
 void __ISR(_ADC_VECTOR, ipl6) AdcHandler(void)
 {     
	 static unsigned int channel = 2;    
    
    //Save actual data
    adc_buf[channel - 2] = ADC1BUF0;
    
    //Update channel
    ++channel;
    if(channel >= MAX_ADC_CH)
    	channel = MIN_ADC_CH;
	AD1CHSbits.CH0SA = channel;
	
	// clear the interrupt flag
    mAD1ClearIntFlag();
	
	//Start new conversion
	AD1CON1bits.SAMP = 1;
} 
