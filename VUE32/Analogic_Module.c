

#include "Analogic_Module.h"

volatile unsigned int *Acc_Foot_Value;
volatile unsigned int *Brk_Foot_Value;

unsigned int *nSpeedSensorLeftFront;
unsigned int *nSpeedSensorRightFront;
unsigned int *nSpeedSensorLeftRear;
unsigned int *nSpeedSensorRightRear;

void Fct_Acc_Foot_init()
{
    Acc_Foot_Value = &AD1_mean[AD_position_for_ACC_FOOT];
    function_table[ucFunctTableSize++] = &Fct_Acc_Foot;
}
void Fct_Acc_Foot()
{
    // do something with Acc_Foot_Value
}
void Fct_Brk_Foot_init()
{
    Brk_Foot_Value = &AD1_mean[AD_position_for_BRK_FOOT];
    function_table[ucFunctTableSize++] = &Fct_Brk_Foot;
}
void Fct_Brk_Foot()
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

void Fct_Speed_Sensor_Left_Front_Init()
{
    function_table[ucFunctTableSize++] = &Fct_Speed_Sensor_Left_Front;
}
void Fct_Speed_Sensor_Right_Front_Init()
{
    function_table[ucFunctTableSize++] = &Fct_Speed_Sensor_Right_Front;
}
void Fct_Speed_Sensor_Left_Rear_Init()
{
    function_table[ucFunctTableSize++] = &Fct_Speed_Sensor_Left_Rear;
}
void Fct_Speed_Sensor_Right_Rear_Init()
{
    function_table[ucFunctTableSize++] = &Fct_Speed_Sensor_Right_Rear;
}
void Fct_Speed_Sensor_Left_Front()
{
    nSpeedSensorLeftFront = &speed[SPEED_SENSOR_LEFT_FRONT_PORT];
}
void Fct_Speed_Sensor_Right_Front()
{
    nSpeedSensorRightFront = &speed[SPEED_SENSOR_RIGHT_FRONT_PORT];
}
void Fct_Speed_Sensor_Left_Rear()
{
    nSpeedSensorLeftRear = &speed[SPEED_SENSOR_LEFT_REAR_PORT];
}
void Fct_Speed_Sensor_Right_Rear()
{
    nSpeedSensorRightRear = &speed[SPEED_SENSOR_RIGHT_REAR_PORT];
}




void Fct_Internal_Temp_init()
{
    cInternalTempStatus = 0;
    unLastTempTimestamp = unGlobalTimestamp;

    function_table[ucFunctTableSize++] = &Fct_Run_Check_Internal_Temp;

}
void Fct_Run_Check_Internal_Temp()
{
    TIMESTAMP_SECURITY(unLastTempTimestamp,100);
    if (COMPARE_TIMESTAMP(unLastTempTimestamp,100))
    {
        unLastTempTimestamp = unGlobalTimestamp;
        board_temp = CONV_TEMP((int)AD1_mean[6]);   // Température of the board that the ADC has returned and scanned
        if(board_temp > HIGH_TEMP)
        {
            //send to obd and deactivate power module
            power_module = FALSE;

        }
        else if (board_temp < LOW_TEMP)
        {
            power_module = TRUE;
        }
    }
}