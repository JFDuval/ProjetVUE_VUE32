#include "vue32_i2c.h"
#include "def.h"

//ToDo: Interrupt and not polling!
//ToDo: set refresh rate

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                    Constants and variables                               //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

short accel_x = 0, accel_y = 0, accel_z = 0;


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

//Read all 6 registers - Polling
void read_adxl345(char reg_adr)
{
    char data[6], i = 0;

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

    for(i = 0; i < 5; i++)
    {
	//Read data - First byte
	I2C1CONbits.RCEN = 1;		    // Enable receive
	while(!I2C1STATbits.RBF);
	I2CAcknowledgeByte(I2C1, TRUE);	    //ACK
	data[i] = I2C1RCV;		    //Read data
	while(!I2CAcknowledgeHasCompleted(I2C1));
    }

    //Read data - Last byte
    I2C1CONbits.RCEN = 1;		    // Enable receive
    while(!I2C1STATbits.RBF);
    I2CAcknowledgeByte(I2C1, FALSE);	    //NACK - Last transfer
    data[5] = I2C1RCV;			    //Read data
    while(!I2CAcknowledgeHasCompleted(I2C1));

    I2C1CONbits.PEN = 1;		    //Stop
    while(I2C1CONbits.PEN);

    //Store combined result
    accel_x = ((data[1]<<8) | data[0]);
    accel_y = ((data[3]<<8) | data[2]);
    accel_z = ((data[5]<<8) | data[4]);
}
