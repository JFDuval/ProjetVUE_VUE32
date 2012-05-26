
#include "def.h"

unsigned short Input_Timer_read;
unsigned short IC_Counter;

void Input_Capture_Init(void);

#define CONV_IC_TIME_IN_NS(x) (x/FPB*10^9);
#define ICI_CONST 0b11
#define ICx 1


