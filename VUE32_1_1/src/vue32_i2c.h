#ifndef INC_I2C_H
#define INC_I2C_H

#define ADXL345_W	0xA6
#define ADXL345_R	0xA7

#define ADXL345_CTL     0x2D

#define ADXL345_X       0x32
#define ADXL345_Y       0x34
#define ADXL345_Z       0x36

#define SLAVE_ADD       0x66    //Our own slave address

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                         	Function prototypes                        //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

void init_i2c(void);
void init_adxl345(void);
void read_adxl345(char reg_adr);

#endif

