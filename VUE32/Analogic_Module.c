

#include "Analogic_Module.h"

volatile unsigned int *Acc_Foot_Value;
volatile unsigned int *Brk_Foot_Value;

unsigned int *nSpeedSensorLeftFront;
unsigned int *nSpeedSensorRightFront;
unsigned int *nSpeedSensorLeftRear;
unsigned int *nSpeedSensorRightRear;

void Acc_Foot_init()
{
    Acc_Foot_Value = &AD1_mean[AD_position_for_ACC_FOOT];
    function_table[ucFunctTableSize++] = &Acc_Foot;
}
void Acc_Foot()
{
    // do something with Acc_Foot_Value
}
void Brk_Foot_init()
{
    Brk_Foot_Value = &AD1_mean[AD_position_for_BRK_FOOT];
    function_table[ucFunctTableSize++] = &Brk_Foot;
}
void Brk_Foot()
{
    if(*(Brk_Foot_Value) > 3 )
    {
        cBrakeLight =1;
    }
    else
    {
        cBrakeLight =0;
    }
}

void Speed_Sensor_Left_Front_Init()
{
    function_table[ucFunctTableSize++] = &Speed_Sensor_Left_Front;
}
void Speed_Sensor_Right_Front_Init()
{
    function_table[ucFunctTableSize++] = &Speed_Sensor_Right_Front;
}
void Speed_Sensor_Left_Rear_Init()
{
    function_table[ucFunctTableSize++] = &Speed_Sensor_Left_Rear;
}
void Speed_Sensor_Right_Rear_Init()
{
    function_table[ucFunctTableSize++] = &Speed_Sensor_Right_Rear;
}
void Speed_Sensor_Left_Front()
{
    nSpeedSensorLeftFront = &speed[SPEED_SENSOR_LEFT_FRONT_PORT];
}
void Speed_Sensor_Right_Front()
{
    nSpeedSensorRightFront = &speed[SPEED_SENSOR_RIGHT_FRONT_PORT];
}
void Speed_Sensor_Left_Rear()
{
    nSpeedSensorLeftRear = &speed[SPEED_SENSOR_LEFT_REAR_PORT];
}
void Speed_Sensor_Right_Rear()
{
    nSpeedSensorRightRear = &speed[SPEED_SENSOR_RIGHT_REAR_PORT];
}