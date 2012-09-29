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
    I2C1CONbits.DISSLW = 0;     // Slew-rate control
    I2C1CONbits.SMEN = 0;	// No SMBus
    I2C1CONbits.GCEN = 0;       // No general call
    I2C1CONbits.RCEN = 1;       // Enable receive

    I2C1ADD = SLAVE_ADD;

    //I2CxBRG = ((1/(2*Fsck) - Tpgd)*PBCLK)-2
    //I2CxBRG = ((1/(2*100kHz) - 104ns)*80MHz)-2 = 390
    //I2CxBRG = ((1/(2*400kHz) - 104ns)*80MHz)-2 = 90
    I2C1BRG = 90;

    I2C1CONbits.ON = 1;         // I2C On
}


//Send a byte (address or data)
void i2c_putc(unsigned char c)
{
    while(I2C1STATbits.TRSTAT);		    //Ready?
    I2C1TRN = c;			    //Send byte
    while(I2C1STATbits.TRSTAT);		    //Wait 'till transfer is over
    while(I2C1STATbits.ACKSTAT);	    //Wait 'till transfer we get an ACK
}

//Read a byte, then ACK or NACK
unsigned char i2c_readc(unsigned char ackstate)
{
    unsigned char byte = 0;

    I2C1CONbits.RCEN = 1;		    //Enable receive
    while(!I2C1STATbits.RBF);
    I2CAcknowledgeByte(I2C1, ackstate);	    //ACK
    byte = I2C1RCV;			    //Read data
    while(!I2CAcknowledgeHasCompleted(I2C1));

    return byte;
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
    i2c_putc(ADXL345_W);

    //Send memory offset - BW_RATE
    i2c_putc(ADXL345_BW_RATE);

    //Send BW_RATE value
    i2c_putc(ADXL345_BW_100);

    //Send POWER_CTL value
    i2c_putc(ADXL345_SET_POWER_CTL);
    //Ok because POWER_CTL is right after BW_RATE

    //Stop
    I2C1CONbits.PEN = 1;
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
    i2c_putc(ADXL345_W);

    //Send memory offset
    i2c_putc(reg_adr);

    //Restart
    I2C1CONbits.RSEN = 1;		    //Restart
    while(I2C1CONbits.RSEN);		    //Wait for restart to be over

    //Send address - Read
    i2c_putc(ADXL345_R);

    for(i = 0; i < 5; i++)
    {
	data[i] = i2c_readc(ACK);
    }

    //Read data - Last byte
    data[5] = i2c_readc(NACK);

    I2C1CONbits.PEN = 1;		    //Stop
    while(I2C1CONbits.PEN);

    //Store combined result
    accel_x = ((data[1]<<8) | data[0]);
    accel_y = ((data[3]<<8) | data[2]);
    accel_z = ((data[5]<<8) | data[4]);
}
