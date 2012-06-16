
#ifndef ANALOGIC_MODULE_H
#define ANALOGIC_MODULE_H

#include "def.h"
#include "VUE32def.h"

#define HIGH_TEMP 70
#define LOW_TEMP 60

void Fct_Acc_Foot_init();
void Fct_Acc_Foot();
void Fct_Brk_Foot_init();
void Fct_Brk_Foot();
void Fct_Speed_Sensor_Left_Front();
void Fct_Speed_Sensor_Right_Front();
void Fct_Speed_Sensor_Left_Rear();
void Fct_Speed_Sensor_Right_Rear();
void Fct_Speed_Sensor_Left_Front_Init();
void Fct_Speed_Sensor_Right_Front_Init();
void Fct_Speed_Sensor_Left_Rear_Init();
void Fct_Speed_Sensor_Right_Rear_Init();


/* ********* Variable for internal Temperature ********** */
unsigned int unNextTempTimestamp;
unsigned int unLastTempTimestamp;
char cInternalTempStatus;
signed int board_temp;
/* ********* Function for internal Temperature ********** */
void Fct_Internal_Temp_init();
void Fct_Run_Check_Internal_Temp();





#endif

