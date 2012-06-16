
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
void Fct_Low_Light_Init(void);
void Fct_Low_Light(void);

void Fct_Left_Light_Init(void);
void Fct_Left_Light(void);

void Fct_Right_Light_Init(void);
void Fct_Right_Light(void);

void Fct_High_Light_Init(void);
void Fct_High_Light(void);

void Fct_Brake_Light_Init(void);
void Fct_Brake_Light(void);

void Fct_Night_Light_Init(void);
void Fct_Night_Light(void);

void Fct_Cooling_Pump_Init(void);
void Fct_Cooling_Pump(void);

void Fct_Wiper_Front_Pump_Init(void);
void Fct_Wiper_Front_Pump(void);

void Fct_Wiper_Back_Pump_Init(void);
void Fct_Wiper_Back_Pump(void);

#endif