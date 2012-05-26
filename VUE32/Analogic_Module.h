
#ifndef ANALOGIC_MODULE_H
#define ANALOGIC_MODULE_H

#include "def.h"
#include "VUE32def.h"

#define HIGH_TEMP 70
#define LOW_TEMP 60

void Acc_Foot_init();
void Acc_Foot();
void Brk_Foot_init();
void Brk_Foot();
void Speed_Sensor_Left_Front();
void Speed_Sensor_Right_Front();
void Speed_Sensor_Left_Rear();
void Speed_Sensor_Right_Rear();
void Speed_Sensor_Left_Front_Init();
void Speed_Sensor_Right_Front_Init();
void Speed_Sensor_Left_Rear_Init();
void Speed_Sensor_Right_Rear_Init();


/* ********* Variable for internal Temperature ********** */
unsigned int unNextTempTimestamp;
unsigned int unLastTempTimestamp;
char cInternalTempStatus;
signed int board_temp;
/* ********* Function for internal Temperature ********** */
void Internal_Temp_init();
void Run_Check_Internal_Temp();





#endif

