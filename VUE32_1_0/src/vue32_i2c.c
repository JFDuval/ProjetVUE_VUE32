#include "vue32_i2c.h"
#include "def.h"

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
    I2C1CONbits.SMEN = 0;      // No SMBus
    I2C1CONbits.GCEN = 0;       // No general call
    I2C1CONbits.RCEN = 1;       // Enable receive

    I2C1CONbits.ON = 1;         // I2C On
}

unsigned int write_byte_i2c(unsigned char addr, unsigned char data)
{
}

unsigned int read_byte_i2c(unsigned char addr)
{
}
