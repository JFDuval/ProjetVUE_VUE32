#include "internalTemp.h"

void InternalTemp_init()
{
    cInternalTempStatus = 0;
    unLastTempTimestamp = unGlobalTimestamp;

    function_table[ucFunctTableSize++] = &RunCheckInternalTemp;

}


void RunCheckInternalTemp()
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

