
#ifndef POWER_MODULE_H
#define POWER_MODULE_H

#include "def.h"
#include "VUE32def.h"
/* ***** Variable of the Power Module ***** */
//Left Light variables
unsigned int unLastLeftLightTimestamp;
unsigned char LeftLighToggle;

//Right Light variables
unsigned int unLastRightLightTimestamp;
unsigned char RightLighToggle;





/* *************Power Module Function************** */
void Low_Light_Init(void);
void Low_Light(void);

void Left_Light_Init(void);
void Left_Light(void);

void Right_Light_Init(void);
void Right_Light(void);

void High_Light_Init(void);
void High_Light(void);

void Brake_Light_Init(void);
void Brake_Light(void);

void Night_Light_Init(void);
void Night_Light(void);

void Cooling_Pump_Init(void);
void Cooling_Pump(void);

void Wiper_Front_Pump_Init(void);
void Wiper_Front_Pump(void);

void Wiper_Back_Pump_Init(void);
void Wiper_Back_Pump(void);

#endif