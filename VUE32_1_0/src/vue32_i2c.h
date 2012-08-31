#ifndef INC_I2C_H
#define INC_I2C_H

//SDO Low, address = 0x1D:
#define ADXL345_W	0b00111010
#define ADXL345_R	0b00111011

#define ADXL345_CTL     0x2D

#define ADXL345_X       0x32
#define ADXL345_Y       0x34
#define ADXL345_Z       0x36

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                         	Function prototypes                        //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

void init_i2c(void);
void init_adxl345(void);
unsigned int read_adxl345(char reg_adr);

#endif

