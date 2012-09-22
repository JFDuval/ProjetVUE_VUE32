#ifndef _BSP_H_
#define _BSP_H_

#include "GenericTypeDefs.h"
#include <p32xxxx.h>
#include <plib.h>
#include <sys/kmem.h>

//UART BAUD RATE
#define DESIRED_BAUDRATE 1000000L

#define MODULE_TABLE_VERSION 0x02
#define MODULE_PROJECT_ID 0x66
#define MODULE_CODE_VERSION 0x01

#define DEVID_BASE_ADDRESS 0xBF80F220 //See Microchip 61145

#define T1_TICK 10*(SYS_XTAL_FREQ/PB_DIV/PRESCALE/TOGGLES_PER_SEC)


/**
    Define all the variables here to be accessible to the NETV protocol.

    The following data structure will fit with this XML configuration file in the NetworkViewer

    <!DOCTYPE INTROLAB-NETWORKVIEWER>
        <ModuleConfiguration moduleState="-1" deviceID="-1" projectID="1" codeVersion="1" processorID="-1" tableVersion="-1" >
        <ModuleVariable offset="0"  description="Description" type="uint8"  value="" name="Var1" />
        <ModuleVariable offset="1"  description="Description" type="uint16" value="" name="Var2" />
        <ModuleVariable offset="3"  description="Description" type="uint32" value="" name="Var3" />
        <ModuleVariable offset="7"  description="Description" type="sint8"  value="" name="Var4" />
        <ModuleVariable offset="8"  description="Description" type="sint16" value="" name="Var5" />
        <ModuleVariable offset="10" description="Description" type="sint32" value="" name="Var6" />
        <ModuleVariable offset="14" description="Description" type="float"  value="" name="Var7" />
        <ModuleVariable offset="18" description="Description" type="double" value="" name="Var8" />
    </ModuleConfiguration>
*/

typedef struct
{
    unsigned short  adc[8];             //Offset 0 to 14
    unsigned short  port;               //Offset 16
    short           accel_x;            //Offset 18
    short           accel_y;            //Offset 20
    short           accel_z;            //Offset 22
    unsigned short  steering_angle;     //Offset 24
    unsigned char   gfi_freq;           //Offset 26
    unsigned char   user_input;         //Offset 27
    unsigned char   vue32_id;           //Offset 28
    char            board_temp;         //Offset 29
    unsigned short  board_volt;         //Offset 30
    short           spdo1_kph;          //Offset 32
    short           spdo2_kph;          //Offset 34
    unsigned char   power_out;          //Offset 36

} GlobalNETVVariables;


#endif
