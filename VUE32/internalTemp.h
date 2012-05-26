#ifndef INTERNAL_TEMP_H
#define INTERNAL_TEMP_H

#include "def.h"


/* ********* Variable for internal Temperature ********** */
unsigned int unNextTempTimestamp;
unsigned int unLastTempTimestamp;
#define HIGH_TEMP 70
#define LOW_TEMP 60

char cInternalTempStatus;
signed int board_temp;


/* ********* Function for internal Temperature ********** */
void InternalTemp_init();
void RunCheckInternalTemp();
#endif

