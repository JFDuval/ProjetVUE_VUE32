#ifndef INC_I2C_H
#define INC_I2C_H

#define ACK             TRUE
#define NACK            FALSE

#define ADXL345_W	0xA6    //Write
#define ADXL345_R	0xA7    //Read

//Registers:
#define ADXL345_DATA_FORMAT     0x31
#define ADXL345_POWER_CTL       0x2D
#define ADXL345_BW_RATE         0x2C

//Config values:
#define ADXL345_SET_POWER_CTL  0b00001000

#define ADXL345_X       0x32
#define ADXL345_Y       0x34
#define ADXL345_Z       0x36

#define SLAVE_ADD       0x66    //Our own slave address

//Bandwitdh. Note that Output rate is 2x Bandwitdh.
#define ADXL345_BW_1600     0b1111
#define ADXL345_BW_800      0b1110
#define ADXL345_BW_400      0b1101
#define ADXL345_BW_200      0b1100
#define ADXL345_BW_100      0b1011
#define ADXL345_BW_50       0b1010
#define ADXL345_BW_25       0b1001
//Note that values down to 0.05Hz are also available
//Note: max BW is linked to I2C frequency. At 100kHz, we are limited to 100Hz

//DATA_FORMAT register settings
//In all cases, we set the Full_Res bit
//Right justify
#define ADXL345_RANGE_2G    0b00001000
#define ADXL345_RANGE_4G    0b00001001
#define ADXL345_RANGE_8G    0b00001010
#define ADXL345_RANGE_16G   0b00001011

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                         	Function prototypes                        //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

void init_i2c(void);
void i2c_putc(unsigned char c);
unsigned char i2c_readc(unsigned char ackstate);
void init_adxl345(void);
void read_adxl345(char reg_adr);

#endif

