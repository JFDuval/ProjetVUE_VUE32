#include "vue32_i2c.h"
#include "def.h"

//I2C used for the ADXL345 3-axis accelerometer (Sparkfun breakout board)
//Some advices from Sparkfun:
//- SDO High = 0x1D, Low = 0x53. In our case: low.
//- We need to write in the 0x2D register before we can read data
//- The pull-ups are already present on the VUE32
//And from the datasheet:
// "With CS tied high to VDD I/O, the ADXL345 is in I2C mode"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                    Constants and variables                               //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                          Functions                                       //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

//Initialize I2C
void init_i2c(void)
{
    //100kHz Master:

    I2C1CONbits.ON = 0;         // I2C Off
    I2C1CONbits.SIDL = 0;       // Continue in idle
    I2C1CONbits.A10M = 0;       // 7-bit address
    I2C1CONbits.DISSLW = 1;     // No slew-rate control (good for 100kHz)
    I2C1CONbits.SMEN = 0;	// No SMBus
    I2C1CONbits.GCEN = 0;       // No general call
    I2C1CONbits.RCEN = 1;       // Enable receive

    I2C1ADD = SLAVE_ADD;

    //I2CxBRG = ((1/(2*Fsck) - Tpgd)*PBCLK)-2
    //I2CxBRG = ((1/(2*100kHz) - 104ns)*80MHz)-2 = 390
    I2C1BRG = 390;

    I2C1CONbits.ON = 1;         // I2C On
}

//The following code is an adaptation from Sparkfun's Nathan Seidle code

//ToDo clean and test
//ToDo: we need an escape condition for the many while()
//Setup ADXL345 for constant measurement mode
void init_adxl345(void)
{
    //Start communication
    while(!I2CBusIsIdle(I2C1));		    //Bus ready?
    I2CStart(I2C1);			    //Start
    while(I2C1CONbits.SEN);		    //Wait for Start to be over

    //Send address
    while(I2C1STATbits.TRSTAT);		    //Ready?
    I2C1TRN = ADXL345_W;		    //Send byte
    while(I2C1STATbits.TRSTAT);		    //Wait 'till transfer is over
    while(I2C1STATbits.ACKSTAT);	    //Wait 'till transfer we get an ACK

    //Send memory offset
    while(I2C1STATbits.TRSTAT);		    //Ready?
    I2C1TRN = ADXL345_CTL;		    //Send byte
    while(I2C1STATbits.TRSTAT);		    //Wait 'till transfer is over
    while(I2C1STATbits.ACKSTAT);	    //Wait 'till transfer we get an ACK

    //Send value
    while(!I2CTransmitterIsReady(I2C1));    //Ready?
    I2C1TRN = 0b00001000;		    //Send byte
    while(I2C1STATbits.TRSTAT);		    //Wait 'till transfer is over
    while(I2C1STATbits.ACKSTAT);	    //Wait 'till transfer we get an ACK

    I2C1CONbits.PEN = 1;		    //Stop
    while(I2C1CONbits.PEN);
}

short read_adxl345(char reg_adr)
{
    char lsb, msb;

    //Start communication
    while(!I2CBusIsIdle(I2C1));		    //Bus ready?
    I2CStart(I2C1);			    //Start
    while(I2C1CONbits.SEN);		    //Wait for Start to be over

    //Send address - Write
    while(I2C1STATbits.TRSTAT);		    //Ready?
    I2C1TRN = ADXL345_W;		    //Send byte
    while(I2C1STATbits.TRSTAT);		    //Wait 'till transfer is over
    while(I2C1STATbits.ACKSTAT);	    //Wait 'till transfer we get an ACK

    //Send memory offset
    while(I2C1STATbits.TRSTAT);		    //Ready?
    I2C1TRN = reg_adr;			    //Send byte
    while(I2C1STATbits.TRSTAT);		    //Wait 'till transfer is over
    while(I2C1STATbits.ACKSTAT);	    //Wait 'till transfer we get an ACK

    //Restart
    I2C1CONbits.RSEN = 1;		    //Restart
    while(I2C1CONbits.RSEN);		    //Wait for restart to be over

    //Send address - Read
    while(I2C1STATbits.TRSTAT);		    //Ready?
    I2C1TRN = ADXL345_R;		    //Send byte
    while(I2C1STATbits.TRSTAT);		    //Wait 'till transfer is over
    while(I2C1STATbits.ACKSTAT);	    //Wait 'till transfer we get an ACK

    //Read data - First byte
    I2C1CONbits.RCEN = 1;		    // Enable receive
    while(!I2C1STATbits.RBF);
    I2CAcknowledgeByte(I2C1, TRUE);	    //ACK
    lsb = I2C1RCV;			    //Read the LSB data
    while(!I2CAcknowledgeHasCompleted(I2C1));

    //Read data - Second byte
    I2C1CONbits.RCEN = 1;		    // Enable receive
    while(!I2C1STATbits.RBF);
    I2CAcknowledgeByte(I2C1, FALSE);	    //NACK - Last transfer
    msb = I2C1RCV;			    //Read the LSB data
    while(!I2CAcknowledgeHasCompleted(I2C1));

    I2C1CONbits.PEN = 1;		    //Stop
    while(I2C1CONbits.PEN);

    //Return combined result
    return( (msb<<8) | lsb);
}
